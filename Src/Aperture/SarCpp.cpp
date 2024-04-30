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
void SarCpp::render(const glm::mat4 &mP,const glm::mat4 &mV,
                    RenderGL::BasicShader *pS,RenderGL::Texture &mcTex,RenderGL::VtxArrayObj &vao)
{
uchar      *pD  = _dImg.data;
glm::vec2  nP   = (_iS * _nI) - 1;
glm::ivec2 aR   = glm::vec2(_nI >> 1) * _aP;
glm::ivec2 bI   = _iIdx - aR;
glm::ivec2 eI   = _iIdx + aR;
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
        glm::vec2   dx  = glm::vec2(iI) / glm::vec2(_nI); 
        glm::vec4   tfx =  (*_pMHLst)[i] * glm::vec4(fx,0,1);
        glm::vec2   lfx = glm::vec2(tfx);    

          lfx /= glm::vec2(_iS);
          lfx /= glm::vec2(_nI);
          dx   = glm::clamp(dx + lfx,glm::vec2(0),glm::vec2(1));  
          dx  *= nP;                     
          
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

  {
    pS->use();
    pS->bindMVP(mP * mV);
    pS->setTextureSampler(0);
  
    _dTex.upload(_dImg);
    _dTex.bind();

    vao.render();
  }
}


//---------------------------------------------------------------------
// init
//---------------------------------------------------------------------
int SarCpp::init(cv::Mat &mcImg,const glm::ivec2 &nI,const glm::ivec2 &iS)
{
int   rc = 0;

  _mcImg = mcImg;

  _dImg.create(iS.y,iS.x,CV_8UC3);
  _nI = nI;
  _iS = iS;

  return rc;
}



//---------------------------------------------------------------------
// SarCpp
//---------------------------------------------------------------------
SarCpp::SarCpp(void) : Sar("SarCpp"),
                         _mcImg(),
                         _dImg(),
                         _dTex()
{
}


//---------------------------------------------------------------------
// ~SarCpp
//---------------------------------------------------------------------
SarCpp::~SarCpp()
{

}






