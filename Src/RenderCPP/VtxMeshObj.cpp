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

// VtxMeshObj.cpp 
// Thomas Burnett


//---------------------------------------------------------------------
// Includes
// System

// 3rdPartyLibs
#include <glm/gtx/norm.hpp>

// Lightfield

#include "RenderCPP/VtxMeshObj.h"

using namespace Lf;
using namespace RenderCPP;
//---------------------------------------------------------------------



//---------------------------------------------------------------------
// setHeightMap
//---------------------------------------------------------------------
void VtxMeshObj::setHeightMap(const float *pF,const glm::ivec2 &dim)
{
float minValue =  FLT_MAX;
float maxValue = -FLT_MAX;

  _dim = dim;
  _hMap.resize(dim.x * dim.y);
  memcpy(_hMap.data(),pF,dim.x * dim.y * sizeof(float));

  // get the min and max height values
  for (size_t idx = 0; idx < _hMap.size(); idx++)
  {
    minValue = glm::min(minValue, _hMap[idx]);
    maxValue = glm::max(maxValue, _hMap[idx]);
  }

  _minMaxHeight = glm::vec2(minValue, maxValue);
  _maxDimension = glm::max(maxValue - minValue, (float)glm::max(dim.x, dim.y));

  _heightOffset = _minMaxHeight[0];
}



//---------------------------------------------------------------------
// VtxMeshObj
//---------------------------------------------------------------------
VtxMeshObj::VtxMeshObj(void) : VtxObj(),
                               _hMap(),
                               _dim(),
                               _minMaxHeight()
{
}


//---------------------------------------------------------------------
// ~VtxMeshObj
//---------------------------------------------------------------------
VtxMeshObj::~VtxMeshObj()
{

}

