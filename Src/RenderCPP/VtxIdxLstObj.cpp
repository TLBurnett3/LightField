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

// VtxIdxLstObj.cpp 
// Thomas Burnett


//---------------------------------------------------------------------
// Includes
// System
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

// 3rdPartyLibs
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/vector_angle.hpp>

// Lightfield
#include "RenderCPP/VtxIdxLstObj.h"

using namespace Lf;
using namespace RenderCPP;
//---------------------------------------------------------------------



//---------------------------------------------------------------------
// setIdxLst
//---------------------------------------------------------------------
void VtxIdxLstObj::setIdxLst(const uint32_t *pI,const uint32_t n)
{
  assert(pI);
  assert(n);

  _idxLst.resize(n);

  {
  uint32_t       *pId    = _idxLst.data();
  const uint32_t *pIs    = pI;
  const uint32_t *pIsEnd = pIs + n;
  const uint32_t *pIsStp = pIsEnd - 8;

    while (pIs < pIsStp)
    {
      *pId = *pIs; pId++; pIs++;
      *pId = *pIs; pId++; pIs++;
      *pId = *pIs; pId++; pIs++;
      *pId = *pIs; pId++; pIs++;

      *pId = *pIs; pId++; pIs++;
      *pId = *pIs; pId++; pIs++;
      *pId = *pIs; pId++; pIs++;
      *pId = *pIs; pId++; pIs++;
    }

    while (pIs < pIsEnd)
    {
      *pId = *pIs; 
       pId++; pIs++;
    }
  }
}


//---------------------------------------------------------------------
// render
//---------------------------------------------------------------------
void  VtxIdxLstObj::render(Shader *pShader)
{
size_t    nI = _idxLst.size();
size_t    nV = _vtxLst.size();

  pShader->determine();

  for (size_t i = 0;i < nI;i += 3)
  {
  uint32_t  i0    = _idxLst[i + 0];
  uint32_t  i1    = _idxLst[i + 1];
  uint32_t  i2    = _idxLst[i + 2];
  Vtx3      *pV0  = &(_vtxLst[i0]);
  Vtx3      *pV1  = &(_vtxLst[i1]);
  Vtx3      *pV2  = &(_vtxLst[i2]);

    pShader->render(pV0,pV1,pV2);
  }
}


//---------------------------------------------------------------------
// VtxIdxLstObj
//---------------------------------------------------------------------
VtxIdxLstObj::VtxIdxLstObj(void) : VtxLstObj(),
                                   _idxLst()
{
}


//---------------------------------------------------------------------
// ~VtxIdxLstObj
//---------------------------------------------------------------------
VtxIdxLstObj::~VtxIdxLstObj()
{

}

