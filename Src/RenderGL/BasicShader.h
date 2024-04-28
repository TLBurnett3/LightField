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

// BasicShader.h
// Thomas Burnett


#pragma once

//---------------------------------------------------------------------
// Includes

// 3rdPartyLibs

// LightField
#include "RenderGL/Shader.h"
//---------------------------------------------------------------------

//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace RenderGL
  {
	  class BasicShader : public Shader
	  {
	    // Defines
      private:
      protected:
      public:

      // Members
      private:
      protected: 
        GLint    _locMatMVP;
        GLint    _locTexSampler;

      public:

      // Methods
      private:
      protected:

      public:
        EXPORT void setTextureSampler(const int t) const
        { glUniform1i(_locTexSampler,t); }

        EXPORT void bindMVP(const glm::mat4 &mT) const
        { glUniformMatrix4fv(_locMatMVP,1,false,glm::value_ptr(mT)); }

        EXPORT virtual int compile(void);
 
        EXPORT BasicShader(const char *pName);
        EXPORT virtual ~BasicShader();
	  };
  };
};

//---------------------------------------------------------------------