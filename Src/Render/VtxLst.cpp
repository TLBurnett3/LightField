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

// VtxLst.cpp
// Thomas Burnett


//---------------------------------------------------------------------
// Includes
// System
#include <float.h>

// LightField
#include "Render/VtxLst.h"

using namespace Lf;
using namespace Render;
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// createQuadXY
// Thomas Burnett
// March 15, 2014
//
// Creates a quad vertex list.
//---------------------------------------------------------------------
int  createQuadXY(const glm::vec3 &vP,VtxVNTLst &vLst,glm::vec2 &d)
{
glm::vec2 hD = glm::vec2(d) * 0.5f;
glm::vec3 vX = glm::vec3(1,0,0) * hD.x;
glm::vec3 vY = glm::vec3(0,1,0) * hD.y;
glm::vec3 vZ = glm::vec3(0,0,1);

  vLst.reset();

  vLst.add(vP + (-vX + vY),vZ,glm::vec2(0.0f,1.0f));
  vLst.add(vP + (-vX - vY),vZ,glm::vec2(0.0f,0.0f));
  vLst.add(vP + ( vX + vY),vZ,glm::vec2(1.0f,1.0f));
  vLst.add(vP + ( vX - vY),vZ,glm::vec2(1.0f,0.0f));

  return GL_TRIANGLE_STRIP;
}


//---------------------------------------------------------------------
// createQuadXZ
// Thomas Burnett
// March 15, 2014
//
// Creates a quad vertex list.
//---------------------------------------------------------------------
int  createQuadXZ(const glm::vec3 &vP,VtxVNTLst &vLst,glm::vec2 &d)
{
glm::vec2 hD = glm::vec2(d) * 0.5f;
glm::vec3 vX = glm::vec3(1,0,0) * hD.x;
glm::vec3 vY = glm::vec3(0,1,0);
glm::vec3 vZ = glm::vec3(0,0,1) * hD.y;

  vLst.reset();

  vLst.add(vP + (-vX - vZ),vY,glm::vec2(0.0f,1.0f));
  vLst.add(vP + (-vX + vZ),vY,glm::vec2(0.0f,0.0f));
  vLst.add(vP + ( vX - vZ),vY,glm::vec2(1.0f,1.0f));
  vLst.add(vP + ( vX + vZ),vY,glm::vec2(1.0f,0.0f));

  return GL_TRIANGLE_STRIP;
}
