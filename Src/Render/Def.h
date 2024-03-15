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

// Def.h
// Thomas Burnett


#pragma once

//---------------------------------------------------------------------
// Includes
// System
#ifdef _WIN32
//#define GLEW_STATIC
#include <GL/glew.h>
#else
//#include <OpenGL/GL.h>
#define __gl_h_
#define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#endif

// 3rdPartyLibs
//#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/ext.hpp>
//---------------------------------------------------------------------

namespace Lf
{
  namespace Render
  {
    //---------------------------------------------------------------------
    // Defines
      enum ShaderAttributes_Def
      {
        PositionAttribute   = 0,
        TexCoordAttribute   = 1,  
        DimensionAttribute  = 1,  
        ColorAttribute      = 1,
        NormalAttribute     = 2,
      };

    // Definitions
    #ifdef _GLES11
    typedef GLushort GLZ;
    #define GLZ_TYPE GL_UNSIGNED_SHORT
    #else
    typedef GLuint GLZ;
    #define GLZ_TYPE GL_UNSIGNED_INT
    #endif
    //---------------------------------------------------------------------
  };
};
