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

// BowTie.cpp 
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

#include "MvPU/BowTie.h"
#include "RenderCPP/BtBasicShader.h"
#include "RenderCPP/BtIntMapShader.h"

using namespace MvPU;
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// exec
//---------------------------------------------------------------------
int BowTie::exec(void) 
{
int               rc    = 0;
glm::ivec2        nH    = _spJob->numHogels();
glm::ivec2        hS    = _spJob->hogelSize();
float             fov   = _spJob->fov();
uint32_t          n     = nH.x * nH.y;
float             a     = (float)hS.x / (float)hS.y;
glm::mat4         mVol  = _spJob->viewVolumeTransform();
glm::mat4         mTs   = _spJob->sceneTransform();
double            tT    = 0;
Lf::Core::Timer       rTimer;
Lf::HogelDef::Camera  camera;

  std::cout << "The BowTie algorithm does not produce row statistics, please be patient...." << std::endl;
  std::cout << "Begin " << _spJob->algorithm() << " BowTie Rendering" << std::endl;

  camera.setBowTiePerspective(fov,a); 

  _pShader->bindFrameBuffer(_pFrameBuffer);
  _pShader->bindViewport(glm::vec2(0),glm::vec2(hS));
  _pShader->bindProjection(camera.projection());
  _pShader->bindVolume(mVol);
  _pShader->bindHogelPlane(_pHogelPlane);
  _pShader->bindCullFace(_spJob->isCullFace());

  if (_spJob->hasLight())
  {
    _pShader->bindLight(_spJob->lightPosition(),
                        _spJob->lightAmbient(),
                        _spJob->lightDiffuse(),
                        _spJob->lightSpecular(),
                        _spJob->lightAttenuation());
  }

  _pShader->clear();

  rTimer.start();
  {
    _pScene->render(camera,_pShader,mTs);
  }
  rTimer.stop();

  _rSec = rTimer.seconds();
 
  {
    _rFps =(double)_pHogelPlane->maxHogels() / _rSec;

    std::cout << "-----------------------------------" << std::endl;
    std::cout << "Finished "  << _spJob->algorithm() <<  " BowTie Rendering" << std::endl;
    std::cout << "Render Time: " << _rSec << std::endl;
    std::cout << " Render FPS: " << _rFps << std::endl;
    std::cout << std::endl;
  }

  return rc;
}


//---------------------------------------------------------------------
// init
//---------------------------------------------------------------------
int BowTie::init(Lf::MvPU::SpJob &spJob) 
{
int   rc = Executor::init(spJob);
 
  if (rc == 0)
  {
    if (_spJob->algorithmType() == Lf::MvPU::Job::Basic)
      _pShader      = new Lf::RenderCPP::BtBasicShader("BtBasic");
    else if (_spJob->algorithmType() == Lf::MvPU::Job::IntMap)
      _pShader      = new Lf::RenderCPP::BtIntMapShader("BtIntMap");
  }

  return rc;
}


//---------------------------------------------------------------------
// destroy
//---------------------------------------------------------------------
void BowTie::destroy(void) 
{
  Executor::destroy();

  delete _pShader;
}


//---------------------------------------------------------------------
// BowTie
//---------------------------------------------------------------------
BowTie::BowTie(void) : Executor()
{
  _name = "Bt";
}


//---------------------------------------------------------------------
// ~BowTie
//---------------------------------------------------------------------
BowTie::~BowTie()
{

}

