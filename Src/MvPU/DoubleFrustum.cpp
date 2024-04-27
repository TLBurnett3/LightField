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

// Lightfield
#include "MvPU/DoubleFrustum.h"
#include "HogelDef/Camera.h"

using namespace MvPU;
//---------------------------------------------------------------------



//---------------------------------------------------------------------
// exec
//---------------------------------------------------------------------
int DoubleFrustum::exec(void) 
{
int               rc    = 0;
glm::ivec2        nH    = _spJob->numHogels();
glm::ivec2        hS    = _spJob->hogelSize();
float             fov   = _spJob->fov();
uint32_t          n     = nH.x * nH.y;
float             a     = (float)hS.x / (float)hS.y;
float             zN    = _spJob->zNear();
float             zF    = _spJob->zFar();
glm::mat4         mVol  = _spJob->viewVolumeTransform();
glm::mat4         mTs   = _spJob->sceneTransform();
uint32_t          i     = 0;
Lf::Core::Timer       rTimer;
Lf::HogelDef::Camera  camera;
glm::ivec2        idx(0);

  std::cout << "Begin Double Frustum Rendering" << std::endl;

  camera.setPerspective(fov,a,zN,zF);

  _pShader->bindFrameBuffer(_pFrameBuffer);
  _pShader->bindViewport(glm::vec2(0),glm::vec2(hS));
  _pShader->bindCullFace(_spJob->isCullFace());
  _pShader->bindProjection(camera.projection());

  if (_spJob->hasLight())
  {
    _pShader->bindLight(_spJob->lightPosition(),
                        _spJob->lightAmbient(),
                        _spJob->lightDiffuse(),
                        _spJob->lightSpecular(),
                        _spJob->lightAttenuation());
  }

  for (idx.y = 0;idx.y < nH.y;idx.y++)
  {  
    rTimer.start();

    for (idx.x = 0;idx.x < nH.x;idx.x++)
    {
    glm::mat4 mH    = mVol * _pHogelPlane->hogel(i)->_mH;
    glm::vec3 vE    = mH[3];
    glm::vec3 vD    = mH[2];
    glm::vec3 vU    = mH[1];
    glm::vec3 vT    = vD * zN;

      _pFrameBuffer->setCurrentFrameBuffer(i);

      // Back Frustum
      if (1)
      {
        camera.setBackFrustum(vE + vT,-vD,vU);

        _pShader->bindNormalScale(1.0f);
        _pShader->bindDepthScale(-1.0f);
        _pShader->bindView(camera.view());

        _pScene->render(camera,_pShader,mTs);
      }

      // Front Frustum
      if (1)
      {
        camera.setFrontFrustum(vE - vT,vD,-vU);

        _pShader->bindNormalScale(-1.0f);
        _pShader->bindDepthScale(1.0f);
        _pShader->bindView(camera.view());

        _pScene->render(camera,_pShader,mTs);
      }

      i++;    
    }
    rTimer.stop();

    {
    double t    = rTimer.seconds();
    double fps  = (double)nH.x / t;

      std::cout << "Completed Row: " << idx.y << "       Seconds: " << t << "      FPS: " << fps << std::endl; 
      _rSec += t;
    }
  }

  {
    _rFps =(double)_pHogelPlane->maxHogels() / _rSec;

    std::cout << "-----------------------------------" << std::endl;
    std::cout << "Finished Double Frustum Rendering" << std::endl;
    std::cout << "Render Time: " << _rSec << std::endl;
    std::cout << " Render FPS: " << _rFps << std::endl;
    std::cout << std::endl;
  }

  return rc;
}


//---------------------------------------------------------------------
// init
//---------------------------------------------------------------------
int DoubleFrustum::init(Lf::MvPU::SpJob &spJob) 
{
int   rc = Executor::init(spJob);
 
  if (rc == 0)
  {
    _pShader      = new Lf::RenderCPP::Shader("Default");
  }

  return rc;
}

//---------------------------------------------------------------------
// destroy
//---------------------------------------------------------------------
void DoubleFrustum::destroy(void) 
{
  Executor::destroy();

  delete _pShader;
}


//---------------------------------------------------------------------
// DoubleFrustum
//---------------------------------------------------------------------
DoubleFrustum::DoubleFrustum(void) : Executor(),
                                     _pShader(0)

{
  _name = "Df";
}


//---------------------------------------------------------------------
// ~DoubleFrustum
//---------------------------------------------------------------------
DoubleFrustum::~DoubleFrustum()
{

}

