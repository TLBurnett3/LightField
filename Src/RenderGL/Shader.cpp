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

// Shader.cpp
// Thomas Burnett


//---------------------------------------------------------------------
// Includes
// System
#include <assert.h>
#include <fstream>
#include <iostream>

// tLib
#include "RenderGL/Shader.h"

using namespace Lf;
using namespace RenderGL;
//---------------------------------------------------------------------


//---------------------------------------------------------------------

//---------------------------------------------------------------------


//---------------------------------------------------------------------
// addSourceFile 
//---------------------------------------------------------------------
int Shader::addSourceFile(const std::filesystem::path &filePath,ShaderSrcLst &shaderSrcLst) 
{
int             rc   = -1;
std::ifstream   fIn(filePath.string().c_str());

  if (!fIn.fail())
  {
    fIn.close();

   shaderSrcLst.push_back(filePath);

   rc = 0;
 }
 else
 {
   std::cout << "Can not find shader file: ";
   std::cout << filePath.string().c_str() << std::endl;

   rc = -1;
 }

  return rc;
}


//---------------------------------------------------------------------
// loadShaderSource
//---------------------------------------------------------------------
int Shader::loadShaderSource(const GLuint sId,ShaderSrcLst &shaderSrcLst) 
{
int     n       = (int)shaderSrcLst.size();
char    **pSrc  = new char *[n];
int     *pLen   = new int[n];
int     rc      = -1;

  for (int i = 0;i < n;i++)
  {
  FILE *fp = fopen(shaderSrcLst[i].string().c_str(),"r");
  long len;
 
  	fseek(fp,0,SEEK_END);
	  len = ftell(fp);
 
	//  printf("File '%s' is %ld long\n",shaderSrcLst[i].string().c_str(), len);
 
	  fseek(fp,0,SEEK_SET);
 
    pSrc[i] = new char[len];
 
	  pLen[i] = (int)fread(pSrc[i],sizeof(char),len,fp);
 
	  //pSrc[i][pLen[i] - 1] = '\0'; /* Shader sources have to term with null */
 
  //  printf("%s",pSrc[i]);

    rc = 0;
    fclose(fp);
  }

  glShaderSource(sId,n,(const GLchar **)pSrc,pLen);
  
  delete[] pSrc;
  delete[] pLen;
  //for (int i = 0;i < n;i++)
  //  delete pSrc[i];
  //
  //delete pSrc;
  //delete pLen;

  return rc;
}



//---------------------------------------------------------------------
// createShader 
//---------------------------------------------------------------------
int Shader::createShader(GLuint sId,const int sType,ShaderSrcLst &shaderSrcLst) 
{
int rc  = -1;

 // assert(glCreateShader);

  rc = loadShaderSource(sId,shaderSrcLst);

  if (rc == 0)
  {
    glCompileShader(sId);

    GLint stat;
    glGetShaderiv(sId,GL_COMPILE_STATUS,&stat);     

    if (stat == GL_FALSE)
    {
    GLint logLen = 0;

      glGetShaderiv(sId,GL_INFO_LOG_LENGTH,&logLen);   

      if (logLen > 0)
      {
      char  log[512];
      std::string str;

        glGetShaderInfoLog(sId,512,NULL,log);     
        str = "Shader Create Log: ";
        str += log;

        std::cout << str.c_str() << std::endl;
      }
    }
  }

  return rc;
}



//---------------------------------------------------------------------
// checkStatus
//---------------------------------------------------------------------
int Shader::checkStatus(const char *pStr,const int check)
{
int logLen = 0;  
int rc     = 0;
GLint stat = 0;

  glGetProgramiv(_programShaderId,check,&stat);

  if (stat == GL_FALSE)
  {
    // Check the status of the compile/link      
    glGetProgramiv(_programShaderId,GL_INFO_LOG_LENGTH,&logLen);
    if (logLen > 0)
    {
    char  log[512];
    std::string str;

      std::cout << pStr << std::endl;
      std::cout << "Shader Program Compile/Link Failed" << std::endl;

      glGetProgramInfoLog(_programShaderId,512,&logLen,log);
      str = "Prog Info Log: ";
      str += log;

      std::cout << str.c_str() << std::endl;
    }

    rc = -1;
  }

  return rc;
}


//---------------------------------------------------------------------
// detachShaders
//---------------------------------------------------------------------
void Shader::detachShaders(void) 
{
  if (_programShaderId)
  {
    std::cout << "Detaching Shader Program" << std::endl;

    if (_vertexShaderId)
    {
      glDetachShader(_programShaderId,_vertexShaderId);
    }

    if (_geometryShaderId)
    {
      glDetachShader(_programShaderId,_geometryShaderId);
    }

    if (_fragmentShaderId)
    {
      glDetachShader(_programShaderId,_fragmentShaderId);
    }
  }
}


//---------------------------------------------------------------------
// compile
//---------------------------------------------------------------------
int Shader::compile(void) 
{
int rc = -1;

  std::cout << "Compiling Shader:" << _sName << std::endl;

  detachShaders();
        
  if (!_programShaderId)
  {
    if (!_vertexShaderId && !_vertexShaderLst.empty())
      _vertexShaderId = glCreateShader(GL_VERTEX_SHADER);

#ifndef _GLES2
    if (!_geometryShaderId && !_geometryShaderLst.empty())
      _geometryShaderId = glCreateShader(GL_GEOMETRY_SHADER);
#endif

    if (!_fragmentShaderId && !_fragmentShaderLst.empty())
      _fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    _programShaderId  = glCreateProgram();
  }

  if (_programShaderId)
  {
    if (_vertexShaderId)
      rc =  createShader(_vertexShaderId,GL_VERTEX_SHADER,_vertexShaderLst);

#ifndef _GLES2
    if (_geometryShaderId)
      rc =  createShader(_geometryShaderId,GL_GEOMETRY_SHADER,_geometryShaderLst);
#endif

    if (_fragmentShaderId)
      rc |= createShader(_fragmentShaderId,GL_FRAGMENT_SHADER,_fragmentShaderLst);
  }


  if (rc == 0)
  {
    if (_vertexShaderId)
    {
      glAttachShader(_programShaderId,_vertexShaderId);
      rc |= checkStatus("glAttachShader (Vertex)",GL_ATTACHED_SHADERS);
    }

#ifndef _GLES2
    if (_geometryShaderId)
    {
      glAttachShader(_programShaderId,_geometryShaderId);
      rc |= checkStatus("glAttachShader (Geometry)",GL_ATTACHED_SHADERS);
    }
#endif

    if (_fragmentShaderId)
    {
      glAttachShader(_programShaderId,_fragmentShaderId);
      rc |= checkStatus("glAttachShader (Fragment)",GL_ATTACHED_SHADERS);
    }

    if (rc == 0)
    {
      glLinkProgram(_programShaderId);
      rc |= checkStatus("glLinkProgram",GL_LINK_STATUS);
    }

#ifdef _WIN32
    if (rc == 0)
    {
      // Validate program
      glValidateProgram(_programShaderId);
      rc |= checkStatus("glValidateProgram",GL_VALIDATE_STATUS);
    }
#endif
  }

  return rc;
}



//---------------------------------------------------------------------
// Shader
//---------------------------------------------------------------------
Shader::Shader(const char *pName) : _sName(pName),
                                    _vertexShaderLst(),
                                    _geometryShaderLst(),
                                    _fragmentShaderLst(),
                                    _programShaderId(0),
                                    _vertexShaderId(0),                                             
                                    _geometryShaderId(0),
                                    _fragmentShaderId(0)
{
}


//---------------------------------------------------------------------
// ~Shader
//---------------------------------------------------------------------
Shader::~Shader()
{
}
