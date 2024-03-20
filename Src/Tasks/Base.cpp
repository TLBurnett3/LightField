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

// Base.cpp 
// Thomas Burnett


//---------------------------------------------------------------------
// Includes
// System

// 3rdPartyLibs

// LightField
#include "Tasks/Base.h"

using namespace Lf;
using namespace Task;
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// exec
//---------------------------------------------------------------------
void Base::exec(void)
{
  while (_run || !_imgQ.empty())
  {
   SpImg spImg(0);

    {
    std::unique_lock<std::mutex> lock(_access);

      _workCondition.wait(lock,[this]{return ((_run == false) | !_imgQ.empty()); });  

       spImg = _imgQ.front();
      _imgQ.pop();
    }

    if (spImg)
      process(spImg->first,spImg->second);
  }
}


//---------------------------------------------------------------------
// Base
//---------------------------------------------------------------------
Base::Base(const char *pN) :_tName(pN),
                            _imgQ(),
                            _access(),
                            _workCondition()
{
}


//---------------------------------------------------------------------
// ~Base
//---------------------------------------------------------------------
Base::~Base()
{

}

