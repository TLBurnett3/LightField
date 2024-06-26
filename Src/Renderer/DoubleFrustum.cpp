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

// DoubleFrustum.cpp 
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
#include "Renderer/DoubleFrustum.h"
#include "Core/Timer.h"
#include "Tasks/ProofImage.h"
#include "Tasks/WriteAvi.h"
#include "Tasks/WriteImg.h"
#include "Tasks/SliceNDice.h"

using namespace Lf;
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// fetchAndQueue
//---------------------------------------------------------------------
void DoubleFrustum::fetchAndQueue(glm::ivec2 idx)
{
glm::ivec2  hS      = _spJob->hogelSize();

  if (_imgTaskLst.size())
  {
  TaskList::iterator        ii    = _imgTaskLst.begin();
  TaskList::iterator        iEnd  = _imgTaskLst.end();
  Task::Base::SpImg         spImg = std::make_shared<std::pair<cv::Mat,glm::ivec2>>();

    spImg->first.create(hS.y,hS.x,CV_8UC3);
    spImg->second = idx;

    glReadBuffer(GL_BACK);
    glReadPixels(0,0,(GLsizei)hS.x,(GLsizei)hS.y,GL_BGR,GL_UNSIGNED_BYTE,spImg->first.data); 
    
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

    spImg->first.create(hS.y,hS.x,CV_32FC1);
    spImg->second = idx;

    glReadBuffer(GL_BACK);
    glReadPixels(0,0,(GLsizei)hS.x,(GLsizei)hS.y,GL_DEPTH_COMPONENT,GL_FLOAT,spImg->first.data);

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
void DoubleFrustum::createTasks(void)
{
  if (_spJob->isTask(Core::Job::ProofImage))
  {
  Task::ProofImage  *pT = new Task::ProofImage("HogelProof");

    pT->create(_spJob->numHogels(),_spJob->hogelSize(),3);
    pT->setPathFile(_spJob->outputPath(),"HogelProof");
    pT->start();

    _imgTaskLst.push_back(pT);
  }

  if (_spJob->isTask(Core::Job::WriteAvi))
  {
  Task::WriteAvi        *pT = new Task::WriteAvi("HogelAvi");
  std::filesystem::path dPath(_spJob->outputPath());

    dPath /= "HogelAvi";

    pT->setPathFile(dPath,"HogelRow");
    pT->start();

    _imgTaskLst.push_back(pT);
  }

  if (_spJob->isTask(Core::Job::WriteImg))
  {
  Task::WriteImg        *pT = new Task::WriteImg("HogelImg");
  std::filesystem::path dPath(_spJob->outputPath());

    dPath /= "HogelImg";

    pT->setPathFile(dPath,"HogelImg_%06dx%06d","png");
    pT->start();

    _imgTaskLst.push_back(pT);
  }

  if (_spJob->isTask(Core::Job::ProofDepth))
  {
  Task::ProofImage  *pT = new Task::ProofImage("DthProof");

    pT->setZNear(_spJob->zNear());
    pT->setZFar(_spJob->zFar());
    pT->create(_spJob->numHogels(),_spJob->hogelSize(),1);
    pT->setPathFile(_spJob->outputPath(),"DthProof");
    pT->start();

    _dthTaskLst.push_back(pT);
  }

  if (_spJob->isTask(Core::Job::WriteDepthImg))
  {
  Task::WriteImg        *pT = new Task::WriteImg("DthImg");
  std::filesystem::path dPath(_spJob->outputPath());

    dPath /= "HogelDth";

    pT->setZNear(_spJob->zNear());
    pT->setZFar(_spJob->zFar());
    pT->setPathFile(dPath,"HogelDthImg_%06dx%06d","png");
    pT->start();

    _dthTaskLst.push_back(pT);
  }
}


//---------------------------------------------------------------------
// createHogelPlane
//---------------------------------------------------------------------
void DoubleFrustum::createHogelPlane(void)
{
glm::ivec2  nH    = _spJob->numHogels();
glm::ivec2  hS    = _spJob->hogelSize();
float       fov   = _spJob->fov();

  _pHogelPlane = new Lf::HogelDef::Plane();

  _pHogelPlane->create(nH,hS,hS,fov);
}


//---------------------------------------------------------------------
// render
//---------------------------------------------------------------------
void DoubleFrustum::render(HogelDef::Camera &camera,Lf::HogelDef::Hogel *pH)
{
float     zN    = _spJob->zNear();
glm::mat4 mH    = _spJob->viewVolumeTransform() * pH->_mH;
glm::vec3 vE    = mH[3];
glm::vec3 vD    = glm::normalize(mH[2]);
glm::vec3 vU    = glm::normalize(mH[1]);
glm::vec3 vT    = vD * zN;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  _pShader->use();
  _pShader->bindTextureSampler(0);

  // back frustum, away from viewer into the display
  if (1)
  {
    glDepthRange(0.5f,1.0f);

    camera.setBackFrustum(vE + vT,-vD,vU);

    _pShader->bindNormalScale(1.0f);
    _pShader->bindCameraPosition(vE);
    _pScene->render(&camera,_pShader,_spJob->sceneTransform());

    glFlush();
  }

  // front frustum, toward the viewer out of the display
  if (1)
  {
    glDepthRange(0.5f,0.0f);

    camera.setFrontFrustum(vE - vT,vD,-vU);

    _pShader->bindNormalScale(-1.0f);
    _pShader->bindCameraPosition(vE);
    _pScene->render(&camera,_pShader,_spJob->sceneTransform());
  }   

  glFinish();
}


//---------------------------------------------------------------------
// exec
//---------------------------------------------------------------------
int DoubleFrustum::exec(void) 
{
int               rc      = 0;
glm::ivec2        nH      = _spJob->numHogels();
glm::ivec2        hS      = _spJob->hogelSize();
glm::ivec2        idx(0);
uint32_t          n(0);
Core::Timer       tH;
HogelDef::Camera  camera;

  bindLight();

  tH.start();

  std::cout << "Starting Double Frustum Hogel Rendering " << std::endl;

  camera.setPerspective(_spJob->fov(),(float)hS.x/(float)(hS.y),_spJob->zNear(),_spJob->zFar());

  glViewport(0,0,hS.x,hS.y);
  glEnable(GL_DEPTH_TEST);

  glFrontFace(GL_CCW);
  glCullFace(GL_BACK);

  if (_spJob->isCullFace())  
    glEnable(GL_CULL_FACE);

  glClearColor(0,0,0,0);
  glPixelStorei(GL_PACK_ALIGNMENT,1);

  for (;(idx.y < nH.y) && !glfwWindowShouldClose(_pWindow);idx.y++)
  {
  Core::Timer tR;

    tR.start();

    std::cout << "Rendering Hogel Row: " << idx.y << std::endl;

    for (idx.x = 0;(idx.x < nH.x) && !glfwWindowShouldClose(_pWindow);idx.x++)
    {
    Lf::HogelDef::Hogel  *pH = _pHogelPlane->hogel(idx);

      render(camera,pH);
      fetchAndQueue(idx);

      glfwSwapBuffers(_pWindow);
      glfwPollEvents();

      n++;
    }

    {
    double t = tR.seconds();
    double c = (double)idx.y / (double)nH.y * 100.0;

      std::cout << "    Row Time: " << t << " seconds";
      std::cout << "    FPS: " << (double)idx.x / t;
      std::cout << "    Complete: " << c << '%' << std::endl;
    }

    taskSync();
  }

  {
  double t = tH.seconds();

    std::cout << "Completed Double Frustum Hogel Rendering " << std::endl;
    std::cout << "Render Time: " << t << " seconds" << std::endl;
    std::cout << "FPS: " << (double)n / t << std::endl;
  }

  return rc;
}


//---------------------------------------------------------------------
// init
//---------------------------------------------------------------------
int DoubleFrustum::init(Core::SpJob &spJob) 
{
int rc  = Executor::init(spJob);

  if (rc == 0)
  {
  glm::ivec2      hS      = _spJob->hogelSize();

    glfwMakeContextCurrent(_pWindow);
    glfwSetWindowSize     (_pWindow,hS.x,hS.y);
    glfwSetWindowTitle    (_pWindow,"Lightfield - Double Frustum");

    createHogelPlane();
  }

  return rc;
}


//---------------------------------------------------------------------
// DoubleFrustum
//---------------------------------------------------------------------
DoubleFrustum::DoubleFrustum(void) : Executor(),
                                     _pHogelPlane(0)
{
}


//---------------------------------------------------------------------
// ~DoubleFrustum
//---------------------------------------------------------------------
DoubleFrustum::~DoubleFrustum()
{
  delete _pHogelPlane;
}

