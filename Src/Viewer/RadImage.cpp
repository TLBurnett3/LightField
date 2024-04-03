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

// RadImage.cpp 
// Thomas Burnett


//---------------------------------------------------------------------
// Includes
// System
#include <iostream>

// 3rdPartyLibs

// LightField
#include "Viewer/RadImage.h"

using namespace Lf;
using namespace Viewer;
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// examine
//---------------------------------------------------------------------
int RadImage::examine(const std::filesystem::path &dPath) 
{
int   rc = -1;
char  buf[64];

  _dPath = dPath;

  for (;;)
  {
  std::filesystem::path fPath = dPath;

    sprintf_s(buf,"HogelRow_%d.avi",_nH.y);
    fPath /= buf;

    {
    cv::VideoCapture  c(fPath.string());

      if (c.isOpened())
      {
        if (_nH.y == 0)
        {
          _hS = glm::ivec2(c.get(cv::CAP_PROP_FRAME_WIDTH),c.get(cv::CAP_PROP_FRAME_HEIGHT));

          while (c.isOpened())
          {          cv::Mat img;

            c >> img;

            if (img.data)
            {
              _nH.x++;

              rc = 0;
            }
            else
              c.release();
          }
        }

        std::cout << ".";

        _nH.y++;

        if (c.isOpened())
          c.release();
      }
      else
        break;
    }
  }

  std::cout << std::endl;
  std::cout << "Num Hogels: " << _nH.x << "," << _nH.y << std::endl;
  std::cout << "Hogel Size: " << _hS.x << "," << _hS.y << std::endl;

  return rc;
}


//---------------------------------------------------------------------
// exec
//---------------------------------------------------------------------
void RadImage::exec(void)
{
glm::ivec2        idx(0);

  std::cout << "Loading radiance image" << std::endl;

  for (idx.y = 0;(idx.y < _nH.y) && _run;idx.y += _hInc.y)
  {
  std::filesystem::path fPath = _dPath;
  char  buf[64];

    sprintf_s(buf,"HogelRow_%d.avi",idx.y);
    fPath /= buf;

    {
    cv::VideoCapture      c(fPath.string());
    
      idx.x = 0;
  
      while ((idx.x < _nH.x) && _run)
      {
      cv::Mat img;

        {
        uint32_t          i(0);

          while (i < _hInc.x)
          {
            c >> img;
            i++;
            idx.x++;
          }
        }
      }

      c.release();
    }

    std::cout << ".";
  }

  std::cout << std::endl;
  std::cout << "Finished loading radiance image" << std::endl;
}


//---------------------------------------------------------------------
// init
//---------------------------------------------------------------------
int RadImage::init(void)
{
int rc = 0;

  _aR   = (float)_nH.x / (float)_nH.y;

  if (_nH.x > _nH.y)
  {
    _vS.x = glm::min(_nH.x,(int)MaxViewSize);
    _vS.y = (int)((float)_vS.x / _aR);
  }
  else
  {
    _vS.y = glm::min(_nH.y,(int)MaxViewSize);
    _vS.x = (int)((float)_vS.y * _aR);
  }

  _nV = glm::min(_hS,glm::ivec2(MaxNumViews));

  _hInc   = glm::vec2((float)_nH.x / (float)_vS.x,(float)_nH.y / (float)_vS.y);

  std::cout << "Num Views: " << _nV.x << "," << _nV.y << std::endl;
  std::cout << "View Size: " << _vS.x << "," << _vS.y << std::endl;
  std::cout << std::endl;

  std::cout << "Allocating memory" << std::endl;

  {
  glm::ivec2 idx(0);
  uint32_t   i(0);
  cv::Mat    img(_vS.y,_vS.x,CV_8UC3);
  cv::Scalar clr(255,221,244); // pink lace

    _matArray.reserve(_nV.x * _nV.y);

    for (idx.y = 0;idx.y < _nV.y;idx.y++)
    {
      for (idx.x = 0;idx.x < _nV.x;idx.x++)
      {
        _matArray[i].create(_vS.y,_vS.x,CV_8UC3);
        _matArray[i].setTo(clr);
        i++;
      }  
    }  
  }

  return rc;
}


//---------------------------------------------------------------------
// RadImage
//---------------------------------------------------------------------
RadImage::RadImage(void) :  Core::Thread(),
                            _matArray(),
                            _dPath(),
                            _nH(0),
                            _hS(0),
                            _nV(0),
                            _vS(0),
                            _aR(0),
                            _hInc(0)
{
}


//---------------------------------------------------------------------
// ~RadImage
//---------------------------------------------------------------------
RadImage::~RadImage()
{

}

