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

// SarShader.cpp
// Thomas Burnett


//---------------------------------------------------------------------
// Includes
// System
#include <assert.h>
#include <fstream>
#include <iostream>

// tLib
#include "Aperture/SarShader.h"

using namespace Lf;
using namespace Aperture;
//---------------------------------------------------------------------



//---------------------------------------------------------------------
// compile
//---------------------------------------------------------------------
int   SarShader::compile(void)
{
int   rc = BasicShader::compile();

  if (rc == 0)
  {
    _locImageIndex     = glGetUniformLocation(_programShaderId,"iIdx");     

    if (_locImageIndex < 0)
    {
      std::cout << "Failed to locate iIdx\n";
      rc = -1;
    }

    _locNumImages     = glGetUniformLocation(_programShaderId,"nI");     

    if (_locNumImages < 0)
    {
      std::cout << "Failed to locate nI\n";
      rc = -1;
    }

    _locAperture     = glGetUniformLocation(_programShaderId,"aD");     

    if (_locAperture < 0)
    {
      std::cout << "Failed to locate aD\n";
      rc = -1;
    }

    _locImageSize     = glGetUniformLocation(_programShaderId,"iS");     

    if (_locImageSize < 0)
    {
      std::cout << "Failed to locate iS\n";
      rc = -1;
    }

    _idxHomographies  = glGetUniformBlockIndex(_programShaderId,"Homographies"); 

    glUniformBlockBinding(_programShaderId,_idxHomographies,HOMOGRAPHIES_BINDING_POINT);

    if (_homographyBuffer == 0)
    {
      glGenBuffers(1,&_homographyBuffer);
      glBindBuffer(GL_UNIFORM_BUFFER,_homographyBuffer);
    }  
  }

  return rc;
}


//---------------------------------------------------------------------
// SarShader
//---------------------------------------------------------------------
SarShader::SarShader(const char *pName) : BasicShader(pName),
                                          _locImageIndex(-1),
                                          _locImageSize(-1),
                                          _locNumImages(-1),
                                          _locAperture(-1),
                                          _idxHomographies(-1),
                                          _homographyBuffer(0)
{
}


//---------------------------------------------------------------------
// ~SarShader
//---------------------------------------------------------------------
SarShader::~SarShader()
{
}
