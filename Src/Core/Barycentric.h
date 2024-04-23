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

// Barycentric.h
// Thomas Burnett

#pragma once

//---------------------------------------------------------------------
// Includes
// System

// 3rdPartyLibs
#include <glm/glm.hpp>

// Lightfield

//---------------------------------------------------------------------

//https://gamedev.stackexchange.com/questions/23743/whats-the-most-efficient-way-to-find-barycentric-coordinates

//---------------------------------------------------------------------
// Classes
namespace Lf
{
  class Barycentric
  {
    // Defines
    private:
    protected:
    public:

    // Members
    private:
    protected:      
      glm::vec2 _vA;
      glm::vec2 _v0;
      glm::vec2 _v1;

      float     _d00;
      float     _d01;
      float     _d11;

      float     _denomI;

    public:   

    // Methods
    private:
    protected:
    public:
      glm::vec3 coordinates(const glm::vec2 &vP) const
      {
      glm::vec2 v2    = vP - _vA;
      float     d20   = glm::dot(v2,_v0);
      float     d21   = glm::dot(v2,_v1);
      float     v     = (_d11 * d20 - _d01 * d21) * _denomI;
      float     w     = (_d00 * d21 - _d01 * d20) * _denomI;
      float     u     = 1.0f - v - w;
	    
        return glm::vec3(u,v,w);
      }
  
      Barycentric(const glm::vec2 &vA,const glm::vec2 &vB,const glm::vec2 &vC)
      {
        _vA     = vA;
        _v0     = vB - vA;
        _v1     = vC - vA;
        _d00    = glm::dot(_v0,_v0);
        _d01    = glm::dot(_v0,_v1);
        _d11    = glm::dot(_v1,_v1);
        _denomI = 1.0f / (_d00 * _d11 - _d01 * _d01);
      }
  };
};
//---------------------------------------------------------------------

