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

#include "Render/Def.h"

//---------------------------------------------------------------------
// Includes
// System
#include <filesystem>
#include <vector>

// 3rdPartyLibs
#include <GLFW/glfw3.h>

// LightField
#include "Viewer/RadImage.h"
#include "Render/VtxLst.h"
#include "Render/Texture.h"
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace Viewer
  {
    class Executor
    {
      // Defines
      private:
      protected:
      public:

      // Members
      private:
      protected:
        GLFWwindow                *_pWindow;
        RadImage                  *_pRadImage;
        glm::ivec2                _wS;

        glm::vec2                 _vA;
        float                     _fov;

        Render::VtxVNTLst         _quad;
        Render::Texture           _tex;

      public:   

      // Methods
      private:
      protected:
        float map(float x,float in_min,float in_max,float out_min,float out_max)
        { return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min; }

        GLFWwindow *Executor::initWindow(const glm::ivec2 wD,const char *pStr,GLFWwindow *pShared,int fps,bool visible);

        void GLInfo(void);

        int  initGLFW(void);
        int  initGraphics(void);

        void motionUpdate(GLFWwindow *pW);

      public:
        void  setViewAngle(const glm::vec2 &vA)
        { 
        glm::vec2 hA = glm::vec2(_fov * 0.5f);

          _vA = vA; 
          _vA = glm::clamp(_vA,-hA,hA);
        }

        void  incViewAngle(const glm::vec2 &vA)
        {
        glm::vec2 hA = glm::vec2(_fov * 0.5f);

          _vA += vA;
          _vA = glm::clamp(_vA,-hA,hA);
        }

        void  fetchView(const glm::ivec2 &idx,cv::Mat &img);
        int   init(const char *pCfg,const uint32_t g);
        int   exec(void);
        void  destroy(void);

        Executor(void);
        ~Executor();
    };
  };
};
//---------------------------------------------------------------------

