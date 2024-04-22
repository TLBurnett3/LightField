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

// Executor.cpp 
// Thomas Burnett


//---------------------------------------------------------------------
// Includes
// System
#include <string>
#include <iostream>

// 3rdPartyLibs
#include <glm/glm.hpp>
#include <glm/ext.hpp>

// LightField
#include "RenderGL/Def.h"
#include "LightField/Executor.h"
#include "Core/Timer.h"
#include "RenderGL/Camera.h"
#include "Tasks/ProofImage.h"
#include "Tasks/WriteAvi.h"
#include "Tasks/WriteImg.h"
#include "Tasks/SliceNDice.h"

using namespace Lf;
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Logging_Callback
//---------------------------------------------------------------------
static void Logging_Callback(const char *p)
{
  std::cout << p << std::endl;
}
static void ErrorCallback(int error,const char * p)
{
  std::cout << error << ": " << p << std::endl;
}


//---------------------------------------------------------------------
// Keyboard_Callback
//---------------------------------------------------------------------
static void Keyboard_Callback(GLFWwindow *pW,int key,int scancode,int action,int mods)
{
  if (action == GLFW_RELEASE)
  {
    switch (key)
    {      
      case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(pW,GL_TRUE);
        break;

      default:
        break;
    }
  }
}


//---------------------------------------------------------------------
// findTask
//---------------------------------------------------------------------
Task::Base    *Executor::findTask(const char *tName,TaskList &tLst)
{
std::string         n     = tName;
TaskList::iterator  ii    = tLst.begin();
TaskList::iterator  iEnd  = tLst.end();

  while (ii != iEnd)
  {
    if (n == (*ii)->name())
      return (*ii);

    ii++;
  }

  return 0;       
}


//---------------------------------------------------------------------
// initWindow 
//---------------------------------------------------------------------
GLFWwindow *Executor::initWindow(const glm::ivec2 wD,const char *pStr,GLFWwindow *pShared,int fps,bool visible)
{
GLFWwindow *pW = 0;

  glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_COMPAT_PROFILE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,1);	
  glfwWindowHint(GLFW_DEPTH_BITS,32);

  if (visible)
	  glfwWindowHint(GLFW_VISIBLE,GL_TRUE);
  else 
	  glfwWindowHint(GLFW_VISIBLE,GL_FALSE);
	
  pW = glfwCreateWindow(wD.x,wD.y,pStr,0,pShared);

  glfwMakeContextCurrent(pW);

  glfwSwapInterval(fps);

  glfwShowWindow(pW);

  return pW;	
}


//---------------------------------------------------------------------
// GLInfo
//---------------------------------------------------------------------
void Executor::GLInfo(void)
{
std::string str;
char        *pS = 0;

  std::cout << std::endl;

  str = "GL Vender: ";
  pS = (char *)glGetString(GL_VENDOR);
  if (pS)
    str += pS;
  else
    str += "(NULL)";
  
  std::cout <<  str.c_str() << std::endl;
  
  str = "GL Version: ";
  pS =  (char *)glGetString(GL_VERSION);
  if (pS)
    str += pS;
  else
    str += "(NULL)";

  std::cout <<  str.c_str() << std::endl;

  str = "GL Renderer: ";
  pS =  (char *)glGetString(GL_RENDERER);
  if (pS)
    str += pS;
  else
    str += "(NULL)";

  std::cout <<  str.c_str() << std::endl;
  
  str = "GL GLSL: ";
  pS = (char *)glGetString(GL_SHADING_LANGUAGE_VERSION);
  if (pS)
    str += pS;
  else
    str += "(NULL)";

  std::cout <<  str.c_str() << std::endl;

  {
  int   b = 0;
  char  buf[16];

    str = "Depth Buffer Bits: ";
    glGetIntegerv(GL_DEPTH_BITS, &b);
    sprintf_s(buf,"%d",b);
    str += buf;

    std::cout <<  str.c_str() << std::endl;
  }


#ifdef _glfw3_h_
  str = "GLFW Version: ";
  str += glfwGetVersionString();

  std::cout <<  str.c_str() << std::endl;
#endif

  std::cout << std::endl;
}


//---------------------------------------------------------------------
// taskWait
//---------------------------------------------------------------------
void Executor::taskWait(Task::Base *pT) 
{
  if (!pT->finished())
  {
  uint32_t i = 0;

    std::cout << "Waiting on Task: " << pT->name();

    do 
    {        
      i++;

      if (i >= 10)
      {
        std::cout << ".";
        i = 0;
      }

      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    while (!pT->finished());

    std::cout << std::endl;
  }
}


//---------------------------------------------------------------------
// taskSync
//---------------------------------------------------------------------
void Executor::taskSync(void) 
{
  {
  TaskList::iterator        ii    = _imgTaskLst.begin();
  TaskList::iterator        iEnd  = _imgTaskLst.end();
    
    while (ii != iEnd)
    {
      taskWait(*ii);

      ii++;
    }
  }

  {
  TaskList::iterator        ii    = _dthTaskLst.begin();
  TaskList::iterator        iEnd  = _dthTaskLst.end();

    while (ii != iEnd)
    {
      taskWait(*ii);

      ii++;
    }
  }
}


//---------------------------------------------------------------------
// loadModels
//---------------------------------------------------------------------
int Executor::loadModels(std::filesystem::path &cPath)
{
int rc = -1;

  _pScene = new RenderGL::Scene();

  if (_pScene)
  {
    rc =_pScene->init(cPath);

    for (size_t i = 0;i < _spJob->numModels();i++)
    {
      if (_pScene->load(_spJob->modelPath(i),_spJob->modelTransform(i)) == 0)
        std::cout << "Succesful Load: " << _spJob->modelPath(i) << std::endl;
      else
      {
        std::cout << "Unsuccesful Load: " << _spJob->modelPath(i) << std::endl;
        rc |= -1;
      }
    }   
  }

  return rc;
}


//---------------------------------------------------------------------
// loadShaders
//---------------------------------------------------------------------
int Executor::loadShaders(std::filesystem::path &cPath)
{
std::filesystem::path  vShader(cPath);
std::filesystem::path  fShader(cPath);
int                    rc = 0;

  vShader /= "Shaders/Phong.vtx";
  fShader /= "Shaders/Phong.frg";

  _pShader = new RenderGL::Shader();
 
  rc |= _pShader->addVertexShader(vShader);
  rc |= _pShader->addFragmentShader(fShader);

  if (rc == 0)
    rc |= _pShader->compile();

  return rc;
}


//---------------------------------------------------------------------
// init
//---------------------------------------------------------------------
int Executor::init(Core::SpJob &spJob) 
{
int   rc = -1;

  _spJob = spJob;

  glfwSetErrorCallback(ErrorCallback);

  if (glfwInit())    
  {
  glm::ivec2 wS = _spJob->hogelSize();

    _pWindow = initWindow(wS,"Lightfield",0,0,true);

    if (_pWindow)
    {
    std::filesystem::path cPath = std::filesystem::current_path();

      glfwSetKeyCallback          (_pWindow,Keyboard_Callback);

#ifdef _WIN32
      glewExperimental = GL_TRUE;
      glewInit();
#endif   

      GLInfo();

      {
      std::filesystem::path outPath = _spJob->outputPath();

        if (!outPath.empty() && !std::filesystem::exists(outPath))
          std::filesystem::create_directory(outPath);
      }

      rc = loadModels(cPath);

      if (rc == 0)
      rc = loadShaders(cPath);

      if (rc == 0)
        createTasks();
    }
    else
      std::cout << "Failed to create GLFW window" << std::endl;
  }

  return rc;
}


//---------------------------------------------------------------------
// bindLight
//---------------------------------------------------------------------
void  Executor::bindLight(void) 
{
  assert(_pShader);

  _pShader->bindLightPosition(_spJob->lightPosition());
  _pShader->bindLightAmbient (_spJob->lightAmbient());
  _pShader->bindLightDiffuse (_spJob->lightDiffuse());
  _pShader->bindLightSpecular(_spJob->lightSpecular());
}


//---------------------------------------------------------------------
// destroy
//---------------------------------------------------------------------
void Executor::destroy(void) 
{
  {
  TaskList::iterator        ii    = _imgTaskLst.begin();
  TaskList::iterator        iEnd  = _imgTaskLst.end();
    
    while (ii != iEnd)
    {
      (*ii)->stop();
      (*ii)->join();
      ii++;
    }
  }

  {
  TaskList::iterator        ii    = _dthTaskLst.begin();
  TaskList::iterator        iEnd  = _dthTaskLst.end();

    while (ii != iEnd)
    {
      (*ii)->stop();
      (*ii)->join();
      ii++;
    }
  }

  if (_pScene)
    delete _pScene;

  if (_pShader)
    delete _pShader;

  if (_pWindow)
    glfwDestroyWindow(_pWindow);

  glfwTerminate();

  while (!_imgTaskLst.empty())
  {
    delete _imgTaskLst.back();
    _imgTaskLst.pop_back();
  }

  while (!_dthTaskLst.empty())
  {
    delete _dthTaskLst.back();
    _dthTaskLst.pop_back();
  }
}


//---------------------------------------------------------------------
// Executor
//---------------------------------------------------------------------
Executor::Executor(void) : _spJob(),
                           _pWindow(0),
                           _pScene(0),
                           _pShader(0),
                           _imgTaskLst(),
                           _dthTaskLst()
{
}


//---------------------------------------------------------------------
// ~Executor
//---------------------------------------------------------------------
Executor::~Executor()
{

}

