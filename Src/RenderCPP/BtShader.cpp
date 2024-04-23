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

// BtShader.cpp
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
#include "RenderCPP/BtShader.h"

using namespace Lf;
using namespace RenderCPP;
//---------------------------------------------------------------------



//---------------------------------------------------------------------
// BtShader
//---------------------------------------------------------------------
BtShader::BtShader(const char *pName) : Shader(pName),
                                        _mVol(),
                                        _objN(0),
                                        _hogelDataLst()
{
}


//---------------------------------------------------------------------
// ~BtShader
//---------------------------------------------------------------------
BtShader::~BtShader()
{
}
