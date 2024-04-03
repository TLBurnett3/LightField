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

// ModMan.cpp 
// Thomas Burnett


//---------------------------------------------------------------------
// Includes
// System
#include <iostream>
#include <assert.h>

//3rdPartyLibs
#include <assimp/postprocess.h>

// LightField
#include "Render/ModMan.h"
#include "Render/VtxArrayObj.h"


using namespace Lf;
using namespace Render;
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// summary
//---------------------------------------------------------------------
void ModMan::print(std::ostream &s)
{
size_t n  = _modelLst.size();

  for (size_t i = 0;i < n;i++)
    _modelLst[i]->print(s,false);
}


//---------------------------------------------------------------------
// render
//---------------------------------------------------------------------
void ModMan::render(const Camera &camera,const Shader &shader,const glm::mat4 &mT)
{
size_t n  = _modelLst.size();

  for (size_t i = 0;i < n;i++)
    _modelLst[i]->render(camera,shader,mT);
}

/*

//---------------------------------------------------------------------
// createImagePlane
//---------------------------------------------------------------------
void ModMan::createImagePlane(const glm::mat4 &mT,const glm::vec3 &fD)
{
VtxVNTLst           vtxLst;
cv::Mat             img(cv::Size(64,64),CV_8UC3);
Model               *pModel = new Model();
#ifndef _GLES2
Object              *pRO    = new VtxArrayObj();
#else
tLib::RenderObject  *pRO    = new tLib::VtxBufferObj();
#endif
Texture             *pTexture   = new Texture();
Mesh                *pMesh      = new Mesh();
Node                *pNode      = new Node();
int                 rM          = createQuadXZ(glm::vec3(0),vtxLst,glm::vec2(fD.x,fD.z));

  img.setTo(cv::Scalar(244,221,255));

  pTexture->upload(img);
  pTexture->setProperties(glm::mat4(glm::vec4(0),glm::vec4(1),glm::vec4(0),glm::vec4(0)));
  pRO->upload(vtxLst,rM);
  
  pMesh->setTexture(pTexture);
  pMesh->setRenderObject(pRO);

  pNode->setTransformMatrix(mT);
  pNode->addMesh(pMesh);

  pModel->setRootNode(pNode);
  pModel->bound(pNode->vMin(),pNode->vMax());

  _imagePlaneModel = pModel;
}*/



//---------------------------------------------------------------------
// load
//---------------------------------------------------------------------
int ModMan::load(const std::filesystem::path &mFile,
                          const glm::mat4 &mT)
{
int   rc      = 0;
Model *pModel = new Model();

  if (pModel)
  {
  uint32_t  aFlags  = 0                               |
                aiProcess_JoinIdenticalVertices       |
                aiProcess_Triangulate                 |
                aiProcess_RemoveComponent             |
                aiProcess_GenSmoothNormals            |
                aiProcess_SplitLargeMeshes            |
                aiProcess_PreTransformVertices        |
                aiProcess_ImproveCacheLocality        |
                aiProcess_RemoveRedundantMaterials    |
                aiProcess_SortByPType                 |
                aiProcess_FindInvalidData             |
                aiProcess_GenUVCoords                 |
                aiProcess_TransformUVCoords           |
                aiProcess_FindInstances               |
                aiProcess_OptimizeMeshes              |
                //aiProcess_OptimizeGraph               |
                0;

    rc |= pModel->load(mFile,mT,aFlags);
  }

  if (rc == 0)
  {
    _modelLst.push_back(pModel);

    _max = glm::max(_max,pModel->vMax());
    _min = glm::min(_min,pModel->vMin());
    _cen = (_max + _min) * 0.5f;
  }
  else
    delete pModel;


  return rc;
}


//---------------------------------------------------------------------
// init
//---------------------------------------------------------------------
int ModMan::init(const std::filesystem::path &cPath)
{
int rc = 0;

return rc;
}


//---------------------------------------------------------------------
// ModMan
//---------------------------------------------------------------------
ModMan::ModMan(void) : _modelLst(),
                       _max(-FLT_MAX),
                       _min(FLT_MIN),
                       _cen(0),
                       _imagePlaneModel(0)
{
}


//---------------------------------------------------------------------
// ~ModMan
//---------------------------------------------------------------------
ModMan::~ModMan()
{
  while (!_modelLst.empty())
  {
    delete _modelLst.back();
    _modelLst.pop_back();
  }

  delete _imagePlaneModel;
}
