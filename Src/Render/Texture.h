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

// Texture.h
// Thomas Burnett

#pragma once


//---------------------------------------------------------------------
// Includes
// 3rdPartyLibs
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// LightField
#include "Render/Def.h"
//---------------------------------------------------------------------



//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace Render
  {
    class Texture 
    { 
      // Defines
      private:
      protected:
      public:
     
      // Members
      private:
      protected:
        GLuint              _tId;
        glm::ivec3          _iDim;
        glm::mat4           _mProp;

      public:

      // Methods
      private:
      protected:
      public:
        const bool isUploaded(void) const
        { return _iDim.z ? true : false; }

        const glm::ivec2 iDim(void) const 
        {  return glm::ivec2(_iDim); }

        int width(void) const
        { return _iDim.x; }

        int height(void) const
        { return _iDim.y; }

        int bpp(void) const 
        { return _iDim.z; }

        GLuint    textureId(void) const
        { return _tId; }

        void setProperties(const glm::mat4 &mP)
        { _mProp = mP; }

        const glm::mat4 &properties(void) const
        { return _mProp; }

        virtual void  bind(void)
        { glBindTexture(GL_TEXTURE_2D,_tId); }


        virtual void upload (const uint8_t *pI,
                             const uint16_t w,const uint16_t h,const uint16_t bpp,
                             const GLint f = 0);
 
        void upload(cv::Mat &img);

        Texture(void);
        virtual ~Texture();
    };
  };
};
//---------------------------------------------------------------------
