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

// MapShader.h
// Thomas Burnett


#pragma once

//---------------------------------------------------------------------
// Includes

// 3rdPartyLibs

// LightField
#include "RenderGL/BasicShader.h"
//---------------------------------------------------------------------

//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace Aperture
  {
	  class MapShader : public RenderGL::BasicShader
	  {
	    // Defines
      private:
      protected:
      public:

      // Members
      private:
      protected: 
        GLint    _locImageIndex;
        GLint    _locNumImages;
        GLint    _locAperture;


      public:

      // Methods
      private:
      protected:

      public:
        EXPORT void bindImageIndex(const glm::ivec2 &idx) const
        { 
        glm::vec2 v = idx;

          glUniform2f(_locImageIndex,v.x,v.y); 
        }

        EXPORT void bindNumImages(const glm::ivec2 &nI) const
        { 
        glm::vec2 v = nI;

          glUniform2f(_locNumImages,v.x,v.y); 
        }

        EXPORT void bindAperture(const float a) const
        { 
          glUniform1f(_locAperture,a); 
        }

        EXPORT virtual int compile(void);
 
        EXPORT MapShader(const char *pName);
        EXPORT virtual ~MapShader();
	  };
  };
};

//---------------------------------------------------------------------