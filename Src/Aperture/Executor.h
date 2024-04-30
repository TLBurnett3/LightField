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
#include "Core/Timer.h"
#include "RenderGL/VtxLst.h"
#include "RenderGL/Texture.h"
#include "RenderGL/VtxArrayObj.h"
#include "RenderGL/BasicShader.h"
#include "Aperture/Sar.h"
#include "Aperture/MapShader.h"
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
        typedef std::vector<Sar *>      SarLst;
        typedef std::vector<glm::mat4>  MatrixLst;

        enum
        {
          SAR_NONE = 0,
          SAR_CPP,
          SAR_CV,
          SAR_GL,
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
        RenderGL::Texture         _mcTex;

        MapShader                 *_pMapShader;

        SarLst                    _sarLst;
        uint32_t                  _sarIdx;

        float                     _aP;
        glm::ivec2                _iIdx;
        float                     _focus;

        MatrixLst                 _mHLst;
        bool                      _bHLst;

        Core::Timer               _timer;
        uint32_t                  _nC;
        float                     _fps;

      public:   

      // Methods
      private:
      protected:
        float map(float x,float in_min,float in_max,float out_min,float out_max)
        { return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min; }

        void calcFps(void)
        { 
        float s = (float)_timer.seconds();
  
          _nC++;        
          _fps = (float)_nC / s;
        }
           
        void resetFps(void)
        { 
          _timer.start();
          _nC = 0;
          _fps = 0;
        }

        void updateWindowTitle(void);

        void GLInfo(void);

        int         initGLFW    (void);
        int         initGraphics(void);
        GLFWwindow  *initWindow (const glm::ivec2 wD,const char *pStr,GLFWwindow *pShared,int fps,bool visible);

        void motionUpdate(GLFWwindow *pW);

        void  updateHomographies(void);

        void  renderSar(glm::mat4 &mP,glm::mat4 &mV,RenderGL::Texture &mcTex,RenderGL::VtxArrayObj &vao);
        void  renderMap(glm::mat4 &mP,glm::mat4 &mV,RenderGL::Texture &mcTex,RenderGL::VtxArrayObj &vao); 

        int initHomographies(void);

        int initMapShader(void);

        int initSarNone (void);
        int initSarCpp  (void);
        int initSarCV   (void);
        int initSarGL   (void);

      public:
         
        void  setSarIdx(const uint32_t i)
        { 
          _sarIdx = (i >= SAR_MAX) ? 0 : i; 
          _bHLst  = true;
          resetFps();

          std::cout << "Switched to: " << _sarLst[_sarIdx]->name() << std::endl;
        }

        void  incAperture(const float a)
        { 
          _aP = glm::clamp(_aP + a,0.0f,1.0f); 
          resetFps();
        }

        void  incFocus(const float f)
        { 
          _focus += f;
          _bHLst = true;
          resetFps();
        }

        void  incSubImgIdx(const glm::ivec2 &inc)
        { 
          _iIdx = glm::clamp(_iIdx +  inc,glm::ivec2(0),_nI -1); 
          resetFps();
        } 

        void reset(void)
        {
          _focus = 0,
          _aP    = 0;
          _iIdx  = _nI >> 1;
          _bHLst = true;

          resetFps();
        }  

        int   exec(void);

        int   init(const char *pDir);
        void  destroy(void);

        Executor(void);
        ~Executor();
    };
  };
};
//---------------------------------------------------------------------

