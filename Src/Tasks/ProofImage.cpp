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

// ProofImage.cpp 
// Thomas Burnett

//---------------------------------------------------------------------
// Includes
// System
#include <filesystem>
// 3rdPartyLibs

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/types.hpp>

// Hogel Render
#include "ProofImage.h"

using namespace Lf;
using namespace Task;
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Globals
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// create
//---------------------------------------------------------------------
void ProofImage::create(const glm::ivec2 &nH,const glm::ivec2 &hS,const uint16_t bpp)
{
  _nH = nH;
  _hS = hS;
  _iSize = (_nH * 3) + 10;

  if (bpp == 3)
  {
  cv::Scalar clr = cv::Scalar(255,221,244); // pink lace

    _proof.create(_iSize.y,_iSize.x, CV_8UC3);
    _proof.setTo(clr);
  }
  else
  {
  cv::Scalar clr = cv::Scalar(128);

    _proof.create(_iSize.y,_iSize.x, CV_16UC1);
    _proof.setTo(clr);
  }
}


//---------------------------------------------------------------------
// write
//---------------------------------------------------------------------
void ProofImage::write(void)
{
std::filesystem::path fName = _dPath;

  if (!_dPath.empty() && !std::filesystem::exists(_dPath))
    std::filesystem::create_directory(_dPath);

  fName /= _fName;
  fName += ".png";

  cv::imwrite(fName.string(),_proof);
}


//---------------------------------------------------------------------
// scatterHogel3
//---------------------------------------------------------------------
void ProofImage::scatterHogel3(cv::Mat &img,glm::ivec2 &idx)
{
cv::Point s(_nH.x + 5,_nH.y + 5);
cv::Point i(idx.x,idx.y);
cv::Point i0(0,0);
cv::Point i1(0,img.cols >> 1);
cv::Point i2(0,img.cols - 1);
cv::Point i3(img.rows >> 1,0);
cv::Point i4(img.rows >> 1,img.cols >> 1);
cv::Point i5(img.rows >> 1,img.cols - 1);
cv::Point i6(img.rows - 1,0);
cv::Point i7(img.rows - 1,img.cols >> 1);
cv::Point i8(img.rows - 1,img.cols - 1);
cv::Vec3b c0 = img.at<cv::Vec3b>(i0);
cv::Vec3b c1 = img.at<cv::Vec3b>(i1);
cv::Vec3b c2 = img.at<cv::Vec3b>(i2);
cv::Vec3b c3 = img.at<cv::Vec3b>(i3);
cv::Vec3b c4 = img.at<cv::Vec3b>(i4);
cv::Vec3b c5 = img.at<cv::Vec3b>(i5);
cv::Vec3b c6 = img.at<cv::Vec3b>(i6);
cv::Vec3b c7 = img.at<cv::Vec3b>(i7);
cv::Vec3b c8 = img.at<cv::Vec3b>(i8);

  i0 = i + cv::Point(0 * s.x,(0 * s.y));
  i1 = i + cv::Point(0 * s.x,(1 * s.y));
  i2 = i + cv::Point(0 * s.x,(2 * s.y));
  i3 = i + cv::Point(1 * s.x,(0 * s.y));
  i4 = i + cv::Point(1 * s.x,(1 * s.y));
  i5 = i + cv::Point(1 * s.x,(2 * s.y));
  i6 = i + cv::Point(2 * s.x,(0 * s.y));
  i7 = i + cv::Point(2 * s.x,(1 * s.y));
  i8 = i + cv::Point(2 * s.x,(2 * s.y));
    
  i0.y = _proof.rows - i0.y - 1;
  i1.y = _proof.rows - i1.y - 1;
  i2.y = _proof.rows - i2.y - 1;
  i3.y = _proof.rows - i3.y - 1;
  i4.y = _proof.rows - i4.y - 1;
  i5.y = _proof.rows - i5.y - 1;
  i6.y = _proof.rows - i6.y - 1;
  i7.y = _proof.rows - i7.y - 1;
  i8.y = _proof.rows - i8.y - 1;
  
  _proof.at<cv::Vec3b>(i0) = c0;
  _proof.at<cv::Vec3b>(i1) = c1;
  _proof.at<cv::Vec3b>(i2) = c2;
  _proof.at<cv::Vec3b>(i3) = c3;
  _proof.at<cv::Vec3b>(i4) = c4;
  _proof.at<cv::Vec3b>(i5) = c5;
  _proof.at<cv::Vec3b>(i6) = c6;
  _proof.at<cv::Vec3b>(i7) = c7;
  _proof.at<cv::Vec3b>(i8) = c8;
}

//---------------------------------------------------------------------
// scatterHogel1
//---------------------------------------------------------------------
void ProofImage::scatterHogel1(cv::Mat &img,glm::ivec2 &idx)
{
cv::Point s(_nH.x + 5,_nH.y + 5);
cv::Point i(idx.x,idx.y);
cv::Point i0(0,0);
cv::Point i1(0,img.cols >> 1);
cv::Point i2(0,img.cols - 1);
cv::Point i3(img.rows >> 1,0);
cv::Point i4(img.rows >> 1,img.cols >> 1);
cv::Point i5(img.rows >> 1,img.cols - 1);
cv::Point i6(img.rows - 1,0);
cv::Point i7(img.rows - 1,img.cols >> 1);
cv::Point i8(img.rows - 1,img.cols - 1);
uint16_t c0 = toUShort(img.at<float>(i0));
uint16_t c1 = toUShort(img.at<float>(i1));
uint16_t c2 = toUShort(img.at<float>(i2));
uint16_t c3 = toUShort(img.at<float>(i3));
uint16_t c4 = toUShort(img.at<float>(i4));
uint16_t c5 = toUShort(img.at<float>(i5));
uint16_t c6 = toUShort(img.at<float>(i6));
uint16_t c7 = toUShort(img.at<float>(i7));
uint16_t c8 = toUShort(img.at<float>(i8));

  i0 = i + cv::Point(0 * s.x,(0 * s.y));
  i1 = i + cv::Point(0 * s.x,(1 * s.y));
  i2 = i + cv::Point(0 * s.x,(2 * s.y));
  i3 = i + cv::Point(1 * s.x,(0 * s.y));
  i4 = i + cv::Point(1 * s.x,(1 * s.y));
  i5 = i + cv::Point(1 * s.x,(2 * s.y));
  i6 = i + cv::Point(2 * s.x,(0 * s.y));
  i7 = i + cv::Point(2 * s.x,(1 * s.y));
  i8 = i + cv::Point(2 * s.x,(2 * s.y));

  i0.y = _proof.rows - i0.y - 1;
  i1.y = _proof.rows - i1.y - 1;
  i2.y = _proof.rows - i2.y - 1;
  i3.y = _proof.rows - i3.y - 1;
  i4.y = _proof.rows - i4.y - 1;
  i5.y = _proof.rows - i5.y - 1;
  i6.y = _proof.rows - i6.y - 1;
  i7.y = _proof.rows - i7.y - 1;
  i8.y = _proof.rows - i8.y - 1;

  _proof.at<uint16_t>(i0) = c0;
  _proof.at<uint16_t>(i1) = c1;
  _proof.at<uint16_t>(i2) = c2;
  _proof.at<uint16_t>(i3) = c3;
  _proof.at<uint16_t>(i4) = c4;
  _proof.at<uint16_t>(i5) = c5;
  _proof.at<uint16_t>(i6) = c6;
  _proof.at<uint16_t>(i7) = c7;
  _proof.at<uint16_t>(i8) = c8;
}


//---------------------------------------------------------------------
// scatterOblique
//---------------------------------------------------------------------
void ProofImage::scatterOblique(cv::Mat &img,glm::ivec2 &idx)
{
cv::Point s(_nH.x + 5,_nH.y + 5);

  if (idx == glm::ivec2(0))
    img.copyTo(_proof(cv::Rect(0,0,img.cols,img.rows)));
  else if (idx == glm::ivec2(_hS.x >> 1,0))
    img.copyTo(_proof(cv::Rect(1 * s.x,0 * s.y,img.cols,img.rows)));
  else if (idx == glm::ivec2(_hS.x - 1,0))
    img.copyTo(_proof(cv::Rect(2 * s.x,0 * s.y,img.cols,img.rows)));
  else if (idx == glm::ivec2(0,_hS.y >> 1))
    img.copyTo(_proof(cv::Rect(0 * s.x,1 * s.y,img.cols,img.rows)));
  else if (idx == glm::ivec2(_hS.x >> 1,_hS.y >> 1))
    img.copyTo(_proof(cv::Rect(1 * s.x,1 * s.y,img.cols,img.rows)));
  else if (idx == glm::ivec2(_hS.x - 1,_hS.y >> 1))
    img.copyTo(_proof(cv::Rect(2 * s.x,1 * s.y,img.cols,img.rows)));
  else if (idx == glm::ivec2(0,_hS.y - 1))
    img.copyTo(_proof(cv::Rect(0 * s.x,2 * s.y,img.cols,img.rows)));
  else if (idx == glm::ivec2(_hS.x >> 1,_hS.y - 1))
    img.copyTo(_proof(cv::Rect(1 * s.x,2 * s.y,img.cols,img.rows)));
  else if (idx == glm::ivec2(_hS.x - 1,_hS.y - 1))
    img.copyTo(_proof(cv::Rect(2 * s.x,2 * s.y,img.cols,img.rows)));
}



//---------------------------------------------------------------------
// process
//---------------------------------------------------------------------
void ProofImage::process(cv::Mat &img,glm::ivec2 &idx)
{
  if (!img.empty())
  {
  bool  doW(false);

    if (_scatterType == HogelScatter)
    {
      if (img.channels() == 3)
        scatterHogel3(img,idx);
      else
        scatterHogel1(img,idx);

      if (idx.x == (_nH.x - 1))
        doW = true;
    }
    else
    {
      scatterOblique(img,idx);

      if (idx.x == (_hS.x - 1))
        doW = true;
    }
  
    if (doW)
      write();
  }
}

