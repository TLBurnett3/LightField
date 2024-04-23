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

// Vtx.h
// Thomas Burnett

#pragma once

//---------------------------------------------------------------------
// Includes
// System

// 3rdPartyLibs
#include <glm/glm.hpp>

// Lightfield

//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace RenderCPP
  {
    class Vtx3
    {
      public:
        glm::vec3 _V;
        glm::vec3 _N;
        glm::vec2 _T;

      Vtx3() : _V(), _N(), _T()
      {}
    };

    class Coords
    {
      public:
        glm::vec3   _Vvs;   // vertex in view space
        glm::vec3   _Ni;
        glm::vec2   _T;

        glm::vec4   _Vcs;   // vertex in clip space
        glm::vec4   _Vndc;  // vertex in NDC (_Vcs / _Vcs.w)

        glm::vec2   _vRas;

      Coords() : _Vcs(), _Vvs(), _Ni(), _T(), _vRas()
      {}
    };
  };
};
//---------------------------------------------------------------------

//void printMat4(const char *pS,const glm::mat4 &m);

//void printVtx3(const char *pStr,const MvPU::Vtx3 *pV0,const MvPU::Vtx3 *pV1,const MvPU::Vtx3 *pV2,const glm::mat4 &mT = glm::mat4());
//void printVtx3(const char *pStr,const MvPU::Vtx3 *pV0,const MvPU::Vtx3 *pV1,const MvPU::Vtx3 *pV2,const glm::mat4 &mT1,const glm::mat4 &mT2);

//void printVtxLst  (const char *pStr,const MvPU::Vtx4 *pVtxLst,const uint32_t n,const glm::mat4 &mT);
//void printVtxLst  (const char *pStr,const MvPU::Vtx4 *pVtxLst,const uint32_t n);
//void printCoordLst(const char *pStr,const MvPU::Coords *pCrdLst,const uint32_t n);
