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

// SarGL.cpp 
// Thomas Burnett


//---------------------------------------------------------------------
// Includes
// System

// 3rdPartyLibs

// LightField
#include "Aperture/SarGL.h"

using namespace Lf;
using namespace Aperture;
//---------------------------------------------------------------------



//---------------------------------------------------------------------
// render
//---------------------------------------------------------------------
void SarGL::render(const glm::mat4 &mP,const glm::mat4 &mV,
                   RenderGL::BasicShader *pS,RenderGL::Texture &mcTex,RenderGL::VtxArrayObj &vao)
{
  _pShader->use();
  _pShader->bindMVP(mP * mV);
  _pShader->bindTextureSampler(0);
  _pShader->bindAperture(_aP);
  _pShader->bindImageIndex(_iIdx);

  if (_pMHLst)
    _pShader->bindHomographies(_pMHLst);

  _pMHLst = 0;

  mcTex.bind();
  vao.render();
}


//---------------------------------------------------------------------
// init
//---------------------------------------------------------------------
int SarGL::init(const glm::ivec2 &nI,const glm::ivec2 &iS)
{
int   rc = 0;

  _pShader = new SarShader("SarGL");

  _iS = iS;

  rc |= _pShader->addVertexShader  ("./Shaders/Default3D.vtx");
  rc |= _pShader->addFragmentShader("./Shaders/Aperture.frg");

  if (rc == 0)
    rc = _pShader->compile();  

  if (rc == 0)
  {
    _pShader->use();
    _pShader->bindImageSize(iS);
    _pShader->bindNumImages(nI);
  }

  return rc;
}



//---------------------------------------------------------------------
// SarGL
//---------------------------------------------------------------------
SarGL::SarGL(void) : Sar("SarGL"),
                     _pShader(0)

{
}


//---------------------------------------------------------------------
// ~SarGL
//---------------------------------------------------------------------
SarGL::~SarGL()
{
  delete _pShader;
}

