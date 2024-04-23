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

// LgtObj.h
// Thomas Burnett

#pragma once

//---------------------------------------------------------------------
// Includes
// System
#include <memory>

// 3rdPartyLibs

// Lightfield

//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Classes
namespace Lf
{
  class LgtObj
  {
    // Defines
    private:
    protected:
    public:

    // Members
    private:
    protected:
    public:                                                         
      glm::vec3 _vPosition;                              
      glm::vec4 _cAmbient;                               
      glm::vec4 _cDiffuse;                               
      glm::vec4 _cSpecular;                              
      float     _att;                           

    // Methods
    private:
    protected:
    public:
  
      LgtObj(void) :  _vPosition(0),     
                      _cAmbient(1),
                      _cDiffuse(0),
                      _cSpecular(0),
                      _att(0)
      {}

      LgtObj(const glm::vec3 &vP,
             const glm::vec4 &cA,
             const glm::vec4 &cD, 
             const glm::vec4 &cS,
             const float     att) : _vPosition(vP),
                                    _cAmbient(cA),
                                    _cDiffuse(cD),
                                    _cSpecular(cS),
                                    _att(att)
      {}

      virtual ~LgtObj()
      {}
  };

  typedef std::shared_ptr<LgtObj> SpLgtObj;
};
//---------------------------------------------------------------------

