//---------------------------------------------------------------------
// MIT License
// 
// Copyright (c) 2024 TLBurnett3
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//---------------------------------------------------------------------

// Thomas Burnett
// Model.cpp

//---------------------------------------------------------------------
// Includes
// System
#include <assert.h>
#include <iostream>

// 3rd Party Libs
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>

// LightField
#include "RenderGL/Model.h"

#ifndef _GLES2
#include "RenderGL/VtxArrayObj.h"
#else
#include "Engine/VtxBufferObj.h"
#endif

using namespace Lf;
using namespace RenderGL;
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// createMaterial
//---------------------------------------------------------------------
Texture *Model::createTexture(const struct aiMaterial *pAIMaterial)
{
Texture     *pTexture = new Texture();
aiString    tName;
glm::mat4   mProp(0);
aiColor4D   c;

  if (pAIMaterial->Get(AI_MATKEY_COLOR_AMBIENT,c) == AI_SUCCESS)
    mProp[0] = glm::vec4(c.r,c.g,c.b,c.a);

  if (pAIMaterial->Get(AI_MATKEY_COLOR_DIFFUSE,c) == AI_SUCCESS)
    mProp[1] = glm::vec4(c.r,c.g,c.b,c.a);
 
  if (pAIMaterial->Get(AI_MATKEY_COLOR_SPECULAR,c) == AI_SUCCESS)
    mProp[2] = glm::vec4(c.r,c.g,c.b,c.a);
 
  pAIMaterial->Get(AI_MATKEY_SHININESS,mProp[3][0]);
  
  if (pAIMaterial->GetTexture(aiTextureType_DIFFUSE,0,&tName) == AI_SUCCESS)
  {
    if (tName.length)
    {
    std::filesystem::path tPath = _mPath;
    cv::Mat               img;

      tPath /= tName.data;

      img = cv::imread(tPath.string());

      cv::flip(img,img,0);

      if (img.data)
        pTexture->upload(img);
      else
       std::cout << "File not found: " << tPath << std::endl;
    }
  }
  else
  {
  cv::Mat     img(cv::Size(16,16),CV_8UC4);
  cv::Scalar  clr;
        
    clr[0] = (unsigned char)(mProp[1][2] * 255.0f);
    clr[1] = (unsigned char)(mProp[1][1] * 255.0f);
    clr[2] = (unsigned char)(mProp[1][0] * 255.0f);
    clr[3] = (unsigned char)(mProp[1][3] * 255.0f);

    img.setTo(clr);

    pTexture->upload(img);
  } 

  pTexture->setProperties(mProp);

  return pTexture;
}


//---------------------------------------------------------------------
// createMesh
//---------------------------------------------------------------------
Mesh *Model::createMesh(const struct aiMesh *pAIMesh)
{
Mesh *pMesh = 0;

  if (pAIMesh->mPrimitiveTypes == aiPrimitiveType_TRIANGLE)
  {
  IdxLst        idxLst;
#ifndef _GLES2
  Object        *pRO = new VtxArrayObj();
#else
  tLib::RenderObject  *pRO = new tLib::VtxBufferObj();
#endif

    pMesh  = new Mesh();

    pMesh->setTexture(_textureLst[pAIMesh->mMaterialIndex]);

    // name
    {
    std::string   name;

      if (pAIMesh->mName.length)
        name = pAIMesh->mName.data;
      else
      {
      static uint32_t  iMesh = 0;
      char        buf[32];

        sprintf_s(buf,"%d",iMesh);

        name  = "Mesh_";
        name += buf; 

        iMesh++;
      }

      pMesh->setName(name);
    }

    // IdxLst
    {
    unsigned int nPnts = 3;

      idxLst.reserve(pAIMesh->mNumFaces * nPnts);

      for (unsigned int i = 0;i < pAIMesh->mNumFaces;i++) 
      {
      const struct aiFace *pFace = &pAIMesh->mFaces[i];

        for (unsigned int j = 0;j < nPnts;j++)
          idxLst.push_back(*(pFace->mIndices + j));
      }
    }

    // Vertex attributes
    if (pAIMesh->HasPositions() && pAIMesh->HasNormals() && pAIMesh->HasTextureCoords(0)) 
    {
    VtxVNTLst vtxLst;
    VtxVNT    vtx;

      vtxLst.reserve(pAIMesh->mNumVertices);

      for (size_t i = 0;i < pAIMesh->mNumVertices;i++)
      {
        vtx._V = glm::vec3(pAIMesh->mVertices[i].x,pAIMesh->mVertices[i].y,pAIMesh->mVertices[i].z);
        vtx._N = glm::vec3(pAIMesh->mNormals[i].x,pAIMesh->mNormals[i].y,pAIMesh->mNormals[i].z);
        vtx._T = glm::vec2(pAIMesh->mTextureCoords[0][i].x,pAIMesh->mTextureCoords[0][i].y);

        vtxLst.add(vtx);
      }

      pRO->upload(vtxLst,idxLst,GL_TRIANGLES);

      pMesh->setNumFaces(pAIMesh->mNumFaces);
      pMesh->setNumVertices(pAIMesh->mNumVertices);
      pMesh->setNumNormals(pAIMesh->mNumVertices);
      pMesh->setNumTexCoords(pAIMesh->mNumVertices);
      pMesh->bound(vtxLst.vMin(),vtxLst.vMax());

      bound(vtxLst.vMin(),vtxLst.vMax());
    }
    else if (pAIMesh->HasPositions() && pAIMesh->HasNormals()) 
    {
    VtxVNLst  vtxLst;
    VtxVN     vtx;

      vtxLst.reserve(pAIMesh->mNumVertices);

      for (size_t i = 0;i < pAIMesh->mNumVertices;i++)
      {
        vtx._V = glm::vec3(pAIMesh->mVertices[i].x,pAIMesh->mVertices[i].y,pAIMesh->mVertices[i].z);
        vtx._N = glm::vec3(pAIMesh->mNormals[i].x,pAIMesh->mNormals[i].y,pAIMesh->mNormals[i].z);

        vtxLst.add(vtx);
      }

      pRO->upload(vtxLst,idxLst,GL_TRIANGLES);

      pMesh->setNumFaces(pAIMesh->mNumFaces);
      pMesh->setNumVertices(pAIMesh->mNumVertices);
      pMesh->setNumNormals(pAIMesh->mNumVertices);
      pMesh->bound(vtxLst.vMin(),vtxLst.vMax());

      bound(vtxLst.vMin(),vtxLst.vMax());
    }
    else if (pAIMesh->HasPositions() && pAIMesh->HasTextureCoords(0)) 
    {
    VtxVTLst  vtxLst;
    VtxVT     vtx;

      vtxLst.reserve(pAIMesh->mNumVertices);

      for (size_t i = 0;i < pAIMesh->mNumVertices;i++)
      {
        vtx._V = glm::vec3(pAIMesh->mVertices[i].x,pAIMesh->mVertices[i].y,pAIMesh->mVertices[i].z);
        vtx._T = glm::vec2(pAIMesh->mTextureCoords[0][i].x,pAIMesh->mTextureCoords[0][i].y);

        vtxLst.add(vtx);
      }

      pRO->upload(vtxLst,idxLst,GL_TRIANGLES);

      pMesh->setNumFaces(pAIMesh->mNumFaces);
      pMesh->setNumVertices(pAIMesh->mNumVertices);
      pMesh->setNumTexCoords(pAIMesh->mNumVertices);
      pMesh->bound(vtxLst.vMin(),vtxLst.vMax());

      bound(vtxLst.vMin(),vtxLst.vMax());
    }
    else if (pAIMesh->HasPositions()) 
    {
    VtxVLst  vtxLst;
    VtxV     vtx;

      vtxLst.reserve(pAIMesh->mNumVertices);

      for (size_t i = 0;i < pAIMesh->mNumVertices;i++)
      {
        vtx._V = glm::vec3(pAIMesh->mVertices[i].x,pAIMesh->mVertices[i].y,pAIMesh->mVertices[i].z);

        vtxLst.add(vtx);
      }

      pRO->upload(vtxLst,idxLst,GL_TRIANGLES);

      pMesh->setNumFaces(pAIMesh->mNumFaces);
      pMesh->setNumVertices(pAIMesh->mNumVertices);
      pMesh->bound(vtxLst.vMin(),vtxLst.vMax());

      bound(vtxLst.vMin(),vtxLst.vMax());
    }

    pMesh->setRenderObject(pRO);
  }

  return pMesh;
}


//---------------------------------------------------------------------
// createNode
//---------------------------------------------------------------------
Node *Model::createNode(const struct aiNode *pAINode)
{
Node      *pNode  = new Node();
glm::mat4 mT      = glm::mat4(pAINode->mTransformation.a1,pAINode->mTransformation.b1,pAINode->mTransformation.c1,pAINode->mTransformation.d1, 
                              pAINode->mTransformation.a2,pAINode->mTransformation.b2,pAINode->mTransformation.c2,pAINode->mTransformation.d2,
                              pAINode->mTransformation.a3,pAINode->mTransformation.b3,pAINode->mTransformation.c3,pAINode->mTransformation.d3, 
                              pAINode->mTransformation.a4,pAINode->mTransformation.b4,pAINode->mTransformation.c4,pAINode->mTransformation.d4);

  pNode->setName(pAINode->mName.data);
  pNode->setTransformMatrix(mT);

  if (pAINode->mNumMeshes)
  {
    pNode->_meshLst.reserve(pAINode->mNumMeshes);

    for (size_t i = 0;i < pAINode->mNumMeshes;i++)
    {
    Mesh  *pMesh  = _meshLst[pAINode->mMeshes[i]];

      if (pMesh)
      {
        pNode->_meshLst.push_back(pMesh);
        pNode->bound(pMesh->vMax(),pMesh->vMin());
      }
    }
  }

  if (pAINode->mNumChildren)
  {
    pNode->_nodeLst.reserve(pAINode->mNumChildren);

    for (size_t i = 0;i < pAINode->mNumChildren;i++)
    {
    Node  *pN  = createNode(pAINode->mChildren[i]);

      pNode->bound(pN->vMax(),pN->vMin());
      pNode->_nodeLst.push_back(pN);
    }
  }

  pNode->adjustBounds(mT);

  return pNode;
}


//---------------------------------------------------------------------
// walkMaterials
//---------------------------------------------------------------------
void Model::walkTextures(const struct aiScene *pAIScene)
{
  _textureLst.reserve(pAIScene->mNumMaterials);

  for (size_t i = 0;i < pAIScene->mNumMaterials;i++)
  {
  Texture  *pTO  = createTexture(pAIScene->mMaterials[i]);

    _textureLst.push_back(pTO);
  }
}


//---------------------------------------------------------------------
// walkMeshes
//---------------------------------------------------------------------
void Model::walkMeshes(const struct aiScene *pAIScene)
{
  _meshLst.reserve(pAIScene->mNumMeshes);

  for (size_t i = 0;i < pAIScene->mNumMeshes;i++)
  {
  Mesh *pMesh  = createMesh(pAIScene->mMeshes[i]);

    _meshLst.push_back(pMesh);
  }
}


//---------------------------------------------------------------------
// walkScene
//---------------------------------------------------------------------
void Model::walkScene(const struct aiScene *pAIScene,const glm::mat4 &mT,uint32_t f)
{
  walkTextures(pAIScene);
  walkMeshes(pAIScene);
  
  _pRoot = createNode(pAIScene->mRootNode);

  _pRoot->_mT = mT * _pRoot->_mT;
}


//---------------------------------------------------------------------
// load
//---------------------------------------------------------------------
int Model::load(const std::filesystem::path &mFile,
                const glm::mat4 &mT,
                uint32_t aFlags,
                const uint32_t flags)
{
int               rc = -1;
Assimp::Importer  importer;

  std::cout << "Parsing: " << mFile << std::endl;
  
  {
  const struct  aiScene   *pAIScene = importer.ReadFile(mFile.string().c_str(),aFlags);

    if (pAIScene)
    {
      _mPath = mFile.parent_path();

      std::cout << "Creating scene" << std::endl;

      walkScene(pAIScene,mT,flags);
        
      std::cout << "Release importer scene memory" << std::endl;

      importer.FreeScene();

      rc = 0;
    }    
  }

  return rc;
}


//---------------------------------------------------------------------
// render
//---------------------------------------------------------------------
void Model::render(const Core::Camera *pCamera,const Shader *pShader,const glm::mat4 &mT)
{
  _pRoot->render(pCamera,pShader,mT);
}


//---------------------------------------------------------------------
// printVec3
//---------------------------------------------------------------------
void Model::printVec3(std::ostream &s,std::string idt,const char *name,const glm::vec3 v)
{
char  buf[128];

  sprintf_s(buf,"%20s: %f %f %f",name,v.x,v.y,v.z);
  s << idt << buf << std::endl;
}


//---------------------------------------------------------------------
// print
//---------------------------------------------------------------------
void Model::print(std::ostream &s,bool detail)
{
std::string  idt = " ";

  s << "Name: " << _sName << std::endl;
  s << "Path: " << _mPath << std::endl;
  
  printVec3(s,idt,"Min",_vMin);
  printVec3(s,idt,"Max",_vMax);
  printVec3(s,idt,"Cen",_vCen);
  printVec3(s,idt,"Dim",_vDim);

  s << "Number of Textures: " << _textureLst.size() << std::endl;
  //for (tLib::tUL i = 0;i < _textureLst.size();i++)
   // _textureLst[i]->print(s,idt + "  ",detail);

  s << "Number of Meshes: " << _meshLst.size() << std::endl;
  for (size_t i = 0;i < _meshLst.size();i++)
  {
    if (_meshLst[i])
      _meshLst[i]->print(s,idt + "  ",detail);
    else
      s << "Mesh: " << i << " is empty" << std::endl;
  }

  if (detail)
  {
    s << "Node Hierarchy" << std::endl;
    _pRoot->print(s,idt);
  }
}

//---------------------------------------------------------------------
// Model
//---------------------------------------------------------------------
Model::Model(void) : Bound(),
                     _sName(),
                     _mPath(),
                     _textureLst(),
                     _meshLst(),
                     _pRoot(0)
                     
{

}


//---------------------------------------------------------------------
// ~Model
// September 9, 2011
// Thomas Burnett
//---------------------------------------------------------------------
Model::~Model(void)
{
  while (!_meshLst.empty())
  {
    delete _meshLst.back();
    _meshLst.pop_back();
  }

  while (!_textureLst.empty())
  {
    delete _textureLst.back();
    _textureLst.pop_back();
  }

  delete _pRoot;
}

