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

// Hogel.h
// Thomas Burnett

#pragma once

//---------------------------------------------------------------------
// Includes
// System
#include <vector>

// 3rdPartyLibs
#include <glm/glm.hpp>
#include <glm/ext.hpp>

// Lightfield

//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace HogelDef
  {
    class Hogel 
    {
      // Defines
      private:
      protected:
      public:

      // Members
      private:
      protected:        
      public:   
        glm::ivec2    _idx; // the (X,Y) index of this hogel in the hogel plane
        glm::vec2     _vC;  // the distance, in pixels, from the hogel center to the hogel plane's minimum extent
        glm::mat4     _mH;  // the transform matrix for this hogel, in normalized hogel plane space ([-0.5,0.5] in each dimension)

      // Methods
      private:
      protected:
      public:

        Hogel(const glm::ivec2 &idx,const glm::vec2 &vC,const glm::mat4 &mH) : _idx(idx),
                                                                               _vC(vC),
                                                                               _mH(mH)
        {};

        Hogel(const glm::ivec2 &idx,const glm::vec2 &vC) : _vC(vC),
                                                           _mH(1)
        {};

        Hogel(void) : _idx(0),
                      _vC(0),
                      _mH(1)
        {};
    };

    typedef std::vector<Hogel> HogelLst;
  };
};
//---------------------------------------------------------------------
