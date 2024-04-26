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
#include "Viewer/Executor.h"
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// main
//---------------------------------------------------------------------
int main(int argc,char *argv[])
{
int                   rc  = 0;
char                  *p  = 0;
uint32_t              gb  = 24;
float                 fov = 90.0f;
Lf::Viewer::Executor  e;

  std::cout << "Usage: LfViewer <path to .avi files> -gb <gigabyes> -fov <fov>\n";

  if (argc > 1)
    p = argv[1];

  if (argc > 2)
  {
  uint32_t i = 2;

    while ((i + 2) <= argc)
    {
      if (strcmp(argv[i+0],"-gb") == 0)
        gb = atoi(argv[i + 1]);
      if (strcmp(argv[i+0],"-fov") == 0)
        fov = atof(argv[i + 1]);

      i += 2;
    }
  }
    
  std::cout << "LfViewer Initialization" << std::endl;
  if (p)
    std::cout << "AVI Path: " << p << std::endl;
  std::cout << "  Memory: " << gb << " gigabytes" << std::endl;
  std::cout << "     FoV: " << fov << std::endl;

  if (p)
  {
    rc = e.init(p,gb,fov);

    if (rc == 0)
      rc = e.exec();

    e.destroy();
  }

  std::cout << "LfViewer Exit: RC " << rc << std::endl;

  return rc;
}

