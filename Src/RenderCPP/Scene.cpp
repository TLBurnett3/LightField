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

// Scene.cpp 
// Thomas Burnett


//---------------------------------------------------------------------
// Includes
// System
#include <iostream>

// 3rdPartyLibs
#include <assimp/postprocess.h>

// Lightfield
#include "RenderCPP/Scene.h"

using namespace Lf;
using namespace RenderCPP;
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Globals
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// clear
//---------------------------------------------------------------------
void Scene::clear(void)
{
  while (!_modelLst.empty())
  {
    delete _modelLst.back();
    _modelLst.pop_back();
  }
}


//---------------------------------------------------------------------
// render
//---------------------------------------------------------------------
void Scene::render(const HogelDef::Camera &camera,Shader *pShader,const glm::mat4 &mT)
{
ModelLst::iterator  ii    = _modelLst.begin();
ModelLst::iterator  iEnd  = _modelLst.end();

  while (ii != iEnd)
  {
    (*ii)->render(camera,pShader,mT);
    ii++;
  }
}


//---------------------------------------------------------------------
// load
//---------------------------------------------------------------------
int Scene::load(const std::filesystem::path &mFile,const glm::mat4 &mT)
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

    std::cout << "Loadeding: " << mFile << std::endl;   
 
    rc |= pModel->load(mFile,mT,aFlags);
  }

  if (rc == 0)
  {
    _modelLst.push_back(pModel);
  }
  else
    delete pModel;

  return rc;
}



//---------------------------------------------------------------------
// init
//---------------------------------------------------------------------
int Scene::init(const std::filesystem::path &cPath)
{
int rc = 0;

return rc;
}



//---------------------------------------------------------------------
// Scene
//---------------------------------------------------------------------
Scene::Scene(void) : _modelLst()
{
}


//---------------------------------------------------------------------
// ~Scene
//---------------------------------------------------------------------
Scene::~Scene()
{
}
