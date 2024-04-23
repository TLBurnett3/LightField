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

// BtClipper.cpp 
// Thomas Burnett


//---------------------------------------------------------------------
// Includes
// System

// 3rdPartyLibs
#include <glm/ext.hpp>

// Lightfield
#include "RenderCPP/BtClipper.h"

using namespace Lf;
using namespace RenderCPP;
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Defines
#define CDEBUG 0
#define MDEBUG 0
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// clipEdge
//---------------------------------------------------------------------
void BtClipper::clipEdge(const glm::vec4 &plane,Vtx3 *pI0,Vtx3 *pI1,Vtx3 *pO,uint32_t *n)
{
float c0 = classify(plane,pI0->_V);
float c1 = classify(plane,pI1->_V);

  if (c0 == InFrontOfPlane) 
  {
    *(pO + *n) = *pI0;
    (*n)++;

    if (c1 == InBackOfPlane)
    {
      intersect(plane,pI0,pI1,(pO + *n));

      if (keepClip(pO,*n))
        (*n)++;
    }
  }
  else if (c0 == InBackOfPlane)
  {
    if (c1 == InFrontOfPlane)
    {
      intersect(plane,pI0,pI1,(pO + *n));

      if (keepClip(pO,*n))
        (*n)++;
    }
  }
  else // c0 is OnPlane
  {
    *(pO + *n) = *pI0;
    (*n)++;
  }
}


//---------------------------------------------------------------------
// clip
// https://gamedevelopment.tutsplus.com/tutorials/understanding-sutherland-hodgman-clipping-for-physics-engines--gamedev-11917
//---------------------------------------------------------------------
Vtx3 *BtClipper::clip(FrustumDef fD,Vtx3 *pA,Vtx3 *pB,uint32_t *n)
{
glm::vec4 *planeEq  = _cPlanes[fD];
Vtx3      *pI       = pA;
Vtx3      *pO       = pB;
uint32_t  nI        = *n;
uint32_t  nO        = 0;
uint32_t  i         = 0;
bool      finished  = false;

  assert((fD == Back) || (fD == Front));

  while (!finished)
  {
    nO = 0;

    for (uint32_t j = 0;j < nI - 1;j++)
      clipEdge(planeEq[i],&pI[j],&pI[j + 1],pO,&nO);

    clipEdge(planeEq[i],&pI[nI - 1],&pI[0],pO,&nO);

    if (nO < 3)
      finished = true;
    else
    {
      i++;

      if (i == MaxPlanes) 
        finished = true;
      else if (i & 0x1)
      {
        pI  = pB;
        pO  = pA;
      }
      else
      {
        pI  = pA;
        pO  = pB;
      }

      nI = nO;
    }
  }

  *n = nO;

  return pO;
}


//---------------------------------------------------------------------
// classifyHogelPlane
//---------------------------------------------------------------------
float BtClipper::classifyHogelPlane(const Vtx3 *pV0,const Vtx3 *pV1,const Vtx3 *pV2)
{
glm::vec4 hPlaneEq    = _cPlanes[Front][LeftPlane]  + _cPlanes[Front][RightPlane];
float     c0          = classify(hPlaneEq,pV0->_V);
float     c1          = classify(hPlaneEq,pV1->_V);
float     c2          = classify(hPlaneEq,pV2->_V);
float     c           = 0;

  if ((c0 > 0.0f) && (c1 > 0.0f) && (c2 > 0.0f))
    c = InFrontOfPlane;
  else if ((c0 < 0.0f) && (c1 < 0.0f) && (c2 < 0.0f))
    c = InBackOfPlane;

  return c;
}


//---------------------------------------------------------------------
// set
//---------------------------------------------------------------------
void BtClipper::set(const glm::mat4 &m) 
{
  _cPlanes[Front][LeftPlane]   =  glm::row(m,3) - glm::row(m,0);
  _cPlanes[Front][RightPlane]  =  glm::row(m,3) + glm::row(m,0);
  _cPlanes[Front][BottomPlane] =  glm::row(m,3) + glm::row(m,1);
  _cPlanes[Front][TopPlane]    =  glm::row(m,3) - glm::row(m,1);

  if (0)
  {
    for (uint32_t i = 0;i < MaxPlanes;i++)
    {
    glm::vec3 plane = glm::vec3(_cPlanes[Front][i]);

      _cPlanes[Front][i] /= glm::dot(plane,plane);
    }
  }

  _cPlanes[Back][LeftPlane]     = -_cPlanes[Front][RightPlane];  
  _cPlanes[Back][RightPlane]    = -_cPlanes[Front][LeftPlane]; 
  _cPlanes[Back][BottomPlane]   = -_cPlanes[Front][TopPlane];
  _cPlanes[Back][TopPlane]      = -_cPlanes[Front][BottomPlane];   

  if (MDEBUG)
  {
    printf("Matrix\n");

    printf("         %10.4f %10.4f %10.4f %10.4f\n",m[0].x,m[0].y,m[0].z,m[0].w);
    printf("         %10.4f %10.4f %10.4f %10.4f\n",m[1].x,m[1].y,m[1].z,m[1].w);
    printf("         %10.4f %10.4f %10.4f %10.4f\n",m[2].x,m[2].y,m[2].z,m[2].w);
    printf("         %10.4f %10.4f %10.4f %10.4f\n",m[3].x,m[3].y,m[3].z,m[3].w);

    printf("Back Plane Equations\n");
    for (uint32_t i = 0;i < MaxPlanes;i++)
      printf("Plane %d: %10.4f %10.4f %10.4f %10.4f\n",i,
               _cPlanes[Back][i].x,_cPlanes[Back][i].y,_cPlanes[Back][i].z,_cPlanes[Back][i].w);

    printf("\nFront Plane Equations\n");
    for (uint32_t i = 0;i < MaxPlanes;i++)
      printf("Plane %d: %10.4f %10.4f %10.4f %10.4f\n",i,
               _cPlanes[Front][i].x,_cPlanes[Front][i].y,_cPlanes[Front][i].z,_cPlanes[Front][i].w);

    printf("\n");
  }
}
