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

// SarShader.h
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
	  class SarShader : public RenderGL::BasicShader
	  {
	    // Defines
      private:
      protected:
        enum
        {
          HOMOGRAPHIES_BINDING_POINT = 1
        };

      public:

      // Members
      private:
      protected: 
        GLint    _locImageIndex;
        GLint    _locImageSize;
        GLint    _locNumImages;
        GLint    _locAperture;
        GLint    _idxHomographies;
        GLuint   _homographyBuffer;

      public:

      // Methods
      private:
      protected:

      public:
        EXPORT void bindImageIndex(const glm::ivec2 &idx) const
        { 
          glUniform2i(_locImageIndex,idx.x,idx.y); 
        }

        EXPORT void bindImageSize(const glm::ivec2 &iS) const
        { 
          glUniform2i(_locImageSize,iS.x,iS.y); 
        }

        EXPORT void bindNumImages(const glm::ivec2 &nI) const
        { 
          glUniform2i(_locNumImages,nI.x,nI.y); 
        }

        EXPORT void bindAperture(const float a) const
        { 
          glUniform1f(_locAperture,a); 
        }

        EXPORT void bindHomographies(const std::vector<glm::mat4> *pMHLst) const
        { 
        size_t n = pMHLst->size();

          glBufferData(GL_UNIFORM_BUFFER,sizeof(glm::mat4) * n,pMHLst->data(),GL_DYNAMIC_DRAW);
          glBindBufferBase(GL_UNIFORM_BUFFER,HOMOGRAPHIES_BINDING_POINT,_homographyBuffer);
        }

        EXPORT virtual int compile(void);
 
        EXPORT SarShader(const char *pName);
        EXPORT virtual ~SarShader();
	  };
  };
};

//---------------------------------------------------------------------