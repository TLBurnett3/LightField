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

// BtBasicShader.cpp
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
#include "RenderCPP/BtBasicShader.h"

using namespace Lf;
using namespace RenderCPP;
//---------------------------------------------------------------------




//---------------------------------------------------------------------
// render
//---------------------------------------------------------------------
void BtBasicShader::render(const Vtx3 *pV0,const Vtx3 *pV1,const Vtx3 *pV2,
                           const glm::ivec2 &iMin,const glm::ivec2 &iMax,
                           const float c)
{
glm::ivec2 idx;
  
  for (idx.y = iMin.y;idx.y <= iMax.y;idx.y++)
  {
    for (idx.x = iMin.x;idx.x <= iMax.x;idx.x++)
    {
    uint32_t   hId = _pHogelPlane->hogelId(idx);
    HogelData *pHD = &_hogelDataLst[hId];

      if (checkState(hId))
        _clipperLst[hId].set(pHD->_mMVP);

      _pFrameBuffer->setCurrentFrameBuffer(hId);
      
      // back frustum
      if (1 && (c <= 0))
      {
        BtBasicShader::loadVtxLst(_vtxLstA,pV0,pV1,pV2); 

        {
        uint32_t n         = 3;
        Vtx3     *pVtxLst  = _clipperLst[hId].clip(BtClipper::Back,_vtxLstA,_vtxLstB,&n);

          if (n > 2)
          {
          bool keep = true;

            BtBasicShader::calculateCoordinates(pVtxLst,_crdLst,n,pHD);

            if (_cullFace)
              keep = Shader::cullPolygon(_crdLst,n);

            if (keep)
            {
              for (uint32_t j = 1;j < n - 1;j++)
                rasterize(_crdLst + 0,_crdLst + j + 0,_crdLst + j + 1);
            }
          }
        }
      }
        
      // front frustum
      if (1 && (c >= 0))
      {
        BtBasicShader::loadVtxLst(_vtxLstA,pV0,pV1,pV2); 
         
        {
        uint32_t n         = 3;
        Vtx3     *pVtxLst  = _clipperLst[hId].clip(BtClipper::Front,_vtxLstA,_vtxLstB,&n);

          if (n > 2)
          {
          bool keep = true;

            BtBasicShader::calculateCoordinates(pVtxLst,_crdLst,n,pHD);

            if (_cullFace)
              keep = Shader::cullPolygon(_crdLst,n);

            if (keep)
            {
              for (uint32_t j = 1;j < n - 1;j++)
                rasterize(_crdLst + 0,_crdLst + j + 0,_crdLst + j + 1);
            }    
          }
        }
      }
    }
  }
}


//---------------------------------------------------------------------
// render
//---------------------------------------------------------------------
void BtBasicShader::render(const Vtx3 *pV0,const Vtx3 *pV1,const Vtx3 *pV2)
{
uint32_t   hId = _pHogelPlane->hogelId(glm::ivec2(0));
HogelData *pHD = &_hogelDataLst[hId];

  if (checkState(hId))
    _clipperLst[hId].set(pHD->_mMVP);
    
  {
  float      c    = _clipperLst[hId].classifyHogelPlane(pV0,pV1,pV2);
  glm::ivec2 iMin = glm::ivec2(0);
  glm::ivec2 iMax = _pHogelPlane->numHogels();

    render(pV0,pV1,pV2,iMin,(iMax - 1),c);
  }
}


//---------------------------------------------------------------------
// BtBasicShader
//---------------------------------------------------------------------
BtBasicShader::BtBasicShader(const char *pName) : BtShader(pName)
{
}


//---------------------------------------------------------------------
// ~BtBasicShader
//---------------------------------------------------------------------
BtBasicShader::~BtBasicShader()
{
}
