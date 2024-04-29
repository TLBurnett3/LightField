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
// Tries to mirror the GLSL version
//---------------------------------------------------------------------
void SarCpp::render(RenderGL::Texture &mctex,RenderGL::VtxArrayObj &vao)
{
uchar      *pD  = _sImg.data;
glm::ivec2 aR   = glm::vec2(_nI >> 1) * _aP;
glm::ivec2 bI   = (_nI >> 1) - aR;
glm::ivec2 eI   = (_nI >> 1) + aR;
glm::ivec2 oI(0);
glm::ivec2 iI(0);

  bI = glm::clamp(bI,glm::ivec2(0),_nI - 1);
  eI = glm::clamp(eI,glm::ivec2(0),_nI - 1);

  for (oI.y = 0;oI.y < _iS.y;oI.y++)
  {
    for (oI.x = 0;oI.x < _iS.x;oI.x++)
    {
    glm::vec2   fx = oI;
    glm::vec3   clr(0.0f,0.0f,0.0f);
    float       n(0);
    cv::Vec3b   c;

      for (iI.y = bI.y;iI.y <= eI.y;iI.y++)
      {
        for (iI.x = bI.x;iI.x <= eI.x;iI.x++)
        {
        int         i   = (iI.y * _nI.x) + iI.x;
        glm::vec2   lfx =  glm::vec2(glm::mat4(1) /*mH[i]*/ * glm::vec4(fx,0,1));     // apply homography
        glm::vec2   dx  =  iI;                     // location of subimage within plenoptic image

          dx   += lfx;                             // add location of subimage
          dx   += glm::vec2(0.5f);

          c = _mcImg.at<cv::Vec3b>((uint32_t)dx.y,(uint32_t)dx.x);

          clr.r += c[0];
          clr.g += c[1];
          clr.b += c[2];
          n++;
        }
      }

      clr /= n;

      *(pD + 0) = (uint8_t)clr.r;
      *(pD + 1) = (uint8_t)clr.g;
      *(pD + 2) = (uint8_t)clr.b;
      pD += 3;
    }
  }
  
  _sTex.upload(_sImg);

  _sTex.bind();
  vao.render();
}


//---------------------------------------------------------------------
// CppCodinite
//---------------------------------------------------------------------
int SarCpp::init(cv::Mat &mcImg,const glm::ivec2 &nI,const glm::ivec2 &iS)
{
int   rc = 0;

  _mcImg = mcImg;

  _sImg.create(iS.y,iS.x,CV_8UC3);
  _nI = nI;
  _iS = iS;

  return rc;
}



//---------------------------------------------------------------------
// SarCpp
//---------------------------------------------------------------------
SarCpp::SarCpp(void) : Sar("SarCpp"),
                         _mcImg(),
                         _sImg(),
                         _sTex(),
                         _nI(0),
                         _iS(0)
{
}


//---------------------------------------------------------------------
// ~SarCpp
//---------------------------------------------------------------------
SarCpp::~SarCpp()
{

}
