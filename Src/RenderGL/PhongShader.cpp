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

// PhongShader.cpp
// Thomas Burnett


//---------------------------------------------------------------------
// Includes
// System
#include <assert.h>
#include <fstream>
#include <iostream>

// tLib
#include "RenderGL/PhongShader.h"

using namespace Lf;
using namespace RenderGL;
//---------------------------------------------------------------------


//---------------------------------------------------------------------

//---------------------------------------------------------------------


//---------------------------------------------------------------------
// compile
//---------------------------------------------------------------------
int PhongShader::compile(void) 
{
int rc = BasicShader::compile();

  if (rc == 0)
  {
    _locMatMV     = glGetUniformLocation(_programShaderId,"mMV");     
    if (_locMatMV < 0)
    {
      std::cout << "Failed to locate ModelView Matrix\n";
      rc = -1;
    }

    _locMatN     = glGetUniformLocation(_programShaderId,"mN");     
    if (_locMatN < 0)
    {
      std::cout << "Failed to locate Normal Matrix\n";
      rc = -1;
    }  

    _locLightPosition     = glGetUniformLocation(_programShaderId,"lightPosition");     
    if (_locLightPosition < 0)
    {
      std::cout << "Failed to locate Light Position\n";
      rc = -1;
    } 

    _locLightAmbient     = glGetUniformLocation(_programShaderId,"lightAmbient");     
    if (_locLightAmbient < 0)
    {
      std::cout << "Failed to locate Ambient Light\n";
      rc = -1;
    } 

    _locLightDiffuse     = glGetUniformLocation(_programShaderId,"lightDiffuse");     
    if (_locLightDiffuse < 0)
    {
      std::cout << "Failed to locate Diffuse Light\n";
      rc = -1;
    } 

    _locLightSpecular     = glGetUniformLocation(_programShaderId,"lightSpecular");     
    if (_locLightSpecular < 0)
    {
      std::cout << "Failed to locate Specular Light\n";
      rc = -1;
    } 

    _locCameraPosition     = glGetUniformLocation(_programShaderId,"cameraPosition");     
    if (_locCameraPosition < 0)
    {
      std::cout << "Failed to locate Camera Position\n";
      rc = -1;
    }  
  }

  return rc;
}



//---------------------------------------------------------------------
// PhongShader
//---------------------------------------------------------------------
PhongShader::PhongShader(const char *pName) : BasicShader(pName),
                                              _nS(1.0f),
                                              _locMatMV(-1),
                                              _locMatN(-1),
                                              _locLightPosition(-1),
                                              _locLightAmbient(-1),
                                              _locLightDiffuse(-1),
                                              _locLightSpecular(-1),
                                              _locCameraPosition(-1)
{
}


//---------------------------------------------------------------------
// ~PhongShader
//---------------------------------------------------------------------
PhongShader::~PhongShader()
{
}
