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

// SarCV.cpp 
// Thomas Burnett


//---------------------------------------------------------------------
// Includes
// System

// 3rdPartyLibs

// LightField
#include "Aperture/SarCV.h"

using namespace Lf;
using namespace Aperture;
//---------------------------------------------------------------------



//---------------------------------------------------------------------
// render
//---------------------------------------------------------------------
void SarCV::render(RenderGL::Texture &mcTex,RenderGL::VtxArrayObj &vao)
{
cv::Mat     tImg(_iS.y,_iS.x,CV_32FC3,cv::Scalar(0,0,0));
cv::Mat     wImg(_iS.y,_iS.x,CV_32FC3);
cv::Mat     mH  (2,3,CV_32FC1);
glm::ivec2  aR   = glm::vec2(_nI >> 1) * _aP;
glm::ivec2  bI   = _iIdx - aR;
glm::ivec2  eI   = _iIdx + aR;
glm::ivec2  iI(0);
float       n(0);

  bI = glm::clamp(bI,glm::ivec2(0),_nI - 1);
  eI = glm::clamp(eI,glm::ivec2(0),_nI - 1);

  for (iI.y = bI.y;iI.y <= eI.y;iI.y++)
  {
    for (iI.x = bI.x;iI.x <= eI.x;iI.x++)
    {
    int              i    = (iI.y * _nI.x) + iI.x;
    const glm::mat4  *pMH = &((*_pMHLst)[i]);

      // remember, GLM/OpenGL matrices are column major
      ((float *)mH.data)[0] =  (*pMH)[0][0]; 
      ((float *)mH.data)[1] =  (*pMH)[1][0]; 
      ((float *)mH.data)[2] = -(*pMH)[3][0];
      ((float *)mH.data)[3] =  (*pMH)[0][1];  
      ((float *)mH.data)[4] =  (*pMH)[1][1]; 
      ((float *)mH.data)[5] = -(*pMH)[3][1];

      cv::warpAffine(_imgLst[i],wImg,mH,wImg.size());
      tImg += wImg;
      n++;
    }
  }

  tImg /= n;

  tImg.convertTo(_dImg,CV_8UC3);
  
  _dTex.upload(_dImg);
  _dTex.bind();

  vao.render();
}


//---------------------------------------------------------------------
// init
//---------------------------------------------------------------------
int SarCV::init(Core::ImgSet &imgSet,const glm::ivec2 &nI,const glm::ivec2 &iS)
{
int     rc  = 0;
size_t  n   = imgSet.size();
  
  for (size_t i = 0;i < n;i++)
  {
  cv::Mat tmp;

    imgSet.get(i)->_img.convertTo(tmp,CV_32FC3);
    _imgLst.push_back(tmp);
  }

  _dImg.create(iS.y,iS.x,CV_8UC3);
  _nI = nI;
  _iS = iS;

  return rc;
}



//---------------------------------------------------------------------
// SarCV
//---------------------------------------------------------------------
SarCV::SarCV(void) : Sar("SarCV"),
                         _imgLst(),
                         _dImg(),
                         _dTex(),
                         _nI(0),
                         _iS(0)
{
}


//---------------------------------------------------------------------
// ~SarCV
//---------------------------------------------------------------------
SarCV::~SarCV()
{

}


