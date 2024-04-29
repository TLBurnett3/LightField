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
#include "Aperture/Executor.h"
#include "Core/Timer.h"
#include "Aperture/SarNone.h"
#include "Aperture/SarCpp.h"

using namespace Lf;
using namespace Aperture;
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// https://graphics.stanford.edu/~vaibhav/pubs/thesis.pdf
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
  Aperture::Executor *pE = (Aperture::Executor *)glfwGetWindowUserPointer(pW);

    switch (key)
    {    
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
        {
        uint32_t skey = key - '0';
        
          pE->setSarIdx(skey);
        }
        break;

      case GLFW_KEY_PAGE_UP:
        pE->incAperture(0.1);
        break;

      case GLFW_KEY_PAGE_DOWN:
        pE->incAperture(-0.1);
        break;

      case GLFW_KEY_HOME:
      case GLFW_KEY_BACKSPACE:
        break;

      case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(pW,GL_TRUE);
        break;

      default:
        break;
    }
  }
}


//---------------------------------------------------------------------
// exec
//---------------------------------------------------------------------
int Executor::exec(void) 
{
int         rc      = 0;
glm::vec2   vW      = glm::vec2(_wS) * 0.5f;
glm::vec3   vP      = glm::vec3(0,1,0);
glm::vec3   vD      = glm::vec3(0,-1,0);
glm::vec3   vU      = glm::vec3(0,0,1);
glm::mat4   mP      = glm::ortho(-vW.x,vW.x,-vW.y,vW.y,0.0f,2.0f);
glm::mat4   mV      = glm::lookAt(vP,vP + vD,vU);
glm::mat4   mM      = glm::mat4(1);
glm::mat4   mMV     = mV * mM;

  glEnable(GL_TEXTURE_2D);
  glActiveTexture(GL_TEXTURE0);

  glClearColor(0.25f,0.25f,0.25f,0);
  glViewport(0,0,_wS.x,_wS.y);

  _pShader->use();
  _pShader->bindMVP(mP * mMV);

  while (!glfwWindowShouldClose(_pWindow))
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _sarLst[_sarIdx]->setAperture(_aP);
    _sarLst[_sarIdx]->render(_mctex,_vao);

    glfwSwapBuffers(_pWindow);
    glfwPollEvents();
  }

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
// initGLFW
//---------------------------------------------------------------------
int Executor::initGLFW(void)
{
int rc = -1;

  glfwSetErrorCallback(ErrorCallback);

  if (glfwInit())    
  {
    _pWindow = initWindow(_wS,"Lightfield Viewer",0,0,true);

    if (_pWindow)
    {
    std::filesystem::path cPath = std::filesystem::current_path();
        
      glfwSetWindowUserPointer(_pWindow,this);

      glfwSetKeyCallback          (_pWindow,Keyboard_Callback);

#ifdef _WIN32
      glewExperimental = GL_TRUE;
      glewInit();
#endif   

      GLInfo();

      rc = 0;
    }
  }

  return rc;
}


//---------------------------------------------------------------------
// initGraphics
//---------------------------------------------------------------------
int Executor::initGraphics(void)
{
int  rc = 0;

  _pShader = new RenderGL::BasicShader("Basic");
  _pShader->addVertexShader  ("./Shaders/Default3D.vtx");
  _pShader->addFragmentShader("./Shaders/Default3D.frg");
  rc = _pShader->compile();  

  if (rc == 0)
  {
  glm::ivec2          vS = _iS;
  glm::ivec2          nV = _nI;
  cv::Scalar          clr(255,221,244); // pink lace
  int                 mode;
  RenderGL::VtxVNTLst quad;

    _wS.y = _wS.x * ((float)vS.y / (float)vS.x);

    mode = quad.createQuadXZ(glm::vec3(0),glm::vec2(_wS));

    _vao.upload(quad,mode);
    _mctex.upload(_mcImg);

    glfwSetWindowSize(_pWindow,_wS.x,_wS.y);
  }
  
  return rc;
}



//---------------------------------------------------------------------
// initSarNone
//---------------------------------------------------------------------
int Executor::initSarNone(void)
{
int rc  = 0;
SarNone *pS = new SarNone();

  pS->init();
  _sarLst[SAR_NONE] = pS;
  
  return rc;
}


//---------------------------------------------------------------------
// initSarCpp
//---------------------------------------------------------------------
int Executor::initSarCpp(void)
{
int rc  = 0;
SarCpp *pS = new SarCpp();

  pS->init(_mcImg,_nI,_iS);
  _sarLst[SAR_CPP] = pS;
  
  return rc;
}


//---------------------------------------------------------------------
// init
//---------------------------------------------------------------------
int Executor::init(const char *pDir) 
{
int rc  = 0;

  rc = _imgSet.load(std::filesystem::path(pDir));

  if (rc == 0)
    rc = initGLFW();

  if (rc == 0)
  {
  GLint mS = 0;

    glGetIntegerv(GL_MAX_TEXTURE_SIZE,&mS);

    rc = _imgSet.fitSize(glm::ivec2(mS));
  }

  if (rc == 0)
    rc = _imgSet.createPlenopticImage(_mcImg,_nI,_iS);

  if (rc == 0)
    cv::imwrite("SarImage.png",_mcImg);

  if (rc == 0)
    rc = initGraphics();

  _sarLst.resize(SAR_MAX);
  
  if (rc == 0)
    rc = initSarNone();

  if (rc == 0)
    rc = initSarCpp();

  return rc;
}


//---------------------------------------------------------------------
// destroy
//---------------------------------------------------------------------
void Executor::destroy(void) 
{
  while (!_sarLst.empty())
  {
    delete _sarLst.back();
    _sarLst.pop_back();
  }

  if (_pWindow)
    glfwDestroyWindow(_pWindow);

  glfwTerminate();
}


//---------------------------------------------------------------------
// Executor
//---------------------------------------------------------------------
Executor::Executor(void) : _pWindow(0),
                           _wS(2048),
                           _imgSet(),
                           _mcImg(),                         
                           _nI(0),
                           _iS(0),
                           _pShader(0),
                           _vao(),
                           _mctex(),
                           _sarLst(),
                           _sarIdx(SAR_NONE),
                           _aP(0)
{
}


//---------------------------------------------------------------------
// ~Executor
//---------------------------------------------------------------------
Executor::~Executor()
{
  delete _pShader;
}

