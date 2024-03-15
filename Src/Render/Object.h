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
// Object.h

#pragma once

//---------------------------------------------------------------------
// Includes
#include <vector>

#include "Render/Def.h"
#include "Render/VtxLst.h"
//---------------------------------------------------------------------



//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace Render
  {
    class Object
    { 
      private:
      protected:
      public:
 
      private:
      protected:
        GLZ               _num;
      
        glm::vec3         _vMin;
        glm::vec3         _vMax;

        GLenum            _mode;
        GLenum            _usage;
      public:

      private:
      protected:
 
        void  checkBounds(const glm::vec3 &v)
        {
          _vMin = glm::min(_vMin,v);
          _vMax = glm::max(_vMax,v);
        }

      public:   
        GLZ       size(void)
        { return _num; }

        glm::vec3 vMax(void)
        { return _vMax; }

        glm::vec3 vMin(void)
        { return _vMin; }

        glm::vec3 vDim(void)
        { return (_vMax - _vMin); }

        bool  isUploaded(void)
        { return _num ? true : false; }

        virtual void  render  (void) = 0;

        virtual void  upload(const VtxVLst   &vLst,const IdxLst &iLst,const GLuint mode = GL_TRIANGLES)
        { assert(0); }

        virtual void  upload(const VtxVTLst  &vLst,const IdxLst &iLst,const GLuint mode = GL_TRIANGLES)
        { assert(0); }

        virtual void  upload(const VtxVNTLst &vLst,const IdxLst &iLst,const GLuint mode = GL_TRIANGLES)
        { assert(0); }

        virtual void  upload(const VtxVNLst &vLst,const IdxLst &iLst,const GLuint mode = GL_TRIANGLES)
        { assert(0); }

        virtual void  upload(const VtxVLst   &vLst,const GLuint mode = GL_TRIANGLES)
        { assert(0); }

        virtual void  upload(const VtxVTLst  &vLst,const GLuint mode = GL_TRIANGLES)
        { assert(0); }

        virtual void  upload(const VtxVNTLst &vLst,const GLuint mode = GL_TRIANGLES)
        { assert(0); }

        virtual void  upload(const VtxVNLst  &vLst,const GLuint mode = GL_TRIANGLES)
        { assert(0); }

        Object() : _num(0),
                   _mode(GL_TRIANGLES),
                   _usage(GL_DYNAMIC_DRAW),
                   _vMin(FLT_MAX),
                   _vMax(-FLT_MAX)
        {
        }

        virtual ~Object() 
        {
        }
    };
  };
};
//---------------------------------------------------------------------
