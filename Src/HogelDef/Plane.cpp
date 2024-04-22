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

// HogelDef.cpp 
// Thomas Burnett


//---------------------------------------------------------------------
// Includes
// System
#include <iostream>

// 3rdPartyLibs
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/intersect.hpp>

// HogelDef
#include "HogelDef/Plane.h"

using namespace Lf;
using namespace HogelDef;
//---------------------------------------------------------------------


//---------------------------------------------------------------------



/*
//---------------------------------------------------------------------
// btHogelViewTransform
//---------------------------------------------------------------------
glm::mat4 PlanebtHogelViewTransform(const uint32_t id,const glm::mat4 &mT)
{
glm::mat4   mH    = mT * _hglLst[id]._mH;
glm::vec3   vE    = mH[3];
glm::vec3   vD    = mH[2];
glm::vec3   vU    = mH[1];
//glm::mat4   mV    = glm::lookAt(vE,vE + vD,vU);

glm::vec3   vDh = glm::normalize(vD);
glm::vec3   vRh = glm::normalize(glm::cross(vDh, vU));
glm::vec3   vUh = glm::cross(vRh, vDh);
glm::vec3   vEh = vE;
glm::mat4   mV  = glm::mat4(-vRh.x, vUh.x, -vDh.x, 0,
                            -vRh.y, vUh.y, -vDh.y, 0,
                            -vRh.z, vUh.z, -vDh.z, 0,
                            glm::dot(vRh, vEh), -glm::dot(vUh, vEh), glm::dot(vDh, vEh), 1);

  return mV;
}*/


//---------------------------------------------------------------------
// btHogelViewTransform
//---------------------------------------------------------------------
glm::mat4 Plane::btHogelViewTransform(const uint32_t id,const glm::mat4 &mT)
{
glm::mat4   mH = mT * _hglLst[id]._mH;
glm::vec3   vD = glm::normalize(glm::vec3(mH[2]));
glm::vec3   vR = glm::normalize(glm::cross(vD,glm::vec3(mH[1])));
glm::vec3   vU = glm::cross(vR,vD);
glm::vec3   vE = mH[3];
glm::mat4   mV = glm::mat4(-vR.x,           vU.x,             -vD.x,           0,   // Column 0
                           -vR.y,           vU.y,             -vD.y,           0,   // Column 1
                           -vR.z,           vU.z,             -vD.z,           0,   // Column 2
                           glm::dot(vR,vE), -glm::dot(vU,vE), glm::dot(vD,vE), 1);  // Column 3

  return mV;
}


//---------------------------------------------------------------------
// dfFrontViewFrustum
//---------------------------------------------------------------------
glm::mat4 Plane::dfFrontViewFrustum(const glm::vec3 &vE,const glm::vec3 &vD,const glm::vec3 &vU)
{
glm::vec3   vDh = glm::normalize(vD);
glm::vec3   vRh = glm::normalize(glm::cross(vDh, vU));
glm::vec3   vUh = glm::cross(vRh, vDh);
glm::vec3   vEh = vE;
glm::mat4   mV = glm::mat4(-vRh.x, vUh.x, -vDh.x, 0,
                           -vRh.y, vUh.y, -vDh.y, 0,
                           -vRh.z, vUh.z, -vDh.z, 0,
                           glm::dot(vRh, vEh), -glm::dot(vUh, vEh), glm::dot(vDh, vEh), 1);

  return mV;
}


//---------------------------------------------------------------------
// dfBackViewFrustum
//---------------------------------------------------------------------
glm::mat4 Plane::dfBackViewFrustum(const glm::vec3 &vE,const glm::vec3 &vD,const glm::vec3 &vU)
{
glm::vec3   vDh = glm::normalize(vD);
glm::vec3   vRh = glm::normalize(glm::cross(vDh, vU));
glm::vec3   vUh = glm::cross(vRh, vDh);
glm::vec3   vEh = vE;
glm::mat4   mV = glm::mat4(vRh.x, vUh.x, -vDh.x, 0,
                           vRh.y, vUh.y, -vDh.y, 0,
                           vRh.z, vUh.z, -vDh.z, 0,
                           -glm::dot(vRh, vEh), -glm::dot(vUh, vEh), glm::dot(vDh, vEh), 1);

  return mV;
}


//---------------------------------------------------------------------
// dfHogelViewTransforms
//---------------------------------------------------------------------
void Plane::dfHogelViewTransforms(const uint32_t id,glm::mat4 &mVf,glm::mat4 &mVb,const glm::mat4 &mT)
{
glm::mat4   mH    = mT * _hglLst[id]._mH;
glm::vec3   vE    = mH[3];
glm::vec3   vD    = mH[2];
glm::vec3   vU    = mH[1];
glm::vec3   vT    = vD * 0.001f;

  mVf = dfFrontViewFrustum(vE - vT, vD, vU);
  mVb = dfBackViewFrustum (vE + vT,-vD,-vU);
}


//---------------------------------------------------------------------
// btCameraTransform
//---------------------------------------------------------------------
glm::mat4 Plane::btCameraTransform(const uint32_t id,const glm::mat4 &mT)
{
glm::mat4   mH    = mT * _hglLst[id]._mH;

  return mH;
}


//---------------------------------------------------------------------
// radianceImageTransform
//---------------------------------------------------------------------
glm::mat4 Plane::radianceImageTransform(const glm::mat4 &mT)
{
glm::mat4 mR  = mT * hogelTransform(glm::vec3(0));

  return mR;
}


//---------------------------------------------------------------------
// radianceViewTransform
//---------------------------------------------------------------------
glm::mat4 Plane::radianceViewTransform(const glm::mat4 &mT)
{
glm::mat4 mR  = mT * hogelTransform(glm::vec3(0));
glm::vec3 vD  = glm::normalize(glm::vec3(mR[2]));
glm::vec3 vR  = glm::normalize(glm::cross(vD,glm::vec3(mR[1])));
glm::vec3 vU  = glm::cross(vR,vD);
glm::vec3 vE  = mR[3];
glm::mat4 mV  = glm::mat4(-vR.x,           vU.x,             -vD.x,           0,   // Column 0
                          -vR.y,           vU.y,             -vD.y,           0,   // Column 1
                          -vR.z,           vU.z,             -vD.z,           0,   // Column 2
                          glm::dot(vR,vE), -glm::dot(vU,vE), glm::dot(vD,vE), 1);  // Column 3 

  return mV;
}


//---------------------------------------------------------------------
// create
//---------------------------------------------------------------------
int Plane::create(const glm::ivec2 &nH,const glm::vec2 &dR,const glm::vec2 &hP)
{
int       rc = 0;
uint32_t  n  = nH.x * nH.y;

  _nH     = nH;
  _hS     = dR;
  _hP     = hP;
  _radDim = glm::vec2(nH) * hP;

  {
  glm::vec2  hW  = hP * 0.5f;
  glm::ivec2 idx(0);
  float      d   = glm::max(_radDim.x,_radDim.y);

    _vMinE  = glm::vec3(-_radDim.x * 0.5f,0.0f,-_radDim.y * 0.5f) / d;
    _vMaxE  = glm::vec3( _radDim.x * 0.5f,0.0f, _radDim.y * 0.5f) / d;
    _vHWE   = (_vMaxE - _vMinE) * 0.5f;

    for (idx.y = 0;idx.y < nH.y;idx.y++)
    {
      for (idx.x = 0;idx.x < nH.x;idx.x++)
      {
      glm::vec2 vC = (glm::vec2(idx) * hP) + hW;
      glm::vec2 vP = (vC / d) - 0.5f;
      glm::mat4 mH = hogelTransform(glm::vec3(vP.x,0.0f,-vP.y));

        _hglLst.emplace_back(idx,vC,mH);
      }
    }
  }

  return 0;
}


//---------------------------------------------------------------------
// print
//---------------------------------------------------------------------
void Plane::print(void)
{
  printf("%20s: %d x %d\n","Num Hogels",_nH.x,_nH.y);
  printf("%20s: %f x %f\n","Hogel Full Width",_hS.x,_hS.y);
  printf("%20s: %f x %f\n","Hogel Pitch",_hP.x,_hP.y);
  printf("%20s: %f x %f\n","Rad. Img. Size",_radDim.x,_radDim.y);
  printf("%20s: %f\n","Field of View",_fov);

  printf("\nHogels\n");
  printf("------\n");

  for (size_t i = 0;i < _hglLst.size();i++)
  {
  Hogel     *pH = &_hglLst[i];
  glm::vec3 vP  = pH->_mH[3];

    printf("%04zu:  %20s: (%f,%f)   (%f,%f,%f)  \n",i,"Center",pH->_vC.x,pH->_vC.y,
                                                             vP.x,vP.y,vP.z);
  }
}


/*

//---------------------------------------------------------------------
// setPerspective
//---------------------------------------------------------------------
void Plane::setPerspective(const float &fov) 
{
float tanHalfFovy = tan(glm::radians(fov) / 2.0f);

  _fov = fov;

	_mPbt = glm::mat4(0);
	_mPbt[0][0] = 1.0f / tanHalfFovy;
	_mPbt[1][1] = 1.0f / tanHalfFovy;
	_mPbt[2][3] = -1.0f;
	_mPbt[3][2] = -1.0f;

  _mPdf = glm::perspective(glm::radians(fov),1.0f,0.001f,10000.0f);
}
*/


//---------------------------------------------------------------------
// Plane
//---------------------------------------------------------------------
Plane::Plane(void): _hglLst(),
                          _nH(0),
                          _hS(0),
                          _hP(0),
                          _radDim(0),
                          _fov(0),
                          _vMinE(0),
                          _vMaxE(0),
                          _vHWE(0)
{
}


//---------------------------------------------------------------------
// ~Plane
//---------------------------------------------------------------------
Plane::~Plane()
{
}

