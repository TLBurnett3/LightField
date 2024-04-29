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

// SarCpp.cpp 
// Thomas Burnett


//---------------------------------------------------------------------
// Includes
// System

// 3rdPartyLibs

// LightField
#include "Aperture/SarCpp.h"

using namespace Lf;
using namespace Aperture;
//---------------------------------------------------------------------



//---------------------------------------------------------------------
// render
//---------------------------------------------------------------------
void SarCpp::render(RenderGL::Texture &mctex,RenderGL::VtxArrayObj &vao)
{
cv::Scalar clr(0.0f,0.0f,0.0f);
glm::ivec2 oI(0);
glm::ivec2 bI(0);
glm::ivec2 eI(0);
glm::ivec2 iI(0);

  for (oI.y = 0;oI.y < _iS.y;oI.y++)
  {
    for (oI.x = 0;oI.x < _iS.x;oI.x++)
    {
    glm::vec2   fx = glm::vec2(oI) / glm::vec2(_iS);
    glm::ivec2  aR = glm::vec2(_nI >> 1) * _aP;

      for (iI.y = bI.y;iI.y < eI.y;iI.y++)
      {
        for (iI.x = bI.x;iI.x < eI.x;iI.x++)
        {
        }
      }
    }
  }

  _img.setTo(clr);
}


//---------------------------------------------------------------------
// CppCodinite
//---------------------------------------------------------------------
int SarCpp::init(const glm::ivec2 &nI,const glm::ivec2 &iS,const float aP)
{
int   rc = 0;

  _img.create(iS.y,iS.x,CV_32FC3);
  _nI = nI;
  _iS = iS;
  _aP = aP;

  return rc;
}



//---------------------------------------------------------------------
// SarCpp
//---------------------------------------------------------------------
SarCpp::SarCpp(void) : Sar("SarCpp"),
                         _img(),
                         _nI(0),
                         _iS(0),
                         _aP(0)
{
}


//---------------------------------------------------------------------
// ~SarCpp
//---------------------------------------------------------------------
SarCpp::~SarCpp()
{

}

