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

// Executor.h
// Thomas Burnett

#pragma once

#include "RenderGL/Def.h"

//---------------------------------------------------------------------
// Includes
// System
#include <filesystem>
#include <vector>

// 3rdPartyLibs
#include <GLFW/glfw3.h>

// LightField
#include "Core/ImgSet.h"
#include "RenderGL/VtxLst.h"
#include "RenderGL/Texture.h"
#include "RenderGL/VtxArrayObj.h"
#include "RenderGL/BasicShader.h"
#include "Aperture/Sar.h"

//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace Aperture
  {
    class Executor
    {
      // Defines
      private:
      protected:
        typedef std::vector<Sar *>  SarLst;

        enum
        {
          SAR_NONE = 0,
          SAR_CPP,
          SAR_MAX
        };
      public:

      // Members
      private:
      protected:
        GLFWwindow                *_pWindow;
        glm::ivec2                _wS;

        Core::ImgSet              _imgSet;
        
        cv::Mat                   _mcImg;
        glm::ivec2                _nI;
        glm::ivec2                _iS;

        RenderGL::BasicShader     *_pShader;
        RenderGL::VtxArrayObj     _vao;
        RenderGL::Texture         _mctex;

        SarLst                    _sarLst;
        uint32_t                  _sarIdx;

        float                     _aP;

      public:   

      // Methods
      private:
      protected:
        float map(float x,float in_min,float in_max,float out_min,float out_max)
        { return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min; }

        void GLInfo(void);

        int         initGLFW    (void);
        int         initGraphics(void);
        GLFWwindow  *initWindow (const glm::ivec2 wD,const char *pStr,GLFWwindow *pShared,int fps,bool visible);

        void motionUpdate(GLFWwindow *pW);

        int initSarNone (void);
        int initSarCpp  (void);

      public:
        void  setSarIdx(const uint32_t i)
        { 
          _sarIdx = (i >= SAR_MAX) ? 0 : i;  

          std::cout << "Switched to: " << _sarLst[_sarIdx]->name() << std::endl;
        }

        void  incAperture(const float a)
        { _aP = glm::clamp(_aP + a,0.0f,1.0f); }

            
        int   init(const char *pDir);
        int   exec(void);
        void  destroy(void);

        Executor(void);
        ~Executor();
    };
  };
};
//---------------------------------------------------------------------

