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

// SarNone.cpp 
// Thomas Burnett


//---------------------------------------------------------------------
// Includes
// System

// 3rdPartyLibs

// LightField
#include "Aperture/SarNone.h"

using namespace Lf;
using namespace Aperture;
//---------------------------------------------------------------------



//---------------------------------------------------------------------
// render
//---------------------------------------------------------------------
void SarNone::render(const glm::mat4 &mP,const glm::mat4 &mV,
                     RenderGL::BasicShader *pS,RenderGL::Texture &mcTex,RenderGL::VtxArrayObj &vao)
{
  pS->use();
  pS->bindMVP(mP * mV);
  pS->bindTextureSampler(0);

  mcTex.bind();
  vao.render();
}


//---------------------------------------------------------------------
// init
//---------------------------------------------------------------------
int SarNone::init(void)
{
int   rc = 0;


  return rc;
}



//---------------------------------------------------------------------
// SarNone
//---------------------------------------------------------------------
SarNone::SarNone(void) : Sar("SarNone")
{
}


//---------------------------------------------------------------------
// ~SarNone
//---------------------------------------------------------------------
SarNone::~SarNone()
{

}

