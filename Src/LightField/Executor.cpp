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
#include "Tasks/WriteAvi.h"
#include "Tasks/WriteImg.h"

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
    
    cv::flip(spImg->first,spImg->first,0);

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

    cv::flip(spImg->first,spImg->first,0);

    while (ii != iEnd)
    {
      (*ii)->queue(spImg);
      ii++;
    }
  }
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
// renderDoubleFrustumPlane
//---------------------------------------------------------------------
int Executor::renderDoubleFrustumPlane(void) 
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

    taskSync();
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
// renderOblique
//---------------------------------------------------------------------
void Executor::renderOblique(Render::Camera &camera,const glm::vec2 &rA)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  if (1)
  {
  glm::vec2 r  = glm::radians(rA);
  glm::mat4 mT = glm::shearY3D(_job.sceneTransform(),-r[0],r[1]);
 
    _modMan.render(camera,_shader,_job.sceneTransform());
  }    
    
  glFinish();
}


//---------------------------------------------------------------------
// renderObliquePlane
//---------------------------------------------------------------------
int Executor::renderObliquePlane(void) 
{
int         rc      = 0;
glm::ivec2  nH      = _job.numHogels();
glm::ivec2  hS      = _job.hogelSize();
glm::ivec2  idx(0);
uint32_t    n(0);
Core::Timer tH;

  glfwMakeContextCurrent(_pWindow);
  glfwSetWindowSize     (_pWindow,nH.x,nH.y);
  glfwSetWindowTitle    (_pWindow,"Lightfield - Obliques");

  tH.start();

  std::cout << "Starting Oblique Rendering " << std::endl;

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
// renderObliqueAndSlice
//---------------------------------------------------------------------
void Executor::renderObliqueAndSlice(void)
{ 
double            FPS       = 0;
glm::ivec2        nH        = _job.numHogels();
glm::ivec2        hS        = _job.hogelSize();
glm::mat4         mVVT      = _job.viewVolumeTransform();
glm::vec3         vC        = glm::vec3(mVVT[3]);
glm::vec3         vT        = glm::vec3(mVVT[1]);
glm::vec3         vP        = vC;
glm::vec3         vD        = vC - vT;
glm::vec3         vU        = vC - glm::vec3(mVVT[2]);
glm::vec2         hD        = glm::vec2(mVVT[0].x,mVVT[2].z) * 0.5f;
float             zF        = _job.zFar();
/*
size_t            nR        = imageExecutor.numSliceRows(); 
glm::ivec2        idx(0);
Render::Camera    camera;
Core::Timer	      tR;

  if (nR == 0)
    nR = nH.y;

  glfwMakeContextCurrent(pWindow);
  glfwSetWindowSize(pWindow,nH.x,nH.y);
  glfwSetWindowTitle(pWindow,"Oblique Render View");

  glViewport(0,0,job.numHogels().x,job.numHogels().y);

  glClearColor(0,0,0,0);
  glPixelStorei(GL_PACK_ALIGNMENT,1);

  imageExecutor.setZNear(-zF);
  imageExecutor.setZFar(zF);

  camera.setOrthographic(-hD.x,hD.x,-hD.y,hD.y,-zF,zF);

  for (size_t i = 0;(i < (size_t)nH.y) && !glfwWindowShouldClose(pWindow);i += nR)
  {
  glm::vec2 rT  = glm::vec2(job.fov()) / 2.0f;
  glm::vec2 rS  = glm::vec2(job.fov()) / glm::vec2(hS);
  glm::vec2 rA  = -rT;

    if ((i + nR) >= (size_t)nH.y)
      nR = (size_t)nH.y - i;

    std::cout << "Slicing Rows: " << i << " to " << i + nR << std::endl;

    imageExecutor.setSliceRange(i,nR);

    for (idx.y = 0;(idx.y < hS.y) && !glfwWindowShouldClose(pWindow);idx.y++)
    {
    Common::Timer  tS;

      rA.x  = -rT.x;

      for (idx.x = 0;(idx.x < hS.x) && !glfwWindowShouldClose(pWindow);idx.x++)
      {
        camera.lookAt(vP,vD,vU);

        renderObliqueView(camera,rA);

        fetchAndQueue(idx);

        glfwSwapBuffers(pWindow);
        glfwPollEvents();

        rA.x  += rS.x; 
      }

      {
      double  fps     = 0;
      char    buf[128];

        if (tS.seconds() > 0)
          fps = (double)hS.x / tS.seconds();

        FPS += fps;

        sprintf(buf,"Line: %-6d   FPS: %6.3f",idx.y,fps);
        std::cout << buf << std::endl;
      }

      rA.y  += rS.y;

      if (idx.y == (hS.y - 1))
        imageExecutor.writeSliceAVIs();

      imageExecutor.hostSync();
    }
  }

  if (FPS > 0)
    FPS /= (double)hS.y;

  double s = tR.seconds();
  std::cout << "Total runtime is " << s << " seconds (" << s / 3600 << " hours)." << std::endl;
  std::cout << "Final FPS: " << FPS << std::endl;

  {
  FILE *fp = fopen("Performance.txt","a");

    fprintf(fp,"(%d,%d) x (%d,%d) FPS: %f; Runtime %f seconds (%f hours)\n",job.hogelSize().x,job.hogelSize().y,
                                           job.numHogels().x,job.numHogels().y,
                                           FPS,s,s/3600.0f);
    fclose(fp);
  }*/
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
  Task::ProofImage  *pT = new Task::ProofImage("RGBProof");

    pT->create(_job.numHogels(),_job.hogelSize(),3);
    pT->setPathFile(_job.outputPath(),"RGBProof");
    pT->start();

    _imgTaskLst.push_back(pT);
  }

  if (_job.isTask(Core::Job::WriteAvi))
  {
  Task::WriteAvi        *pT = new Task::WriteAvi("RGBAvi");
  std::filesystem::path dPath(_job.outputPath());

    dPath /= "HogelAvi";

    pT->setPathFile(dPath,"HogelRow_");
    pT->start();

    _imgTaskLst.push_back(pT);
  }

  if (_job.isTask(Core::Job::WriteImg))
  {
  Task::WriteImg        *pT = new Task::WriteImg("RGBImg");
  std::filesystem::path dPath(_job.outputPath());

    dPath /= "HogelImg";

    pT->setPathFile(dPath,"HogelImg_%06dx%06d","png");
    pT->start();

    _imgTaskLst.push_back(pT);
  }

  if (_job.isTask(Core::Job::ProofDepth))
  {
  Task::ProofImage  *pT = new Task::ProofImage("DthProof");

    pT->setZNear(_job.zNear());
    pT->setZFar(_job.zFar());
    pT->create(_job.numHogels(),_job.hogelSize(),1);
    pT->setPathFile(_job.outputPath(),"DthProof");
    pT->start();

    _dthTaskLst.push_back(pT);
  }

  if (_job.isTask(Core::Job::WriteDepthImg))
  {
  Task::WriteImg        *pT = new Task::WriteImg("DthImg");
  std::filesystem::path dPath(_job.outputPath());

    dPath /= "HogelDth";

    pT->setZNear(_job.zNear());
    pT->setZFar(_job.zFar());
    pT->setPathFile(dPath,"HogelDthImg_%06dx%06d","png");
    pT->start();

    _dthTaskLst.push_back(pT);
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
    rc = renderDoubleFrustumPlane();
  else if (_job.renderType() == Core::Job::RenderTypes::Oblique)
    rc = renderObliquePlane();

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

