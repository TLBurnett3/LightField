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

// MultCamImageSet.cpp 
// Thomas Burnett


//---------------------------------------------------------------------
// Includes
// System
#include <iostream>

// 3rdPartyLibs

// LightField
#include "RadImg/MultCamImageSet.h"

using namespace Lf;
using namespace RadImg;
//---------------------------------------------------------------------



//---------------------------------------------------------------------
// create 
//---------------------------------------------------------------------
int MultCamImageSet::create(EPIVerImageSet &is,const uint32_t col)
{
int rc = -1;

  is._iLst.clear();
  is._iLst.resize(_iS.x);

  for (size_t i = 0;i < (size_t)_iS.x;i++)
  {
    is._iLst[i]._img.create(_iS.y,_nI.y,CV_8UC3);
    is._iLst[i]._idx = glm::ivec2(i,0);
    is._iLst[i]._pos = glm::ivec2(0,0);
    is._iLst[i]._uv  = glm::ivec2(0,0);
  }

  if ((col == -1) || (col < _nI.y))
  {
  glm::ivec2  iIdx;
  glm::ivec2  nIdx;
  cv::Vec3b   c;
  uint32_t    i = (col == -1) ? _nI.y >> 1 : col;

    for (nIdx.y = 0;nIdx.y < _nI.y;nIdx.y++)
    {
      for (iIdx.y = 0;iIdx.y < _iS.y;iIdx.y++)
      {
        for (iIdx.x = 0;iIdx.x < _iS.x;iIdx.x++)
        {
          c = _iLst[i]._img.at<cv::Vec3b>(iIdx.y,iIdx.x);

          is._iLst[iIdx.x]._img.at<cv::Vec3b>(iIdx.y,nIdx.y) = c;
        }
      }

      i += _nI.x;
    }

    is._nI = glm::ivec2(_iS.x,1);
    is._iS = glm::ivec2(_iS.y,_nI.y);
    is._aP = 0;

    rc = 0;
  }

  return rc;
}



//---------------------------------------------------------------------
// create 
//---------------------------------------------------------------------
int MultCamImageSet::create(EPIHorImageSet &is,const uint32_t row)
{
int rc = -1;

  is._iLst.clear();
  is._iLst.resize(_iS.y);

  for (size_t i = 0;i < (size_t)_iS.y;i++)
  {
    is._iLst[i]._img.create(_nI.x,_iS.x,CV_8UC3);
    is._iLst[i]._idx = glm::ivec2(0,i);
    is._iLst[i]._pos = glm::ivec2(0,0);
    is._iLst[i]._uv  = glm::ivec2(0,0);
  }

  if ((row == -1) || (row < _nI.y))
  {
  glm::ivec2  iIdx;
  glm::ivec2  nIdx;
  cv::Vec3b   c;
  uint32_t    r = (row == -1) ? _nI.y >> 1 : row;
  uint32_t    i = r * _nI.x;

    for (nIdx.x = 0;nIdx.x < _nI.x;nIdx.x++)
    {
      for (iIdx.y = 0;iIdx.y < _iS.y;iIdx.y++)
      {
        for (iIdx.x = 0;iIdx.x < _iS.x;iIdx.x++)
        {
          c = _iLst[i]._img.at<cv::Vec3b>(iIdx.y,iIdx.x);

          is._iLst[iIdx.y]._img.at<cv::Vec3b>(nIdx.x,iIdx.x) = c;
        }
      }

      i++;
    }

    is._nI = glm::ivec2(1,_iS.y);
    is._iS = glm::ivec2(_iS.x,_nI.x);
    is._aP = 0;

    rc = 0;
  }

  return rc;
}


//---------------------------------------------------------------------
// create 
//---------------------------------------------------------------------
int MultCamImageSet::create(MultCamImage &mci)
{
int         rc = -1;
glm::ivec2  sz = _nI * _iS;
glm::ivec2  iIdx;
glm::ivec2  nIdx;

  mci._img.create(sz.y,sz.x,CV_8UC3);

  if (!mci._img.empty())
  {
  unsigned  char  *pD = mci._img.data;
  unsigned  char  *pS = 0;

    std::cout << "Slicing Multi-Camera Image:  " <<  sz.y << "," << sz.x << std::endl;

    mci._iS = _iS;
    mci._nI = _nI;

    for (nIdx.y = 0;nIdx.y < _nI.y;nIdx.y++)
    {  
      for (iIdx.y = 0;iIdx.y < _iS.y;iIdx.y++)
      {
        for (nIdx.x = 0;nIdx.x < _nI.x;nIdx.x++)
        {
          for (iIdx.x = 0;iIdx.x < _iS.x;iIdx.x++)
          {  
            pS =  _iLst[(nIdx.y * _nI.x) + nIdx.x]._img.data;
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
    std::cout << "Multi-Camera image too large: " << _iS.y << "," << _iS.x << std::endl;

  return rc;
}


//---------------------------------------------------------------------
// MultCamImageSet
//---------------------------------------------------------------------
MultCamImageSet::MultCamImageSet(void) :  ImageSet()
{
}


//---------------------------------------------------------------------
// ~MultCamImageSet
//---------------------------------------------------------------------
MultCamImageSet::~MultCamImageSet()
{

}

