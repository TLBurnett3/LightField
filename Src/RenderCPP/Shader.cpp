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

// 3rdPartyLibs
#include <glm/ext.hpp>

// Lightfield
#include "RenderCPP/Shader.h"
#include "Core/Barycentric.h"

using namespace Lf;
using namespace RenderCPP;
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Notes
// https://learnopengl.com/Getting-started/Coordinate-Systems
// https://carmencincotti.com/2022-05-02/homogeneous-coordinates-clip-space-ndc/
// https://www.songho.ca/opengl/gl_projectionmatrix.html
// https://en.wikipedia.org/wiki/Back-face_culling
// https://bruop.github.io/frustum_culling/
// https://graphicscompendium.com/opengl/24-clipping-culling
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// determine
//---------------------------------------------------------------------
void  Shader::determine(void)
{
  _mMV   = _mV * _mT;
  _mMVP  = _mP * _mMV;

  {
  glm::mat4 mMVs = glm::scale(_mMV,glm::vec3(_nS));

    _mN    = glm::inverseTranspose(glm::mat3(mMVs));
  }
}


//---------------------------------------------------------------------
// processLightFragment
//---------------------------------------------------------------------
void  Shader::processLightFragment(uint8_t *pC,const Coords *pC0,const Coords *pC1,const Coords *pC2,const glm::vec3 &vBC)
{
glm::vec3 vP  = (pC0->_Vvs * vBC.x) + (pC1->_Vvs * vBC.y) + (pC2->_Vvs * vBC.z);
glm::vec3 vN  = (pC0->_Ni  * vBC.x) + (pC1->_Ni  * vBC.y) + (pC2->_Ni  * vBC.z);
glm::vec2 vUV = (pC0->_T   * vBC.x) + (pC1->_T   * vBC.y) + (pC2->_T   * vBC.z);
glm::vec3 vE  = glm::normalize(vP);
glm::vec4 clr = glm::vec4(_pTxtObj->color(vUV));
glm::vec4 aClr(0);
glm::vec4 dClr(0);
glm::vec4 sClr(0);
glm::vec4 tClr(0);

  vN = glm::normalize(vN);

  for (size_t i = 0;i < _lgtLst.size();i++)
  {
  glm::vec3 vL  = glm::normalize(_lgtLst[i]._vPosition - vP);
  glm::vec3 vR  = glm::reflect(vL,vN);

    aClr = clr * _lgtLst[i]._cAmbient;
    dClr = clr * _lgtLst[i]._cDiffuse  * glm::max(glm::dot(vN,vL),0.0f);
    sClr = clr * _lgtLst[i]._cSpecular * glm::pow(glm::max(glm::dot(vR,vE),0.0f),0.3f * _pTxtObj->_s);

    tClr += aClr + dClr + sClr;
  }

  tClr = glm::clamp(tClr,glm::vec4(0),glm::vec4(255));
   
  *(pC + 0) = (uint8_t)tClr.r;
  *(pC + 1) = (uint8_t)tClr.g;
  *(pC + 2) = (uint8_t)tClr.b;
  *(pC + 3) = (uint8_t)tClr.a;
}


//---------------------------------------------------------------------
// processFragment
//---------------------------------------------------------------------
void  Shader::processFragment(uint8_t *pC,const Coords *pC0,const Coords *pC1,const Coords *pC2,const glm::vec3 &vBC)
{
glm::vec2   vUV = (pC0->_T * vBC.x) + (pC1->_T * vBC.y) + (pC2->_T * vBC.z);
glm::uvec4  clr = _pTxtObj->color(vUV);

  *(pC + 0) = clr.x;
  *(pC + 1) = clr.y;
  *(pC + 2) = clr.z;
  *(pC + 3) = clr.a;
}


//---------------------------------------------------------------------
// rasterize
//---------------------------------------------------------------------
void Shader::rasterize(const Coords *pC0,const Coords *pC1,const Coords *pC2)
{
glm::ivec2  vImin;
glm::ivec2  vImax;

  _pFrameBuffer->createRasterIndices(vImin,vImax,pC0,pC1,pC2);

  {
  Barycentric bary(pC0->_vRas,pC1->_vRas,pC2->_vRas);
  glm::vec3   vZ  = glm::vec3(pC0->_Vvs.z,pC1->_Vvs.z,pC2->_Vvs.z);
  glm::vec3   vZi = 1.0f / vZ;
  glm::ivec2  idx;  

    for (idx.y = vImin.y;idx.y <= vImax.y;idx.y++)
    {
    uint32_t  xI    = _pFrameBuffer->hogelSize().x * idx.y;
    float     *pD   = _pFrameBuffer->dthPtr(xI);
    uint8_t   *pC   = _pFrameBuffer->imgPtr(xI);

      idx.x =  vImin.x;
      pD    += idx.x;
      pC    += (4 * idx.x);

      for (;idx.x <= vImax.x;idx.x++)
      {
      glm::vec3 vBC = bary.coordinates(glm::vec2(idx));    

        if ((vBC.x >= 0) && (vBC.y >= 0) && (vBC.z >= 0))
        {
          vBC *= vZi;                       // scale the barycentrics for z depth
          vBC /= (vBC.x + vBC.y + vBC.z);   // ensures vBC sums to ones, thus barycentric again

          {
          glm::vec3 vVmvp = (pC0->_Vcs * vBC.x) + (pC1->_Vcs * vBC.y) + (pC2->_Vcs * vBC.z);
          float     d     = glm::dot(vZ,vBC) * _depthScale;
         
            if (processDepth(pD,d))
              (this->*_pFragFuncPtr)(pC,pC0,pC1,pC2,vBC);
          }
        }
 
        pD++;
        pC += 4;
      }   
    }
  }
}


//---------------------------------------------------------------------
// render
//---------------------------------------------------------------------
void Shader::render(const Vtx3 *pV0,const Vtx3 *pV1,const Vtx3 *pV2)
{
  loadVtxLst(_vtxLstA,pV0,pV1,pV2);

  // the vertices are in view space now
  {
  uint32_t n        = 3;
  Vtx3     *pVtxLst = _clipper.clip(_vtxLstA,_vtxLstB,&n);

    if (n > 2)
    {
    bool  keep = true;

      calculateCoordinates(pVtxLst,_crdLst,n);

      if (_cullFace)
        keep = cullPolygon(_crdLst,n);

      if (keep)
      {       
        for (uint32_t j = 1;j < n - 1;j++)
          rasterize(_crdLst + 0,_crdLst + j + 0,_crdLst + j + 1);
      }
    }
  }
}


//---------------------------------------------------------------------
// Shader
//---------------------------------------------------------------------
Shader::Shader(const char *pName) : _name(pName),
                                    _mP(),
                                    _mMVP(),
                                    _mMV(),
                                    _mN(),
                                    _nS(1.0f),
                                    _depthScale(1.0f),
                                    _cullFace(false),
                                    _lgtLst(),
                                    _vtxLstA(),
                                    _vtxLstB(),
                                    _crdLst(),
                                    _clipper(),
                                    _pTxtObj(0),
                                    _pFrameBuffer(0),
                                    _pFragFuncPtr(&Shader::processFragment)
{
}


//---------------------------------------------------------------------
// ~Shader
//---------------------------------------------------------------------
Shader::~Shader()
{
  // do not delete _pTxtObj or _pFrameBuffer
}
