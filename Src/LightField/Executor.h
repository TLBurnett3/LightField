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
#include "Core/Job.h"
#include "Tasks/Base.h"
#include "Render/Camera.h"
#include "Render/Shader.h"
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
      typedef std::vector<Task::Base *> TaskList;
    public:

    // Members
    private:
    protected:
      Lf::Core::Job   _job;
      GLFWwindow      *_pWindow;

      Render::ModMan  _modMan;
      Render::Shader  _shader;

      TaskList        _imgTaskLst;
      TaskList        _dthTaskLst;

    public:   

    // Methods
    private:
    protected:
      int parseJob(const char *pCfg);

      GLFWwindow *Executor::initWindow(const glm::ivec2 wD,const char *pStr,GLFWwindow *pShared,int fps,bool visible);

      void renderHogel  (Render::Camera &camera,const glm::vec3 &vI);
      void renderOblique(Render::Camera &camera,const glm::vec2 &rA);

      int renderDoubleFrustumPlane     (void);
      int renderObliquePlane           (void);
      void renderObliqueAndSlice       (void);


      void fetchHogelAndQueue(glm::ivec2 idx);

      void GLInfo(void);

      int  loadModels (std::filesystem::path &cPath);
      int  loadShaders(std::filesystem::path &cPath);
      int  createTasks(void);

      void taskWait(Task::Base *pT);
      void taskSync(void);


    public:

      int   init(const char *pCfg);
      int   exec(void);
      void  destroy(void);

      Executor(void);
      ~Executor();
  };
};
//---------------------------------------------------------------------

