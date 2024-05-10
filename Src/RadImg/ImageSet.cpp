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

// ImageSet.cpp 
// Thomas Burnett


//---------------------------------------------------------------------
// Includes
// System
#include <iostream>

// 3rdPartyLibs

// LightField
#include "RadImg/ImageSet.h"

using namespace Lf;
using namespace RadImg;
//---------------------------------------------------------------------



//---------------------------------------------------------------------
// convert
//---------------------------------------------------------------------
void ImageSet::convert(ImageSet &iSet,uint32_t c) 
{
size_t  n   = iSet.size();

  _subImageLst.clear();
  _subImageLst.resize(n);

  for (size_t i = 0;i < n;i++)
  {
    iSet.getSubImg(i)->_img.convertTo(_subImageLst[i]._img,CV_32FC3);

    _subImageLst[i]._idx = iSet.getSubImg(i)->_idx;
    _subImageLst[i]._pos = iSet.getSubImg(i)->_pos;
    _subImageLst[i]._uv  = iSet.getSubImg(i)->_uv;  
  }

  _nI = iSet._nI;
  _iS = iSet._iS;
  _aP = iSet._aP;
}


//---------------------------------------------------------------------
// fitSize
//---------------------------------------------------------------------
int ImageSet::fitSize(const glm::ivec2 &mS) 
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
  SubImageLst::iterator ii   = _subImageLst.begin();
  SubImageLst::iterator iEnd = _subImageLst.end();
    
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
int ImageSet::load(const std::filesystem::path &dPath) 
{
int         rc = 0;

  if (std::filesystem::exists(dPath))
  {
  glm::vec2   aMin( FLT_MAX);
  glm::vec2   aMax(-FLT_MAX);
  glm::vec2   avg(0);

    for (auto const &dE : std::filesystem::directory_iterator{dPath}) 
    {
    std::filesystem::path fPath = dE.path();
    std::filesystem::path fname = fPath.filename();
  
      std::cout << "Loading: " << fPath.filename();

      {
      const char  *pD = "_\n\0";
      char        *p  = 0;
      uint32_t    i   = 0;
      SubImage    subImage;
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
          subImage._idx.y = atoi(pT[1]);
          subImage._idx.x = atoi(pT[2]);

          _nI = glm::max(_nI,subImage._idx + 1);

          std::cout << "  " << subImage._idx.y << "," << subImage._idx.x;

          if (i > 4)
          {
            subImage._pos.y = atof(pT[3]);
            subImage._pos.x = atof(pT[4]);

            aMin = glm::min(aMin,subImage._pos);
            aMax = glm::max(aMax,subImage._pos);
            avg += subImage._pos;

            std::cout << "  " << subImage._pos.y << "," << subImage._pos.x;
          }
        }

        subImage._img = cv::imread(fPath.string());

        if (!subImage._img.empty())
        {
        glm::ivec2 iS(subImage._img.cols,subImage._img.rows);

          if (!subImage._img.empty())
            _iS = iS;

          std::cout << "  " << subImage._img.rows << "," << subImage._img.cols;

          if (_iS == iS)
          {
            std::cout << "  Success" << std::endl;
            _subImageLst.emplace_back(subImage);
          }
          else
          {
            std::cout << "  load failure" << std::endl;
            rc |= -1;
          }
        } 
      }   
    }

    avg /= (float)_subImageLst.size();

    {
    glm::vec2  uv = 0.9f / (aMax - aMin);
    float      s  = (uv.x < uv.y ? uv.x : uv.y);

      for (size_t i = 0;i < _subImageLst.size();i++)
        _subImageLst[i]._uv = s * (_subImageLst[i]._pos - avg);
    }

    _aP = glm::max(aMax.y - aMin.y,aMax.x - aMin.x);

    std::cout << "Num Images: " << _nI.y << "," << _nI.x << std::endl;
    std::cout << " Aperture: " << _aP << std::endl;
  }

  return rc;
}


//---------------------------------------------------------------------
// ImageSet
//---------------------------------------------------------------------
ImageSet::ImageSet(void) :  _subImageLst(),
                            _nI(0),
                            _iS(0),
                            _aP(0)
{
}


//---------------------------------------------------------------------
// ~ImageSet
//---------------------------------------------------------------------
ImageSet::~ImageSet()
{
}

