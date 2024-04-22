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

//---------------------------------------------------------------------
// Includes
#include "Core/Export.h"
#include "RenderGL/Object.h"
#include "RenderGL/VtxLst.h"
//---------------------------------------------------------------------



//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace RenderGL
  {
    class VtxBufferObj : public Object
    { 
      private:
      protected:
        typedef	void	(VtxBufferObj::*iRenderFunc)   (void);

      public:
 
      private:
        iRenderFunc _renderFunc;

      protected:
        GLuint            _idVBO;
        GLuint            _idIBO;

      public:

      private:
        void renderIV   (void);
        void renderIVT  (void);
        void renderIVN  (void);
        void renderIVNT (void);

        void renderVT  (void);
        void renderVD  (void);
        void renderV   (void);
        void renderVNT (void);

      protected:
 
      public:   
    
        EXPORT void  render  (void)
        { 
          assert(_renderFunc);
          (this->*_renderFunc)();
        }

  #ifdef tLibPCL
        void  upload(const pcl::PointCloud<pcl::PointXYZRGBA>::Ptr &cloud,const int mode);
  #endif

        EXPORT void  upload(const VtxVLst   &vLst,const IdxLst &iLst,const GLuint mode = GL_TRIANGLES);
        EXPORT void  upload(const VtxVTLst  &vLst,const IdxLst &iLst,const GLuint mode = GL_TRIANGLES);
        EXPORT void  upload(const VtxVNTLst &vLst,const IdxLst &iLst,const GLuint mode = GL_TRIANGLES);
        EXPORT void  upload(const VtxVNLst  &vLst,const IdxLst &iLst,const GLuint mode = GL_TRIANGLES);

        EXPORT void  upload(const VtxVLst   &vLst,const GLuint mode = GL_TRIANGLES);
        EXPORT void  upload(const VtxVTLst  &vLst,const GLuint mode = GL_TRIANGLES);
        EXPORT void  upload(const VtxVNTLst &vLst,const GLuint mode = GL_TRIANGLES);
        EXPORT void  upload(const VtxVNLst  &vLst,const GLuint mode = GL_TRIANGLES);


        EXPORT VtxBufferObj() :  Object(),
                                 _idVBO(0),
                                 _idIBO(0),
                                 _renderFunc(0)
        {}

        EXPORT virtual ~VtxBufferObj();
    };
  };
};
//---------------------------------------------------------------------
