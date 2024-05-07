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
#include "Core/Job.h"
#include "Tasks/Base.h"
#include "HogelDef/Camera.h"
#include "RenderGL/PhongShader.h"
#include "RenderGL/Scene.h"
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
      Lf::Core::SpJob _spJob;
      GLFWwindow      *_pWindow;

      RenderGL::Scene        *_pScene;
      RenderGL::PhongShader  *_pShader;

      TaskList        _imgTaskLst;
      TaskList        _dthTaskLst;

    public:   

    // Methods
    private:
    protected:
      Task::Base    *findTask(const char *tName,TaskList &tLst);

      GLFWwindow    *initWindow(const glm::ivec2 wD,const char *pStr,GLFWwindow *pShared,int fps,bool visible);

      void GLInfo(void);

      void bindLight(void);

      void taskWait(Task::Base *pT);
      void taskSync(void);

      virtual int  loadModels (std::filesystem::path &cPath);
      virtual int  loadShaders(std::filesystem::path &cPath);

      virtual void fetchAndQueue(glm::ivec2 idx) = 0;
      virtual void createTasks  (void)           = 0;

    public:
      virtual int   exec    (void) = 0;

      virtual int   init    (Core::SpJob &spJob);
      virtual void  destroy (void);

      Executor(void);
      virtual ~Executor();
  };
};
//---------------------------------------------------------------------

