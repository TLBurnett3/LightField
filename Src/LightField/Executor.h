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

// 3rdPartyLibs
#include <GLFW/glfw3.h>

// LightField
#include "Core/Job.h"

#include "Render/Camera.h"
#include "Render/ModMan.h"
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Classes
namespace Lf
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
      Lf::Core::Job   _job;
      GLFWwindow      *_pWindow;

      Render::ModMan  _modMan;

    public:   

    // Methods
    private:
    protected:
      int parseJob(const char *pCfg);

      GLFWwindow *Executor::initWindow(const glm::ivec2 wD,const char *pStr,GLFWwindow *pShared,int fps,bool visible);

      void renderHogel(Render::Camera &camera,const glm::vec3 &vP,const glm::mat4 &mT);

      int renderDoubleFrustum(void);
      int renderObliqueSliceDice(void);

      void GLInfo(void);
    public:

      int   init(const char *pCfg);
      int   exec(void);
      void  destroy(void);

      Executor(void);
      ~Executor();
  };
};
//---------------------------------------------------------------------

