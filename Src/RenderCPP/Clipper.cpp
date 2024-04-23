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

// Clipper.cpp 
// Thomas Burnett


//---------------------------------------------------------------------
// Includes
// System

// 3rdPartyLibs
#include <glm/ext.hpp>

// Lightfield
#include "RenderCPP/Clipper.h"

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
void Clipper::clipEdge(const glm::vec4 &plane,Vtx3 *pI0,Vtx3 *pI1,Vtx3 *pO,uint32_t *n)
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
Vtx3 *Clipper::clip(Vtx3 *pA,Vtx3 *pB,uint32_t *n)
{
Vtx3      *pI       = pA;
Vtx3      *pO       = pB;
uint32_t  nI        = *n;
uint32_t  nO        = 0;
uint32_t  i         = 0;
bool      finished  = false;

  while (!finished)
  {
    nO = 0;

    for (uint32_t j = 0;j < nI - 1;j++)
      clipEdge(_cPlanes[i],&pI[j],&pI[j + 1],pO,&nO);

    clipEdge(_cPlanes[i],&pI[nI - 1],&pI[0],pO,&nO);

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
// set
//---------------------------------------------------------------------
void Clipper::set(const glm::mat4 &m) 
{
  _cPlanes[LeftPlane]   =  glm::row(m,3) - glm::row(m,0);
  _cPlanes[RightPlane]  =  glm::row(m,3) + glm::row(m,0);
  _cPlanes[BottomPlane] =  glm::row(m,3) + glm::row(m,1);
  _cPlanes[TopPlane]    =  glm::row(m,3) - glm::row(m,1);
  _cPlanes[FarPlane]    =  glm::row(m,3) - glm::row(m,2);
  _cPlanes[NearPlane]   =  glm::row(m,3) + glm::row(m,2);

  if (0)
  {
    for (uint32_t i = 0;i < MaxPlanes;i++)
    {
    glm::vec3 plane = glm::vec3(_cPlanes[i]);

      _cPlanes[i] /= glm::dot(plane,plane);
    }
  }

  if (MDEBUG)
  {
    printf("Matrix\n");

    printf("         %10.4f %10.4f %10.4f %10.4f\n",m[0].x,m[0].y,m[0].z,m[0].w);
    printf("         %10.4f %10.4f %10.4f %10.4f\n",m[1].x,m[1].y,m[1].z,m[1].w);
    printf("         %10.4f %10.4f %10.4f %10.4f\n",m[2].x,m[2].y,m[2].z,m[2].w);
    printf("         %10.4f %10.4f %10.4f %10.4f\n",m[3].x,m[3].y,m[3].z,m[3].w);

    printf("\nPlane Equations\n");
    for (uint32_t i = 0;i < MaxPlanes;i++)
      printf("Plane %d: %10.4f %10.4f %10.4f %10.4f\n",i,
               _cPlanes[i].x,_cPlanes[i].y,_cPlanes[i].z,_cPlanes[i].w);

    printf("\n");
  }
}
