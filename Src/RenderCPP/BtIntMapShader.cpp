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

// BtIntMapShader.cpp
// Thomas Burnett


//---------------------------------------------------------------------
// Includes
// System
#include <assert.h>
#include <fstream>
#include <iostream>

// 3rdPartyLibs
#include <glm/glm.hpp>
#include <glm/ext.hpp>

// Lightfield
#include "RenderCPP/BtIntMapShader.h"

using namespace Lf;
using namespace RenderCPP;
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// clear
//---------------------------------------------------------------------
void BtIntMapShader::clear(void)
{
  BtBasicShader::clear();

  {
  glm::vec4   vD = glm::vec4(0.0f,1.0f,0.0f,0.0f);
  glm::vec3   vR = glm::normalize(glm::vec3(1.0f,0.0f,_pHogelPlane->aspectRatio()));
  glm::mat4   mR = glm::rotate(_pHogelPlane->fov() * 0.5f,vR);
  glm::vec3   vA = glm::normalize(mR * vD);

    _frustumDirs[0] = glm::vec3( vA.x,vA.y, vA.z);
    _frustumDirs[1] = glm::vec3( vA.x,vA.y,-vA.z);
    _frustumDirs[2] = glm::vec3(-vA.x,vA.y, vA.z);
    _frustumDirs[3] = glm::vec3(-vA.x,vA.y,-vA.z);
    _vN             = vD;
  }

 // printf("fD0   %f,%f,%f\n",_frustumDirs[0].x,_frustumDirs[0].y,_frustumDirs[0].z);
 // printf("fD1   %f,%f,%f\n",_frustumDirs[1].x,_frustumDirs[1].y,_frustumDirs[1].z);
 // printf("fD2   %f,%f,%f\n",_frustumDirs[2].x,_frustumDirs[2].y,_frustumDirs[2].z);
 // printf("fD3   %f,%f,%f\n",_frustumDirs[3].x,_frustumDirs[3].y,_frustumDirs[3].z);
 // printf("vN    %f,%f,%f\n",_vN.x,_vN.y,_vN.z);

}


//---------------------------------------------------------------------
// determine
//---------------------------------------------------------------------
void BtIntMapShader::determine(void)
{
  _mTVoli = glm::inverse(_mVol) * _mT;
  _objN++;
}


//---------------------------------------------------------------------
// determineHogelPlaneIndices
//---------------------------------------------------------------------
bool BtIntMapShader::determineHogelPlaneIndices(const Vtx3 *pV0,const Vtx3 *pV1,const Vtx3 *pV2,
                                                glm::ivec2 *pIMin,glm::ivec2 *pIMax)
{
bool        s  = false;
glm::vec3   v0 = _mTVoli * glm::vec4(pV0->_V,1);
glm::vec3   v1 = _mTVoli * glm::vec4(pV1->_V,1);
glm::vec3   v2 = _mTVoli * glm::vec4(pV2->_V,1);
float       t0 = 1.0f;
float       t1 = 1.0f;
float       t2 = 1.0f;
glm::vec2   iMax(-std::numeric_limits<float>::max());
glm::vec2   iMin( std::numeric_limits<float>::max());

  if (v0.y > 0.0f)
    t0 = -t0;
  if (v1.y > 0.0f)
    t1 = -t1;
  if (v1.y > 0.0f)
    t1 = -t1;

  // for each frustum edge
  for (uint32_t i = 0;i < 4;i++)
  {
  float     d   = 0;
  glm::vec3 vD;
  glm::vec3 vN;

    // create a ray at the vertex heading in the direction of the frustum point
    // intersect it against the clipper hogel plane
    vD = t0 * _frustumDirs[i];
    vN = t0 * _vN;
    if (glm::intersectRayPlane(v0,vD,_vC,vN,d))
    {
    glm::vec3   vI  = v0 + (vD * d);
    glm::vec2   vI2(vI.x,vI.z);

      iMin = glm::min(iMin,vI2);
      iMax = glm::max(iMax,vI2);

      s = true;
    }
    
    vD = t1 * _frustumDirs[i];
    vN = t1 * _vN;
    if (glm::intersectRayPlane(v1,vD,_vC,vN,d))
    {
    glm::vec3   vI  = v1 + (vD * d);
    glm::vec2   vI2(vI.x,vI.z);

      iMin = glm::min(iMin,vI2);
      iMax = glm::max(iMax,vI2);

      s = true;
    }

    vD = t1 * _frustumDirs[i];
    vN = t1 * _vN;
    if (glm::intersectRayPlane(v2,vD,_vC,vN,d))
    {
    glm::vec3   vI  = v2 + (vD * d);
    glm::vec2   vI2(vI.x,vI.z);

      iMin = glm::min(iMin,vI2);
      iMax = glm::max(iMax,vI2);

      s = true;
    }
  }

  if (s)  // this is always likely true.....
  {  
  glm::ivec2 v0 = _pHogelPlane->hogelIndexFromNormalizedPlanePosition(iMin);
  glm::ivec2 v1 = _pHogelPlane->hogelIndexFromNormalizedPlanePosition(iMax);
  glm::ivec2 nH = _pHogelPlane->numHogels() - 1;

    *pIMin = glm::min(v0,v1);
    *pIMax = glm::max(v0,v1);

    *pIMin += glm::ivec2(-1);
    *pIMax += glm::ivec2( 1);

    *pIMin = glm::clamp(*pIMin,glm::ivec2(0),nH);
    *pIMax = glm::clamp(*pIMax,glm::ivec2(0),nH);
  }

  return s;
}


//---------------------------------------------------------------------
// render
//---------------------------------------------------------------------
void BtIntMapShader::render(const Vtx3 *pV0,const Vtx3 *pV1,const Vtx3 *pV2)
{
glm::ivec2 iMin;
glm::ivec2 iMax;

  if (determineHogelPlaneIndices(pV0,pV1,pV2,&iMin,&iMax) == true) // isVisible
  {
  uint32_t   hId = _pHogelPlane->hogelId(glm::ivec2(0));
  HogelData *pHD = &_hogelDataLst[hId];

    if (checkState(hId))
      _clipperLst[hId].set(pHD->_mMVP);

    {
    float c = _clipperLst[hId].classifyHogelPlane(pV0,pV1,pV2);

      BtBasicShader::render(pV0,pV1,pV2,iMin,iMax,c);
    }
  }
}


//---------------------------------------------------------------------
// BtIntMapShader
//---------------------------------------------------------------------
BtIntMapShader::BtIntMapShader(const char *pName) : BtBasicShader(pName),
                                                    _mTVoli(),
                                                    _vC(),
                                                    _vN(),
                                                    _frustumDirs()
{
}


//---------------------------------------------------------------------
// ~BtIntMapShader
//---------------------------------------------------------------------
BtIntMapShader::~BtIntMapShader()
{
}
