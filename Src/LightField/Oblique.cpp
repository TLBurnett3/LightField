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

// Oblique.cpp 
// Thomas Burnett


//---------------------------------------------------------------------
// Includes
// System
#include <string>
#include <iostream>

// 3rdPartyLibs
#include <glm/glm.hpp>
#include <glm/ext.hpp>

// LightField
#include "RenderGL/Def.h"
#include "LightField/Oblique.h"
#include "Core/Timer.h"
#include "RenderGL/Camera.h"
#include "Tasks/ProofImage.h"
#include "Tasks/WriteAvi.h"
#include "Tasks/WriteImg.h"
#include "Tasks/SliceNDice.h"

using namespace Lf;
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// fetchAndQueue
//---------------------------------------------------------------------
void Oblique::fetchAndQueue(glm::ivec2 idx)
{
glm::ivec2  nH      = _spJob->numHogels();

  if (_imgTaskLst.size())
  {
  TaskList::iterator        ii    = _imgTaskLst.begin();
  TaskList::iterator        iEnd  = _imgTaskLst.end();
  Task::Base::SpImg         spImg = std::make_shared<std::pair<cv::Mat,glm::ivec2>>();

    spImg->first.create(nH.y,nH.x,CV_8UC3);
    spImg->second = idx;

    glReadBuffer(GL_BACK);
    glReadPixels(0,0,(GLsizei)nH.x,(GLsizei)nH.y,GL_BGR,GL_UNSIGNED_BYTE,spImg->first.data); 
    
    cv::flip(spImg->first,spImg->first,0);

    while (ii != iEnd)
    {
      (*ii)->queue(spImg);
      ii++;
    }
  }

  if (_dthTaskLst.size())
  {
  TaskList::iterator        ii    = _dthTaskLst.begin();
  TaskList::iterator        iEnd  = _dthTaskLst.end();
  Task::Base::SpImg         spImg = std::make_shared<std::pair<cv::Mat,glm::ivec2>>();

    spImg->first.create(nH.y,nH.x,CV_32FC1);
    spImg->second = idx;

    glReadBuffer(GL_BACK);
    glReadPixels(0,0,(GLsizei)nH.x,(GLsizei)nH.y,GL_DEPTH_COMPONENT,GL_FLOAT,spImg->first.data);

    cv::flip(spImg->first,spImg->first,0);

    while (ii != iEnd)
    {
      (*ii)->queue(spImg);
      ii++;
    }
  }
}



//---------------------------------------------------------------------
// createTasks
//---------------------------------------------------------------------
void Oblique::createTasks(void)
{
  if (_spJob->isTask(Core::Job::ProofImage))
  {
  Task::ProofImage  *pT = new Task::ProofImage("ObliqueProof");

    pT->create(_spJob->numHogels(),_spJob->hogelSize(),3);
    pT->setPathFile(_spJob->outputPath(),"ObliqueProof");
    pT->setScatterType(Task::ProofImage::ObliqueScatter);
    pT->start();

    _imgTaskLst.push_back(pT);
  }

  if (_spJob->isTask(Core::Job::WriteAvi) && !_spJob->isTask(Core::Job::SliceOblique))
  {
  Task::WriteAvi        *pT = new Task::WriteAvi("ObliqueAvi");
  std::filesystem::path dPath(_spJob->outputPath());

    dPath /= "ObliqueAvi";

    pT->setPathFile(dPath,"ObliqueRow");
    pT->start();

    _imgTaskLst.push_back(pT);
  }

  if (_spJob->isTask(Core::Job::WriteImg) && !_spJob->isTask(Core::Job::SliceOblique))
  {
  Task::WriteImg        *pT = new Task::WriteImg("ObliqueImg");
  std::filesystem::path dPath(_spJob->outputPath());

    dPath /= "ObliqueImg";

    pT->setPathFile(dPath,"ObliqueImg_%06dx%06d","png");
    pT->start();

    _imgTaskLst.push_back(pT);
  }

  if (_spJob->isTask(Core::Job::SliceOblique))
  {
  Task::SliceNDice      *pT = new Task::SliceNDice("SliceOblique");
  std::filesystem::path dPath(_spJob->outputPath());

    dPath /= "HogelAvi";

    pT->setPathFile(dPath,"HogelRow");
    pT->init(_spJob->numHogels(),_spJob->hogelSize(),_spJob->sliceMem());
    pT->start();

    _imgTaskLst.push_back(pT);
  }

  if (_spJob->isTask(Core::Job::ProofDepth) && !_spJob->isTask(Core::Job::SliceOblique))
  {
  Task::ProofImage  *pT = new Task::ProofImage("ObliqueDthProof");

    pT->setZNear(_spJob->zNear());
    pT->setZFar(_spJob->zFar());
    pT->create(_spJob->hogelSize(),_spJob->numHogels(),1);
    pT->setPathFile(_spJob->outputPath(),"ObliqueDthProof");
    pT->start();

    _dthTaskLst.push_back(pT);
  }

  if (_spJob->isTask(Core::Job::WriteDepthImg) && !_spJob->isTask(Core::Job::SliceOblique))
  {
  Task::WriteImg        *pT = new Task::WriteImg("ObliqueDthImg");
  std::filesystem::path dPath(_spJob->outputPath());

    dPath /= "ObliqueDth";

    pT->setZNear(_spJob->zNear());
    pT->setZFar(_spJob->zFar());
    pT->setPathFile(dPath,"ObliqueDthImg_%06dx%06d","png");
    pT->start();

    _dthTaskLst.push_back(pT);
  }
}


//---------------------------------------------------------------------
// renderOblique
//---------------------------------------------------------------------
void Oblique::renderOblique(RenderGL::Camera &camera,const glm::vec2 &rA)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (1)
  {
  glm::vec2 r  = glm::radians(rA);
  glm::mat4 mT = glm::shearY3D(_spJob->sceneTransform(),-r[0],r[1]);
 
    _pShader->bindCameraPosition(glm::vec3(camera.view()[3]));
    _pScene->render(camera,_pShader,mT);
  }    
    
  glFinish();
}


//---------------------------------------------------------------------
// renderObliqueSet
//---------------------------------------------------------------------
uint32_t Oblique::renderObliqueSet(void) 
{
glm::ivec2      nH      = _spJob->numHogels();
glm::ivec2      hS      = _spJob->hogelSize();
glm::mat4       mVVT    = _spJob->viewVolumeTransform();
glm::vec3       vC      = glm::vec3(mVVT[3]);
glm::vec3       vT      = glm::vec3(mVVT[1]);
glm::vec3       vP      = vC;
glm::vec3       vD      = vC - vT;
glm::vec3       vU      = vC - glm::vec3(mVVT[2]);
glm::vec2       rT      = glm::vec2(_spJob->fov()) / 2.0f;
glm::vec2       rS      = glm::vec2(_spJob->fov()) / glm::vec2(hS);
glm::vec2       rA      = -rT;
glm::vec2       hD      = glm::vec2(mVVT[0].x,mVVT[2].z) * 0.5f;
float           zF      = _spJob->zFar();
RenderGL::Camera  camera;
glm::ivec2      idx(0);
uint32_t        n(0);

  camera.setOrthographic(-hD.x,hD.x,-hD.y,hD.y,-zF,zF);

  for (;(idx.y < hS.y) && !glfwWindowShouldClose(_pWindow);idx.y++)
  {
  Core::Timer tR;

    tR.start();

    rA.x  = -rT.x;

    std::cout << "Rendering Oblique Row: " << idx.y << std::endl;

    for (idx.x = 0;(idx.x < hS.x) && !glfwWindowShouldClose(_pWindow);idx.x++)
    {
      camera.lookAt(vP,vD,vU);

      renderOblique(camera,rA);
      fetchAndQueue(idx);

      glfwSwapBuffers(_pWindow);
      glfwPollEvents();

      rA.x  += rS.x; 
      n++;
    }

    {
    double t = tR.seconds();
    double c = (double)idx.y / (double)nH.y * 100.0;

      std::cout << "    Row Time: " << t << " seconds";
      std::cout << "    FPS: " << (double)idx.x / t;
      std::cout << "    Complete: " << c << '%' << std::endl;
    }

    rA.y  += rS.y;

    taskSync();
  }

  return n;
}


//---------------------------------------------------------------------
// renderObliquePlane
//---------------------------------------------------------------------
void Oblique::renderObliquePlane(void) 
{
glm::ivec2      nH      = _spJob->numHogels();
uint32_t        n       = 0;
Core::Timer     tH;

  tH.start();

  std::cout << "Starting Oblique Rendering " << std::endl;

  n = renderObliqueSet();

  {
  double t = tH.seconds();

    std::cout << "Completed Oblique Plane Rendering " << std::endl;
    std::cout << "Render Time: " << t << " seconds" << std::endl;
    std::cout << "FPS: " << (double)n / t << std::endl;
  }
}


//---------------------------------------------------------------------
// renderObliqueAndSlice
//---------------------------------------------------------------------
void Oblique::renderObliqueAndSlice(void)
{ 
Task::SliceNDice    *pSnDT  = (Task::SliceNDice *)findTask("SliceOblique",_imgTaskLst);

  if (pSnDT)
  {
  size_t            nR        = pSnDT->numSliceRows(); 
  glm::ivec2        nH        = _spJob->numHogels();
  double            FPS       = 0;
  uint32_t          n         = 0;
  Core::Timer	      tH;

    if (nR == 0)
      nR = nH.y;

    for (size_t i = 0;(i < (size_t)nH.y) && !glfwWindowShouldClose(_pWindow);i += nR)
    {
      if ((i + nR) >= (size_t)nH.y)
        nR = (size_t)nH.y - i;

      std::cout << "Slicing Rows: " << i << " to " << i + nR << std::endl;

      pSnDT->setSliceRange(i,nR);

      n += renderObliqueSet();

      pSnDT->writeAVIs();
    }

    {
    double t = tH.seconds();

      std::cout << "Completed Oblique Slice and Dice Rendering " << std::endl;
      std::cout << "Render & Slice n Dice Time: " << t << " seconds" << std::endl;
      std::cout << "FPS: " << (double)n / t << std::endl;
    }
  }
}


//---------------------------------------------------------------------
// exec
//---------------------------------------------------------------------
int Oblique::exec(void) 
{
glm::ivec2  nH  = _spJob->numHogels();

  glViewport(0,0,nH.x,nH.y);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glClearColor(0,0,0,0);
  glPixelStorei(GL_PACK_ALIGNMENT,1);

  bindLight();

  if (_spJob->isTask(Lf::Core::Job::SliceOblique))
    renderObliqueAndSlice();
  else
    renderObliquePlane();

  return 0;
}


//---------------------------------------------------------------------
// init
//---------------------------------------------------------------------
int Oblique::init(Core::SpJob &spJob) 
{
int rc  = Executor::init(spJob);

  if (rc == 0)
  {
  glm::ivec2      nH      = spJob->numHogels();

    glfwMakeContextCurrent(_pWindow);
    glfwSetWindowSize     (_pWindow,nH.x,nH.y);

    if (spJob->isTask(Lf::Core::Job::SliceOblique))
      glfwSetWindowTitle    (_pWindow,"Lightfield - Obliques & Slice n Dice");
    else
      glfwSetWindowTitle    (_pWindow,"Lightfield - Obliques");
  }

  return rc;
}


//---------------------------------------------------------------------
// Oblique
//---------------------------------------------------------------------
Oblique::Oblique(void) : Executor()
{
}


//---------------------------------------------------------------------
// ~Oblique
//---------------------------------------------------------------------
Oblique::~Oblique()
{
}

