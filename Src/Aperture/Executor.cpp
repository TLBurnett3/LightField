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
#include "Aperture/SarCV.h"
#include "Aperture/SarGL.h"

using namespace Lf;
using namespace Aperture;
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// https://graphics.stanford.edu/~vaibhav/pubs/thesis.pdf
// http://lightfield.stanford.edu/
// https://graphics.stanford.edu/papers/light/
// http://lightfield.stanford.edu/acq.html#lego
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Defines
#define DZ    1.000f
#define AINC  0.1f
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
// CursorPosition_Callback
//---------------------------------------------------------------------
static void CursorPosition_Callback(GLFWwindow *pW,double xPos,double yPos)
{
Aperture::Executor *pE = (Aperture::Executor *)glfwGetWindowUserPointer(pW);

  pE->mouseMotion(glm::fvec2(xPos,yPos));
}

//---------------------------------------------------------------------
// MouseButton_Callback
//---------------------------------------------------------------------
static void MouseButton_Callback(GLFWwindow *pW,int button,int action,int mods)
{
  if (button == 0)
  {
  Aperture::Executor *pE = (Aperture::Executor *)glfwGetWindowUserPointer(pW);
  glm::dvec2         vMp;

    glfwGetCursorPos(pW,&vMp.x,&vMp.y);   
    pE->mouseButton(glm::fvec2(vMp),action);
  }
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
        pE->incAperture(AINC);
        break;

      case GLFW_KEY_PAGE_DOWN:
        pE->incAperture(-AINC);
        break;

      case GLFW_KEY_RIGHT:
        pE->incSubImgIdx(glm::ivec2(-1,0));
        break;

      case GLFW_KEY_LEFT:
        pE->incSubImgIdx(glm::ivec2(1,0));
        break;

      case GLFW_KEY_UP:
        pE->incSubImgIdx(glm::ivec2(0,1));
        break;

      case GLFW_KEY_DOWN:
        pE->incSubImgIdx(glm::ivec2(0,-1));
        break;      

     case GLFW_KEY_INSERT:
        pE->incFocus(DZ);
        break;

      case GLFW_KEY_DELETE:
        pE->incFocus(-DZ);
        break;

      case GLFW_KEY_HOME:
        pE->reset();
        break;

      case GLFW_KEY_END:
        pE->writeImage();
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
// mouseMotion
//---------------------------------------------------------------------
void Executor::mouseMotion(const glm::fvec2 &vMp)
{
  if ((_sarIdx > SAR_NONE) && _bMouseMotion)
  {
  float       s     = 0.20f;
  glm::vec2   wS    = glm::vec2(_wS);
  glm::vec2   wD    = wS * s;
  glm::vec2   wT    = glm::vec2(wS.x - wD.x,wD.y);

    if ((vMp.x > wT.x) && (vMp.y < wD.y))
    {
    glm::vec2 vM = glm::vec2(vMp.x- wT.x,vMp.y);

      _vMe  = glm::vec2(1) - (vM / wD);

      _aP   = glm::distance(_vMe,_vMs) * 2.0f;
      _aP   = glm::clamp(_aP,0.0f,1.0f);
    }
  }
}

//---------------------------------------------------------------------
// mouseButton
//---------------------------------------------------------------------
void Executor::mouseButton(const glm::fvec2 &vMp,const int action)
{
  if (_sarIdx > SAR_NONE)
  {
  float       s     = 0.20f;
  glm::vec2   wS    = glm::vec2(_wS);
  glm::vec2   wD    = wS * s;
  glm::vec2   wT    = glm::vec2(wS.x - wD.x,wD.y);

    if ((vMp.x > wT.x) && (vMp.y < wD.y))
    {
    glm::vec2 vM = glm::vec2(vMp.x- wT.x,vMp.y);

      if (action == GLFW_PRESS)
      {
        _vMs = glm::vec2(1) - (vM / wD);
        _vMe = _vMs;

        _iIdx = _vMs * glm::fvec2(_nI);

        _bMouseMotion = true;
      }
    }

    if (action == GLFW_RELEASE)
    {
      if (_bMouseMotion)
      {
      glm::vec2 vM = glm::vec2(vMp.x- wT.x,vMp.y);

        _vMe  = glm::vec2(1) - (vM / wD);

        _aP   = glm::distance(_vMe,_vMs) * 2.0f;
        _aP   = glm::clamp(_aP,0.0f,1.0f);
      }

      _bMouseMotion = false;
    }
  }
  else
    _bMouseMotion = false;
}


//---------------------------------------------------------------------
// updateWindowTitle
//---------------------------------------------------------------------
void Executor::updateWindowTitle(void) 
{
char buf[512];

  sprintf(buf,"%s - (%d,%d) - (%d,%d) - Aperture: %.2f - Focus: %.2f - Idx: (%d,%d) - fps: %.2f",
              _sarLst[_sarIdx]->name().c_str(),
              _nI.y,_nI.x,
              _iS.y,_iS.x,
              _aP,
              _focus,
              _iIdx.x,_iIdx.y,
              _fps);

  glfwSetWindowTitle(_pWindow,buf);
}



//---------------------------------------------------------------------
// updateHomographies
//---------------------------------------------------------------------
void Executor::updateHomographies(void)
{
  for (size_t i = 0;i < _mHLst.size();i++)
  {
  glm::vec2 uv = _imgSet.get(i)->_uv;
  glm::vec3 vT = glm::vec3(uv.x * _focus * 2.0f,uv.y * _focus * 2.0f,1.0f);

    _mHLst[i] = glm::translate(glm::mat4(1),vT);
  }

  _bHLst = false;
  _sarLst[_sarIdx]->bindHomographies(&_mHLst);
  resetFps();
}


//---------------------------------------------------------------------
// renderMap
//---------------------------------------------------------------------
void Executor::renderMap(glm::mat4 &mP,glm::mat4 &mV,RenderGL::Texture &mcTex,RenderGL::VtxArrayObj &vao) 
{
float       s     = 0.20f;
glm::vec2   wS    = glm::vec2(_wS);
glm::vec2   wD    = wS * s;
glm::vec2   wT    = wS - wD;
glm::mat4   mM(1);

  wT *= 0.5f;

  mM = glm::translate(mM,glm::vec3(-wT.x,0.0f,wT.y));
  mM = glm::scale(mM,glm::vec3(s));

  _pMapShader->use();
  _pMapShader->bindTextureSampler(0);
  _pMapShader->bindMVP(mP * mV * mM);
  _pMapShader->bindImageIndex(_iIdx);
  _pMapShader->bindNumImages(_nI);
  _pMapShader->bindAperture(_aP);

  mcTex.bind();
  vao.render();
}


//---------------------------------------------------------------------
// renderSar
//---------------------------------------------------------------------
void Executor::renderSar(glm::mat4 &mP,glm::mat4 &mV,RenderGL::Texture &mcTex,RenderGL::VtxArrayObj &vao) 
{
  _sarLst[_sarIdx]->bindSubImageIdx(_iIdx);
  _sarLst[_sarIdx]->bindAperture(_aP);
  _sarLst[_sarIdx]->render(mP,mV,_pShader,_mcTex,_vao);
}


//---------------------------------------------------------------------
// writeImage
//---------------------------------------------------------------------
void Executor::writeImage(void) 
{
cv::Mat         img(_wS.y,_wS.x,CV_8UC3);
static uint32_t n(0);
std::string     fName = _sarLst[_sarIdx]->name();

  fName += "_";
  fName += std::to_string(n);
  fName += ".png";

  glReadBuffer(GL_BACK);
  glReadPixels(0,0,(GLsizei)_wS.x,(GLsizei)_wS.y,GL_BGR,GL_UNSIGNED_BYTE,img.data); 
    
  cv::flip(img,img,0);

  cv::imwrite(fName.c_str(),img);

  std::cout << "Saved: " << fName << std::endl;

  n++;
}


//---------------------------------------------------------------------
// exec
//---------------------------------------------------------------------
int Executor::exec(void) 
{
int         rc      = 0;
glm::vec4   clr     = glm::vec4(255,221,244,0) / 255;  // Pink Lace

  glEnable(GL_TEXTURE_2D);
  glActiveTexture(GL_TEXTURE0);

  glClearColor(clr.r,clr.g,clr.b,clr.a);
  setSarIdx(SAR_NONE);

  while (!glfwWindowShouldClose(_pWindow))
  {
  glm::vec2   vW      = glm::vec2(_wS) * 0.5f;
  glm::vec3   vP      = glm::vec3(0,1,0);
  glm::vec3   vD      = glm::vec3(0,-1,0);
  glm::vec3   vU      = glm::vec3(0,0,1);
  glm::mat4   mP      = glm::ortho(-vW.x,vW.x,-vW.y,vW.y,0.0f,2.0f);
  glm::mat4   mV      = glm::lookAt(vP,vP + vD,vU);

    glViewport(0,0,_wS.x,_wS.y);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (_bHLst)
      updateHomographies();

    renderSar(mP,mV,_mcTex,_vao);

    if (_sarIdx > 0)
      renderMap(mP,mV,_mcTex,_vao);
 
    calcFps();

    updateWindowTitle();

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
    sprintf(buf,"%d",b);
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
      glfwSetMouseButtonCallback  (_pWindow,MouseButton_Callback);
      glfwSetCursorPosCallback    (_pWindow,CursorPosition_Callback); 

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

  rc |= _pShader->addVertexShader  ("./Shaders/Default3D.vtx");
  rc |= _pShader->addFragmentShader("./Shaders/Default3D.frg");

  if (rc == 0)
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
    _mcTex.upload(_mcImg);

    glfwSetWindowSize(_pWindow,_wS.x,_wS.y);

    _iIdx = _nI >> 1;
  }
  
  return rc;
}


//---------------------------------------------------------------------
// initHomographies
//---------------------------------------------------------------------
int Executor::initHomographies(void)
{
int rc = 0;

  _mHLst.resize(_nI.x * _nI.y);

  for (size_t i = 0;i < _mHLst.size();i++)
  {
    _mHLst[i] = glm::mat4(1);
  }

  return rc;
}


//---------------------------------------------------------------------
// initSarNone
//---------------------------------------------------------------------
int Executor::initSarNone(void)
{
int     rc  = 0;
SarNone *pS = new SarNone();

  pS->init();
  _sarLst[SAR_NONE] = pS;

  std::cout << "Created: " << pS->name() << std::endl;
  
  return rc;
}


//---------------------------------------------------------------------
// initSarCpp
//---------------------------------------------------------------------
int Executor::initSarCpp(void)
{
int    rc  = 0;
SarCpp *pS = new SarCpp();

  pS->init(_mcImg,_nI,_iS);
  _sarLst[SAR_CPP] = pS;

  std::cout << "Created: " << pS->name() << std::endl;
  
  return rc;
}


//---------------------------------------------------------------------
// initSarCV
//---------------------------------------------------------------------
int Executor::initSarCV(void)
{
int   rc  = 0;
SarCV *pS = new SarCV();

  pS->init(_imgSet,_nI,_iS);
  _sarLst[SAR_CV] = pS;

  std::cout << "Created: " << pS->name() << std::endl;
  
  return rc;
}


//---------------------------------------------------------------------
// initSarGL
//---------------------------------------------------------------------
int Executor::initSarGL(void)
{
int   rc  = 0;
SarGL *pS = new SarGL();

  pS->init(_nI,_iS);
  _sarLst[SAR_GL] = pS;

  std::cout << "Created: " << pS->name() << std::endl;
  
  return rc;
}


//---------------------------------------------------------------------
// initMapShader
//---------------------------------------------------------------------
int Executor::initMapShader(void)
{
int rc  = 0;

  _pMapShader = new MapShader("MapShader");

  rc |= _pMapShader->addVertexShader  ("./Shaders/Default3D.vtx");
  rc |= _pMapShader->addFragmentShader("./Shaders/MapAperture.frg");

  if (rc == 0)
    rc = _pMapShader->compile();  

  return rc;
}



//---------------------------------------------------------------------
// instructions
//---------------------------------------------------------------------
void Executor::instructions(void) 
{
  std::cout << std::endl;
  std::cout << "Aperture Instructions" << std::endl;
  std::cout << "---------------------" << std::endl;

  std::cout << "Input .png files need to of the form: name_y_x_v_u.png"                                  << std::endl;
  std::cout << "The .png files should be rectified and cropped"                                            << std::endl;
  std::cout << "See the New Stanford Light Field Archive (https://graphics.stanford.edu/data/LF/lfs.html)" << std::endl;
  std::cout << "   for details and example datasets"                                                       << std::endl;
  std::cout << "Key" << std::endl;

  std::cout << "Insert      - Move focal plane back"                << std::endl;
  std::cout << "Delete      - Move focal plane forward"             << std::endl;
  std::cout << "PageUp      - Increase aperture"                    << std::endl;
  std::cout << "PageDown    - Decrease aperture"                    << std::endl;
  std::cout << "Home        - Reset"                                << std::endl;
  std::cout << "End         - Save screenshot/framebuffer"          << std::endl;
  std::cout << "Left Arrow  - Decrease horizontal subimage index"   << std::endl;
  std::cout << "Right Arrow - Increase horizontal subimage index"   << std::endl;
  std::cout << "Up Arrow    - Decrease vertical subimage index"     << std::endl;
  std::cout << "Down Arrow  - Increase vertical subimage index"     << std::endl;
  std::cout << "Esc         - Quit"                                 << std::endl;
  std::cout << std::endl;

  std::cout << "Or left mouse click and drag the mini light-field image in the upper right corner of the window"  << std::endl;
  std::cout << std::endl;

  std::cout << "0           - SarNone: No synthetic aperture rendering, view full lightfield image"  << std::endl;
  std::cout << "1           - SarCpp:  Synthetic aperture rendering in C++"                          << std::endl;
  std::cout << "2           - SarCV:   Synthetic aperture rendering using OpenCV"                    << std::endl;
  std::cout << "3           - SarGL:   Synthetic aperture rendering using OpenGL GLSL"               << std::endl;
  std::cout << std::endl;
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

  if (rc == 0)
    rc = initMapShader();

  _sarLst.resize(SAR_MAX);

  if (rc == 0)
    rc = initHomographies();
  
  if (rc == 0)
    rc = initSarNone();

  if (rc == 0)
    rc = initSarCpp();

  if (rc == 0)
    rc = initSarCV();

  if (rc == 0)
    rc = initSarGL();

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
                           _mcTex(),
                           _pMapShader(0),
                           _sarLst(),
                           _sarIdx(SAR_NONE),
                           _aP(0),
                           _iIdx(0),
                           _focus(0),
                           _mHLst(0),
                           _bHLst(true),
                           _timer(),
                           _nC(0),
                           _fps(0),
                           _bMouseMotion(false),
                           _vMs(),
                           _vMe()
{
}


//---------------------------------------------------------------------
// ~Executor
//---------------------------------------------------------------------
Executor::~Executor()
{
  delete _pShader;
  delete _pMapShader;
}

