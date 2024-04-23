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
// Job.cpp

//---------------------------------------------------------------------

// Includes
// System
#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>

// 3rdPartyLibs
#include "glm/gtc/type_ptr.hpp"

// LightField
#include "MvPU/Job.h"

using namespace Lf;
using namespace MvPU;
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// printMatrix
//---------------------------------------------------------------------
void printMatrix(std::ostream &s,std::string idt,const char *str,const glm::mat4 &m)
{
  s << idt << str << std::endl;
  s << idt << " " << m[0].x << " " << m[0].y << " " << m[0].z << " " << m[0].w << std::endl; 
  s << idt << " " << m[1].x << " " << m[1].y << " " << m[1].z << " " << m[1].w << std::endl; 
  s << idt << " " << m[2].x << " " << m[2].y << " " << m[2].z << " " << m[2].w << std::endl; 
  s << idt << " " << m[3].x << " " << m[3].y << " " << m[3].z << " " << m[3].w << std::endl; 
}


//---------------------------------------------------------------------
// parseDocument
//---------------------------------------------------------------------
int Job::parseDocument(Core::JSon::Value &doc)
{
int rc = Core::Job::parseDocument(doc);

  if ((_renderer == "DF") || (_renderer == "DoubleFrustum"))
    _renderType = DoubleFrustum;
  else if ((_renderer == "BT") || (_renderer == "BowTie"))
    _renderType = BowTie;
  else
    assert(0);

  if (_renderType == BowTie)
  {
	  Core::JSon::parse(doc, "Algorithm",   _algorithm);
  
    if (!_algorithm.empty())
    {
      if (_algorithm == "Basic")
        _algorithmType = Basic;
      else if (_algorithm == "IntMap")
        _algorithmType = IntMap;
      else
      {
        std::cout << "Unknown Algorithm: " << _algorithm << std::endl;
        rc = -1;
      }
    }
  }

  if (_renderType == DoubleFrustum)
  {
  }
 
  return rc;
}



//---------------------------------------------------------------------
// Job
//---------------------------------------------------------------------
Job::Job(void) : Core::Job()
{

}


//---------------------------------------------------------------------
// ~Job
//---------------------------------------------------------------------
Job::~Job()
{

}

