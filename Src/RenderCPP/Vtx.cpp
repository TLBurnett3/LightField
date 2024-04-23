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

// Vtx.cpp
// Thomas Burnett


#pragma once

//---------------------------------------------------------------------
// Includes
// System
#include <stdio.h>

// 3rdPartyLibs

// Lightfield
#include "RenderCPP/Vtx.h"

using namespace Lf;
using namespace RenderCPP;
//---------------------------------------------------------------------
/*

void printMat4(const char *pS,const glm::mat4 &m)
{
  printf("%s\n",pS);
  printf("%10.4f  %10.4f  %10.4f  %10.4f\n",m[0].x,m[1].x,m[2].x,m[3].x);
  printf("%10.4f  %10.4f  %10.4f  %10.4f\n",m[0].y,m[1].y,m[2].y,m[3].y);
  printf("%10.4f  %10.4f  %10.4f  %10.4f\n",m[0].z,m[1].z,m[2].z,m[3].z);
  printf("%10.4f  %10.4f  %10.4f  %10.4f\n",m[0].w,m[1].w,m[2].w,m[3].w);
}  

//---------------------------------------------------------------------
// printVtx3
//---------------------------------------------------------------------
void printVtx3(const char *pStr,const MvPU::Vtx3 *pV0,const MvPU::Vtx3 *pV1,const MvPU::Vtx3 *pV2,const glm::mat4 &mT)
{
glm::vec4 vV;

  printf("%s\n",pStr);

  vV = mT * glm::vec4(pV0->_V,1);
  printf("V0:  %10.4f  %10.4f  %10.4f                   V0t: %10.4f  %10.4f  %10.4f\n",pV0->_V.x,pV0->_V.y,pV0->_V.z,vV.x,vV.y,vV.z);
                                                        
  vV = mT * glm::vec4(pV1->_V,1);                       
  printf("V1:  %10.4f  %10.4f  %10.4f                   V1t: %10.4f  %10.4f  %10.4f\n",pV1->_V.x,pV1->_V.y,pV1->_V.z,vV.x,vV.y,vV.z);
                                                        
  vV = mT * glm::vec4(pV2->_V,1);                       
  printf("V2:  %10.4f  %10.4f  %10.4f                   V2t: %10.4f  %10.4f  %10.4f\n",pV2->_V.x,pV2->_V.y,pV2->_V.z,vV.x,vV.y,vV.z);
}

//---------------------------------------------------------------------
// printVtx3
//---------------------------------------------------------------------
void printVtx3(const char *pStr,const MvPU::Vtx3 *pV0,const MvPU::Vtx3 *pV1,const MvPU::Vtx3 *pV2,const glm::mat4 &mT1,const glm::mat4 &mT2)
{
glm::vec4 vV1;
glm::vec4 vV2;

  printf("%s\n",pStr);

  vV1 = mT1 * glm::vec4(pV0->_V,1);
  vV2 = mT2 * glm::vec4(pV0->_V,1);
  printf("V0:  %10.4f  %10.4f  %10.4f",pV0->_V.x,pV0->_V.y,pV0->_V.z);                   
  printf("         %10.4f  %10.4f  %10.4f",vV1.x,vV1.y,vV1.z);
  printf("         %10.4f  %10.4f  %10.4f\n",vV2.x,vV2.y,vV2.z);
                                                        
  vV1 = mT1 * glm::vec4(pV1->_V,1);                       
  vV2 = mT2 * glm::vec4(pV1->_V,1);                       
  printf("V1:  %10.4f  %10.4f  %10.4f",pV1->_V.x,pV1->_V.y,pV1->_V.z);                   
  printf("         %10.4f  %10.4f  %10.4f",vV1.x,vV1.y,vV1.z);
  printf("         %10.4f  %10.4f  %10.4f\n",vV2.x,vV2.y,vV2.z);
                                                        
  vV1 = mT1 * glm::vec4(pV2->_V,1);                       
  vV2 = mT2 * glm::vec4(pV2->_V,1);                       
  printf("V2:  %10.4f  %10.4f  %10.4f",pV2->_V.x,pV2->_V.y,pV2->_V.z);                   
  printf("         %10.4f  %10.4f  %10.4f",vV1.x,vV1.y,vV1.z);
  printf("         %10.4f  %10.4f  %10.4f\n",vV2.x,vV2.y,vV2.z);
}


//---------------------------------------------------------------------
// printVtxLst
//---------------------------------------------------------------------
void printVtxLst(const char *pStr,const MvPU::Vtx4 *pVtxLst,const uint32_t n,const glm::mat4 &mT)
{
const Vtx4 *pVtx    = pVtxLst;
const Vtx4 *pVtxEnd = pVtx + n;
glm::vec4  vV;

  printf("%s\n",pStr);

  while (pVtx < pVtxEnd)
  {
    vV = mT * pVtx->_Vcs;

    printf("V%lld:  %10.4f  %10.4f  %10.4f  %10.4f       Vt%lld: %10.4f  %10.4f  %10.4f  %10.4f \n",
                             pVtx - pVtxLst,
                             pVtx->_Vcs.x,pVtx->_Vcs.y,pVtx->_Vcs.z,pVtx->_Vcs.w,
                             pVtx - pVtxLst,
                             vV.x,vV.y,vV.z,vV.w);

    pVtx++;
  }
}



//---------------------------------------------------------------------
// printVtxLst
//---------------------------------------------------------------------
void printVtxLst(const char *pStr,const MvPU::Vtx4 *pVtxLst,const uint32_t n)
{
const Vtx4 *pVtx    = pVtxLst;
const Vtx4 *pVtxEnd = pVtx + n;

  printf("%s\n",pStr);

  while (pVtx < pVtxEnd)
  {
    printf("V%lld:  %10.4f  %10.4f  %10.4f  %10.4f\n",
                             pVtx - pVtxLst,
                             pVtx->_Vcs.x,pVtx->_Vcs.y,pVtx->_Vcs.z,pVtx->_Vcs.w);

    pVtx++;
  }
}

//---------------------------------------------------------------------
// printCoordLst
//---------------------------------------------------------------------
void printCoordLst(const char *pStr,const MvPU::Coords *pCrdLst,const uint32_t n)
{
const Coords *pCrd    = pCrdLst;
const Coords *pCrdEnd = pCrd + n;

  printf("%s\n",pStr);

  while (pCrd < pCrdEnd)
  {
    printf("V%lld:      VP: %10.4f  %10.4f       RAS: %10.4f  %10.4f\n",
                            pCrd - pCrdLst,
                            pCrd->_vVprt.x,pCrd->_vVprt.y,
                            pCrd->_vRas.x,pCrd->_vRas.y);

    pCrd++;
  }
}*/