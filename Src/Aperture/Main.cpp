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

// Thomas Burnett
// Main.cpp 

//---------------------------------------------------------------------
// Includes
#include <string>
#include <iostream>

// 3rd Party Libs

// LightField
#include "Aperture/Executor.h"
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// main
//---------------------------------------------------------------------
int main(int argc,char *argv[])
{
int                      rc  = 0;
char                     *p  = 0;
Lf::Aperture::Executor  e;

  std::cout << "Usage: Aperture <path to .png files>\n";

  if (argc > 1)
    p = argv[1];
  
  std::cout << "Aperture Initialization" << std::endl;
  if (p)
    std::cout << "Png Path: " << p << std::endl;

  if (p)
  {
    rc = e.init(p);

    if (rc == 0)
      e.instructions();

    if (rc == 0)
      rc = e.exec();

    e.destroy();
  }

  std::cout << "Aperture Exit: RC " << rc << std::endl;

  return rc;
}

