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

// WriteImg.cpp 
// Thomas Burnett


//---------------------------------------------------------------------
// Includes
// System
#include <filesystem>
#include <stdio.h>

// 3rdPartyLibs

// Hogel Tasks
#include "Tasks/WriteImg.h"

using namespace Lf;
using namespace Task;
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Globals
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// process
//---------------------------------------------------------------------
void WriteImg::process(cv::Mat &img,glm::ivec2 &idx)
{
std::filesystem::path   fPath = _dPath;
cv::Mat                 iImg;
char                    buf[256];

  sprintf(buf,_fName.c_str(),idx.y,idx.x);

  fPath /= buf;
  fPath += ".";
  fPath += _ext;
      
  if (img.channels() == 3)
    cv::imwrite(fPath.string(),img);
  else
  {
  cv::Mat       dImg(img.rows,img.cols,CV_16UC1);
  float         *p    = (float *)img.data;
  uint16_t      *d    = (uint16_t *)dImg.data;
  float         *pEnd = p + ((uint16_t)img.rows * (uint16_t)img.cols);                             

    while (p < pEnd)
    {
      *d = toUShort(*p);

      d++;
      p++;
    }  

    cv::imwrite(fPath.string(),dImg); 
  }
}
