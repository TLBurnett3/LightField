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

// SliceNDice.cpp 
// Thomas Burnett

//---------------------------------------------------------------------
// Includes
// System
#include <iostream>
#include <stdio.h>

// 3rdPartyLibs

// LightField
#include "Tasks/SliceNDice.h"

using namespace Lf;
using namespace Task;
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// process
//---------------------------------------------------------------------
void SliceNDice::process(cv::Mat &img,glm::ivec2 &idx)
{ 
  for (size_t y = 0;y < _yN;y++)
  {
    for (size_t x = 0;x < img.cols;x++)
    {
    cv::Vec3b c = img.at<cv::Vec3b>(_yS + y,x);

      _imgArray[y][x].at<cv::Vec3b>(idx.y,idx.x) = c;
    }
  }
}


//---------------------------------------------------------------------
// writeAVIs()
//---------------------------------------------------------------------
void SliceNDice::writeAVIs(void)
{ 
std::filesystem::path   fPath  = _dPath;
int                     fourcc = cv::VideoWriter::fourcc('M','P','4','3');

  if (!std::filesystem::exists(fPath))
    std::filesystem::create_directory(fPath);

  for (size_t y = 0;y < _yN;y++)
  {
  std::filesystem::path   filePath  = fPath;
  cv::VideoWriter         videoWriter;
  cv::Size                sz(_imgArray[y][0].cols,_imgArray[y][0].rows);

  char buf[16];

    sprintf(buf,"_%zd.avi",_yS + y);

    filePath /= _fName;
    filePath += buf;

    std::cout << "Writing: " << filePath << " ";

    videoWriter.open(filePath.string().c_str(),fourcc,60,sz,true);

    for (size_t x = 0;x < _imgArray[y].size();x++)
    {
    cv::Vec3b c = _imgArray[y][x].at<cv::Vec3b>(sz.height/2,sz.width/2);

      _proofImg.at<cv::Vec3b>(_yS + y,x) = c;

      videoWriter << _imgArray[y][x];
    }

    videoWriter.release();

    //_pImageCache->insert("SliceProof",_proofImg);

    {
    std::filesystem::path fName = _dPath;

      fName /= "..";
      fName /= "SliceProof.png";

      cv::imwrite(fName.string(),_proofImg);
    }

    std::cout << "Done." << std::endl;
  }
}


//---------------------------------------------------------------------
// init
//---------------------------------------------------------------------
void SliceNDice::init(const glm::ivec2 &nH,const glm::ivec2 &hS,const uint16_t mS)
{
uint64_t nG = (uint64_t)mS * 1024 * 1024 * 1024;
uint64_t nB = (uint64_t)nH.x * (uint64_t)hS.x * (uint64_t)hS.y * (uint64_t)3;
uint64_t nR = glm::min(nG / nB,(uint64_t)nH.y);

  std::cout << "Slice Memory (bytes): " << nG << std::endl;
  std::cout << "Slice Row (bytes): " << nB << std::endl;
  std::cout << "Slice Rows : " << nR << std::endl;

  {
  cv::Scalar clr   = cv::Scalar(255,221,244); // pink lace

    _proofImg.create(nH.y,nH.x,CV_8UC3);
    _proofImg.setTo(clr);
  }

  _imgArray.resize(nR);

  for (uint64_t i = 0;i < nR;i++)
  {
    _imgArray[i].resize(nH.x);

    for (uint16_t j = 0;j < nH.x;j++)
      _imgArray[i][j].create(hS.y,hS.x,CV_8UC3);

    std::cout << "Slice Row: " << i << " reserved" << std::endl;
  }
}

