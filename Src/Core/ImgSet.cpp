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

// ImgSet.cpp 
// Thomas Burnett


//---------------------------------------------------------------------
// Includes
// System
#include <iostream>

// 3rdPartyLibs

// LightField
#include "Core/ImgSet.h"

using namespace Lf;
using namespace Core;
//---------------------------------------------------------------------



//---------------------------------------------------------------------
// createPlenopticImage 
// Thomas Burnett
// November  16, 2013
//---------------------------------------------------------------------
int ImgSet::createPlenopticImage(cv::Mat &img,glm::ivec2 &nI,glm::ivec2 &iS)
{
int         rc = -1;
glm::ivec2  sz = _nI * _iS;
glm::ivec2  iIdx;
glm::ivec2  nIdx;

  img.create(sz.y,sz.x,CV_8UC3);

  if (!img.empty())
  {
  unsigned  char  *pD = img.data;
  unsigned  char  *pS = 0;

    std::cout << "Slicing Plenoptic Image:  " <<  sz.y << "," << sz.x << std::endl;

    iS = _iS;
    nI = _nI;

    for (nIdx.y = 0;nIdx.y < _nI.y;nIdx.y++)
    {  
      for (iIdx.y = 0;iIdx.y < _iS.y;iIdx.y++)
      {
        for (nIdx.x = 0;nIdx.x < _nI.x;nIdx.x++)
        {
          for (iIdx.x = 0;iIdx.x < _iS.x;iIdx.x++)
          {  
            pS =  _imgSet[(nIdx.y * _nI.x) + nIdx.x]._img.data;
            pS += iIdx.y * _iS.x * 3;
            pS += iIdx.x * 3;

            *(pD + 0) = *(pS + 0);
            *(pD + 1) = *(pS + 1);
            *(pD + 2) = *(pS + 2);

            pD += 3;
          }
        }
      }
    }

    rc = 0;
  }
  else
    std::cout << "Plenoptic image too large: " << _iS.y << "," << _iS.x << std::endl;

  return rc;
}


//---------------------------------------------------------------------
// fitSize
//---------------------------------------------------------------------
int ImgSet::fitSize(const glm::ivec2 &mS) 
{
int        rc  = 0;
glm::ivec2 iS  = _iS;
uint32_t   s   = 0;

  while (((iS.x * _nI.x) > mS.x) || ((iS.y * _nI.y) > mS.y))
  {
    iS >>= 1;
    s++;
  }

  if (s)
  {
  ISet::iterator ii   = _imgSet.begin();
  ISet::iterator iEnd = _imgSet.end();
    
    while (ii != iEnd)
    {
      cv::resize(ii->_img,ii->_img,cv::Size(iS.x,iS.y));
      ii++;
    }  
  }

  _iS = iS; 

  return rc;
}


//---------------------------------------------------------------------
// load
//---------------------------------------------------------------------
int ImgSet::load(const std::filesystem::path &dPath) 
{
int         rc = -1;
glm::vec2   aMin( FLT_MAX);
glm::vec2   aMax(-FLT_MAX);

  for (auto const &dE : std::filesystem::directory_iterator{dPath}) 
  {
  std::filesystem::path fPath = dE.path();
  std::filesystem::path fname = fPath.filename();
  
    std::cout << "Loading: " << fPath.filename();

    {
    const char  *pD = "_\n\0";
    char        *p  = 0;
    uint32_t    i   = 0;
    ImgData     imgData;
    char        *pT[10];
    char        buf[512+1];

      strncpy(buf,fname.string().c_str(),512);

      p = strtok(buf,pD);

      do 
      {
        pT[i] = p;
        i++;

        p = strtok(0,pD);
      }
      while ((p != 0) && (i < 10));

      if (i > 2)
      {
        imgData._iNum.y = atoi(pT[1]);
        imgData._iNum.x = atoi(pT[2]);

        _nI = glm::max(_nI,imgData._iNum + 1);

        std::cout << "  " << imgData._iNum.y << "," << imgData._iNum.x;

        if (i > 4)
        {
          imgData._iLoc.y = atof(pT[3]);
          imgData._iLoc.x = atof(pT[4]);

          aMin = glm::min(aMin,imgData._iLoc);
          aMax = glm::max(aMax,imgData._iLoc);

          std::cout << "  " << imgData._iLoc.y << "," << imgData._iLoc.x;
        }
      }

      imgData._img = cv::imread(fPath.string());

      if (!imgData._img.empty())
      {
      glm::ivec2 iS(imgData._img.cols,imgData._img.rows);

        if (_imgSet.empty())
          _iS = iS;

        std::cout << "  " << imgData._img.rows << "," << imgData._img.cols;

        if (_iS == iS)
        {
          std::cout << "  Success" << std::endl;
          _imgSet.emplace_back(imgData);
          rc = 0;
        }
      } 
    } 
  }

  _aP = glm::max(aMax.y - aMin.y,aMax.x - aMin.x);

  std::cout << "Num Images: " << _nI.y << "," << _nI.x << std::endl;
  std::cout << " Aperture: " << _aP << std::endl;

  return rc;
}


//---------------------------------------------------------------------
// ImgSet
//---------------------------------------------------------------------
ImgSet::ImgSet(void) :  _imgSet(),
                        _nI(0),
                        _iS(0),
                        _aP(0)
{
}


//---------------------------------------------------------------------
// ~ImgSet
//---------------------------------------------------------------------
ImgSet::~ImgSet()
{

}

