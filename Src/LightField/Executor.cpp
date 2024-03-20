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
#include "Render/Def.h"
#include "LightField/Executor.h"
#include "Core/Timer.h"
#include "Render/Camera.h"
#include "Tasks/ProofImage.h"

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
// parseJob
//---------------------------------------------------------------------
int Executor::parseJob(const char *pCfg) 
{
std::string cfgFile(pCfg);
int rc  = 0;

  std::cout << "Parsing job file: " << cfgFile << std::endl;

  rc = _job.parse(cfgFile);

  _job.print(std::cout);

  std::cout << "Job file parsed: " << ((rc == 0) ? "Successful" : "Failed") << std::endl;

  return rc;
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
// fetchHogelAndQueue
//---------------------------------------------------------------------
void Executor::fetchHogelAndQueue(glm::ivec2 idx)
{
glm::ivec2  hS      = _job.hogelSize();

  if (_imgTaskLst.size())
  {
  TaskList::iterator        ii    = _imgTaskLst.begin();
  TaskList::iterator        iEnd  = _imgTaskLst.end();
  Task::Base::SpImg         spImg = std::make_shared<std::pair<cv::Mat,glm::ivec2>>();

    spImg->first.create(hS.y,hS.x,CV_8UC3);
    spImg->second = idx;

    glReadBuffer(GL_BACK);
    glReadPixels(0,0,(GLsizei)hS.x,(GLsizei)hS.y,GL_BGR,GL_UNSIGNED_BYTE,spImg->first.data); 
    
    while (ii != iEnd)
    {
      (*ii)->queue(spImg);
      ii++;
    }
  }

  if (_dthTaskLst.size())
  {
  TaskList::iterator        ii    = _dthTaskLst.begin();
  TaskList::iterator        iEnd  = _dthTaskLst.end();
  Task::Base::SpImg         spImg = std::make_shared<std::pair<cv::Mat,glm::ivec2>>();

    spImg->first.create(hS.y,hS.x,CV_32FC1);
    spImg->second = idx;

    glReadBuffer(GL_BACK);
    glReadPixels(0,0,(GLsizei)hS.x,(GLsizei)hS.y,GL_DEPTH_COMPONENT,GL_FLOAT,spImg->first.data);

    while (ii != iEnd)
    {
      (*ii)->queue(spImg);
      ii++;
    }
  }
}



//---------------------------------------------------------------------
// renderHogel
//---------------------------------------------------------------------
void Executor::renderHogel(Render::Camera &camera,const glm::vec3 &vI)
{
glm::mat4   mT = _job.viewVolumeTransform();
glm::vec3   vP = mT * glm::vec4(vI,1);
glm::vec3   vU = glm::normalize(mT[2]);  
glm::vec3   vD = glm::normalize(mT[1]); // we render along the y axis of the VVT

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  _shader.use();
  _shader.setTextureSampler(0);

  // back frustum, away from viewer into the display
  if (1)
  {
  glm::vec3 vE(vP + (vD * camera.zNear()));

    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glDepthRange(0.5f,1.0f);

    camera.backFrustum(vE,-vD,vU);

    _modMan.render(camera,_shader,_job.sceneTransform());

    glFlush();
  }

  // front frustum, toward the viewer out of the display
  if (1)
  {
  glm::vec3 vE(vP + (vD * -camera.zNear()));

    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);
    glDepthRange(0.5f,0.0f);

    camera.frontFrustum(vE,vD,-vU);

    _modMan.render(camera,_shader,_job.sceneTransform());
  }   

  glFinish();
}



//---------------------------------------------------------------------
// renderDoubleFrustum
//---------------------------------------------------------------------
int Executor::renderDoubleFrustum(void) 
{
int             rc      = 0;
glm::ivec2      nH      = _job.numHogels();
glm::ivec2      hS      = _job.hogelSize();
float           s       = glm::max(nH.x,nH.y);
glm::ivec2      idx(0);
uint32_t        n(0);
Core::Timer     tH;
Render::Camera  camera;

  glfwMakeContextCurrent(_pWindow);
  glfwSetWindowSize     (_pWindow,hS.x,hS.y);
  glfwSetWindowTitle    (_pWindow,"Lightfield - Double Frustum");

  tH.start();

  std::cout << "Starting Double Frustum Hogel Rendering " << std::endl;

  camera.setPerspective(_job.fov(),(float)hS.x/(float)(hS.y),_job.zNear(),_job.zFar());

  glViewport(0,0,hS.x,hS.y);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glClearColor(0,0,0,0);
  glPixelStorei(GL_PACK_ALIGNMENT,1);

  for (;(idx.y < nH.y) && !glfwWindowShouldClose(_pWindow);idx.y++)
  {
  Core::Timer tR;

    tR.start();

    std::cout << "Rendering Hogel Row: " << idx.y << std::endl;

    for (idx.x = 0;(idx.x < nH.x) && !glfwWindowShouldClose(_pWindow);idx.x++)
    {
    glm::vec3 vI = glm::vec3(idx.x,0,idx.y);

      vI /= s;
      vI -= glm::vec3(0.5f,0.0f,0.5f);
      vI *= glm::vec3(1.0f,0.0f,-1.0f);

      renderHogel(camera,vI);
      fetchHogelAndQueue(idx);

      glfwSwapBuffers(_pWindow);
      glfwPollEvents();

      n++;
    }

    {
    double t = tR.seconds();
    double c = (double)idx.y / (double)nH.y * 100.0;

      std::cout << "    Row Time: " << t << " seconds";
      std::cout << "    FPS: " << (double)idx.x / t;
      std::cout << "    Complete: " << c << '%' << std::endl;
    }
  }

  {
  double t = tH.seconds();

    std::cout << "Completed Double Frustum Hogel Rendering " << std::endl;
    std::cout << "Render Time: " << t << " seconds" << std::endl;
    std::cout << "FPS: " << (double)n / t << std::endl;
  }

  return rc;
}


//---------------------------------------------------------------------
// renderObliqueSliceDice
//---------------------------------------------------------------------
int Executor::renderObliqueSliceDice(void) 
{
int         rc      = 0;
glm::ivec2  nH      = _job.numHogels();
glm::ivec2  hS      = _job.hogelSize();
glm::ivec2  idx(0);
uint32_t    n(0);
Core::Timer tH;

  glfwMakeContextCurrent(_pWindow);
  glfwSetWindowSize     (_pWindow,nH.x,nH.y);
  glfwSetWindowTitle    (_pWindow,"Lightfield - Oblique Slice Dice");

  tH.start();

  std::cout << "Starting Oblique Slice & Dice Rendering " << std::endl;

  glViewport(0,0,nH.x,nH.y);

  for (;(idx.y < hS.y) && !glfwWindowShouldClose(_pWindow);idx.y++)
  {
  Core::Timer tR;

    tR.start();

    std::cout << "Rendering Oblique Row: " << idx.y << std::endl;

    for (idx.x = 0;(idx.x < hS.x) && !glfwWindowShouldClose(_pWindow);idx.x++)
    {
      glfwSwapBuffers(_pWindow);
      glfwPollEvents();

      n++;
    }

    {
    double t = tR.seconds();
    double c = (double)idx.y / (double)nH.y * 100.0;

      std::cout << "    Row Time: " << t << " seconds";
      std::cout << "    FPS: " << (double)idx.x / t;
      std::cout << "    Complete: " << c << '%' << std::endl;
    }
  }

  {
  double t = tH.seconds();

    std::cout << "Completed Oblique Slice & Dice Rendering " << std::endl;
    std::cout << "Render Time: " << t << " seconds" << std::endl;
    std::cout << "FPS: " << (double)n / t << std::endl;
  }

  return rc;
}


//---------------------------------------------------------------------
// loadModels
//---------------------------------------------------------------------
int Executor::loadModels(std::filesystem::path &cPath)
{
int rc = _modMan.init(cPath);

  for (size_t i = 0;i < _job.numModels();i++)
  {
    if (_modMan.load(_job.modelPath(i),_job.modelTransform(i)) == 0)
      std::cout << "Succesful Load: " << _job.modelPath(i) << std::endl;
    else
    {
      std::cout << "Unsuccesful Load: " << _job.modelPath(i) << std::endl;
      rc |= -1;
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

  vShader /= "Shaders/Default3D.vtx";
  fShader /= "Shaders/Default3D.frg";
 
  rc |= _shader.addVertexShader(vShader);
  rc |= _shader.addFragmentShader(fShader);

  if (rc == 0)
    rc |= _shader.compile();

  return rc;
}


//---------------------------------------------------------------------
// createTasks
//---------------------------------------------------------------------
int Executor::createTasks(void)
{
int rc = 0;

  if (_job.isTask(Core::Job::ProofImage))
  {
  Task::ProofImage  *pT = new Task::ProofImage("ImageProof");

    pT->create(_job.numHogels(),_job.hogelSize(),3);
    pT->setPath(_job.outputPath());
    pT->start();

    _imgTaskLst.push_back(pT);
  }

  return rc;
}


//---------------------------------------------------------------------
// init
//---------------------------------------------------------------------
int Executor::init(const char *pCfg) 
{
int rc  = parseJob(pCfg);

  if (rc == 0)
  {
    glfwSetErrorCallback(ErrorCallback);

    if (glfwInit())    
    {
    glm::ivec2 wS = _job.hogelSize();

      _pWindow = initWindow(wS,"Lightfield",0,0,true);

      if (_pWindow)
      {
      std::filesystem::path cPath = std::filesystem::current_path();

        glfwSetKeyCallback      (_pWindow,Keyboard_Callback);

#ifdef _WIN32
        glewExperimental = GL_TRUE;
        glewInit();
#endif   

        GLInfo();

        rc |= loadModels(cPath);
        rc |= loadShaders(cPath);
        rc |= createTasks();
      }
    }
  }

  return rc;
}


//---------------------------------------------------------------------
// exec
//---------------------------------------------------------------------
int Executor::exec(void) 
{
int rc      = 0;

  if (_job.renderType() == Core::Job::RenderTypes::DoubleFrustum)
    rc = renderDoubleFrustum();
  else if (_job.renderType() == Core::Job::RenderTypes::ObliqueSliceDice)
    rc = renderObliqueSliceDice();

  return rc;
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
      ii++;
    }
  }

  {
  TaskList::iterator        ii    = _dthTaskLst.begin();
  TaskList::iterator        iEnd  = _dthTaskLst.end();

    while (ii != iEnd)
    {
      (*ii)->stop();
      ii++;
    }
  }

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
Executor::Executor(void) : _job(),
                           _pWindow(0),
                           _modMan(),
                           _shader(),
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

