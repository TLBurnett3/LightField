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

// Texture.cpp
// Thomas Burnett


//---------------------------------------------------------------------
// Includes

// LightField
#include "Render/Texture.h"

using namespace Lf;
using namespace Render;
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// upload
//---------------------------------------------------------------------
void Texture::upload(const uint8_t *pI,
                     const uint16_t w,const uint16_t h,const uint16_t bpp,
                     const GLint f)
{
GLint iFmt  = GL_RGB;
#ifndef _GLES2
GLint fmt   = f ? f : GL_BGR;
#else
GLint fmt   = GL_RGB;
#endif

  if (!_tId)
    glGenTextures(1,&_tId);
   
  glBindTexture(GL_TEXTURE_2D,_tId);

  if (bpp == 4)
  {
    iFmt = GL_RGBA;
#ifndef _GLES2
    fmt  = f ? f : GL_BGRA;
#else
    fmt  = f ? f : GL_RGBA;
#endif
  }  
  else if (bpp == 1)
  {
#ifndef _GLES2
    iFmt = GL_RED;
    fmt  = f ? f : GL_RED;
#else
    iFmt = GL_LUMINANCE;
    fmt  = f ? f : GL_LUMINANCE;
#endif
  }
  
  _iDim = glm::ivec3(w,h,bpp);

  if ((w & 0x3) == 0)
  {
    glPixelStorei(GL_PACK_ALIGNMENT,4);
    glPixelStorei(GL_UNPACK_ALIGNMENT,4);
  }
  else if ((w & 0x1) == 0)
  {
    glPixelStorei(GL_PACK_ALIGNMENT,2);
    glPixelStorei(GL_UNPACK_ALIGNMENT,2);
  }
  else
  {
    glPixelStorei(GL_PACK_ALIGNMENT,1);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
  }
   

#ifndef _GLES2
  if (fmt == GL_RED)
  {
  GLint swizzleMask[] = {GL_RED,GL_RED,GL_RED,GL_ONE};   
  
    glTexImage2D(GL_TEXTURE_2D,0,iFmt,w,h,0,fmt,GL_UNSIGNED_BYTE,pI);
    glTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_SWIZZLE_RGBA,swizzleMask);
  }
  else
#endif
    glTexImage2D(GL_TEXTURE_2D,0,iFmt,w,h,0,fmt,GL_UNSIGNED_BYTE,pI);

  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);  

  glBindTexture(GL_TEXTURE_2D,0);
}


//---------------------------------------------------------------------
// upload
//---------------------------------------------------------------------
void Texture::upload(cv::Mat &img)
{
GLint iFmt  = GL_RGB;
#ifndef _GLES2
GLint fmt   = GL_BGR;
#else
GLint fmt   = GL_RGB;
#endif

  if (!_tId)
    glGenTextures(1,&_tId);
   
  glBindTexture(GL_TEXTURE_2D,_tId);

  if (img.channels() == 4)
  {
    iFmt = GL_RGBA;
#ifndef _GLES2
    fmt  = GL_BGRA;
#else
    fmt  = GL_RGBA;
#endif 
  }  
  else if (img.channels() == 1)
  {
#ifndef _GLES2
    iFmt = GL_RED;
    fmt  = GL_RED;
#else
    iFmt = GL_LUMINANCE;
    fmt  = GL_LUMINANCE;
#endif
  }
  
  _iDim = glm::ivec3(img.cols,img.rows,img.channels());

  if ((_iDim.x & 0x3) == 0)
  {
    glPixelStorei(GL_PACK_ALIGNMENT,4);
    glPixelStorei(GL_UNPACK_ALIGNMENT,4);
  }
  else if ((_iDim.x & 0x1) == 0)
  {
    glPixelStorei(GL_PACK_ALIGNMENT,2);
    glPixelStorei(GL_UNPACK_ALIGNMENT,2);
  }
  else
  {
    glPixelStorei(GL_PACK_ALIGNMENT,1);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
  }
   
#ifndef _GLES2
  if (fmt == GL_RED)
  {
  GLint swizzleMask[] = {GL_RED,GL_RED,GL_RED,GL_ONE};   
  
    if ((img.elemSize() / img.channels()) == 1)
      glTexImage2D(GL_TEXTURE_2D,0,iFmt,_iDim.x,_iDim.y,0,fmt,GL_UNSIGNED_BYTE,img.data);
    else
      glTexImage2D(GL_TEXTURE_2D,0,iFmt,_iDim.x,_iDim.y,0,fmt,GL_UNSIGNED_SHORT,img.data);

    glTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_SWIZZLE_RGBA,swizzleMask);
  }
  else
#endif
  {
    if ((img.elemSize() / img.channels()) == 1)
      glTexImage2D(GL_TEXTURE_2D,0,iFmt,_iDim.x,_iDim.y,0,fmt,GL_UNSIGNED_BYTE,img.data);
    else
      glTexImage2D(GL_TEXTURE_2D,0,iFmt,_iDim.x,_iDim.y,0,fmt,GL_UNSIGNED_SHORT,img.data);
  }

  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);  
//  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
//  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);  

  glBindTexture(GL_TEXTURE_2D,0);
}


//---------------------------------------------------------------------
// Texture 
//---------------------------------------------------------------------
Texture::Texture() : _tId(0),
                     _iDim(0),
                     _mProp(0)
{
}


//---------------------------------------------------------------------
// ~Texture 
//---------------------------------------------------------------------
Texture::~Texture()
{
  if (_tId > 0)
    glDeleteTextures(1,&_tId);
}
