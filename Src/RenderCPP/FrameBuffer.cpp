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

// FrameBuffer.cpp 
// Thomas Burnett


//---------------------------------------------------------------------
// Includes
// System
#include <iostream>

// 3rdPartyLibs
#include <opencv2/imgproc.hpp>

// Lightfield
#include "RenderCPP/FrameBuffer.h"

using namespace Lf;
using namespace RenderCPP;
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// create
//---------------------------------------------------------------------
int FrameBuffer::create(const glm::ivec2 &nH,const glm::ivec2 &hS)
{
cv::Scalar      clr(255,221,244,0); // pink lace
cv::Scalar      dth(std::numeric_limits<float>::max());
size_t          n = nH.y * nH.x;

  std::cout << "Creating Framebuffers" << std::endl;

  _fbLst.resize(n);
  _hS = hS;

  for (size_t i = 0;i < n;i++)
  {
    _fbLst[i].first.create(hS.y,hS.x,CV_8UC4);
    _fbLst[i].second.create(hS.y,hS.x,CV_32FC1);

    _fbLst[i].first.setTo(clr);
    _fbLst[i].second.setTo(dth);
  }

  return 0;
}


//---------------------------------------------------------------------
// FrameBuffer
//---------------------------------------------------------------------
FrameBuffer::FrameBuffer(void) :  _fbLst(),
                                  _pImg(0),
                                  _pDth(0)
{
}


//---------------------------------------------------------------------
// ~FrameBuffer
//---------------------------------------------------------------------
FrameBuffer::~FrameBuffer()
{
  // do not delete pImg or pDth
}

