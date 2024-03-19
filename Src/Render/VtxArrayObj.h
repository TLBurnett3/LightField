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

// VtxArrayObj.h
// Thomas Burnett

#pragma once

#ifndef _GLES2

//---------------------------------------------------------------------
// Includes

#include "Render/Object.h"
#include "Render/VtxLst.h"
//---------------------------------------------------------------------



//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace Render
  {
    class VtxArrayObj : public Object
    { 
      private:
      protected:
      public:
 
      private:
      protected:
        GLuint            _idVAO;
        GLuint            _idVBO;
        GLuint            _idIBO;

      public:

      private:
      protected:
 

      public:   
    
        void  render  (void)
        { 
          glBindVertexArray(_idVAO); 

          if (_idIBO)
            glDrawElements(_mode,(GLsizei)_num,GLZ_TYPE,0);
          else
            glDrawArrays(_mode,0,(GLsizei)_num); 

          glBindVertexArray(0); 
        }

        void  upload(const VtxVLst   &vLst,const IdxLst &iLst,const GLuint mode = GL_TRIANGLES);
        void  upload(const VtxVTLst  &vLst,const IdxLst &iLst,const GLuint mode = GL_TRIANGLES);
        void  upload(const VtxVNTLst &vLst,const IdxLst &iLst,const GLuint mode = GL_TRIANGLES);
        void  upload(const VtxVNLst  &vLst,const IdxLst &iLst,const GLuint mode = GL_TRIANGLES);

        void  upload(const VtxVLst   &vLst,const GLuint mode = GL_TRIANGLES);
        void  upload(const VtxVTLst  &vLst,const GLuint mode = GL_TRIANGLES);
        void  upload(const VtxVNTLst &vLst,const GLuint mode = GL_TRIANGLES);
        void  upload(const VtxVNLst  &vLst,const GLuint mode = GL_TRIANGLES);


        VtxArrayObj() :  Object(),
                         _idVAO(0),
                         _idVBO(0),
                         _idIBO(0)
        {}

        virtual ~VtxArrayObj();
    };
  };
};
//---------------------------------------------------------------------


#endif