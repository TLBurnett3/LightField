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

// Shader.h
// Thomas Burnett


#pragma once

//---------------------------------------------------------------------
// Includes
#include <string>
#include <vector>
#include <filesystem>

// 3rdPartyLibs
#include <glm/glm.hpp>

// Lightfield
#include "Core/Export.h"
#include "RenderCPP/TxtObj.h"
#include "RenderCPP/LgtObj.h"
#include "RenderCPP/Vtx.h"
#include "RenderCPP/Clipper.h"
#include "RenderCPP/FrameBuffer.h"
//---------------------------------------------------------------------

//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace RenderCPP
  {
	  class Shader
	  {
	    // Defines
      private:
      protected:

        typedef std::vector<LgtObj>     LgtLst;

        typedef void (Shader::*FragFuncPtr)(uint8_t *pC,const Coords *pC0,const Coords *pC1,const Coords *pC2,const glm::vec3 &vBC);
      public:
        enum
        {
          MaxVtx   = 8,    
        };

        enum
        {
          Keep        = 1,
          NoKeep      = 0,

          FrontFace   = 0,
          BackFace    = 1,
        };

      // Members
      private:
      protected: 
      public:
        std::string   _name;

        glm::vec2     _vVpPos;
        glm::vec2     _vVpDim;

        glm::mat4     _mT;
        glm::mat4     _mV;
        glm::mat4     _mP;

        glm::mat4     _mMVP;
        glm::mat4     _mMV;
        glm::mat3     _mN;

        float         _nS;
        float         _depthScale;
        bool          _cullFace;  

        LgtLst        _lgtLst;   

        Vtx3          _vtxLstA[MaxVtx];
        Vtx3          _vtxLstB[MaxVtx];
        Coords        _crdLst[MaxVtx];
        Clipper       _clipper;

        TxtObj        *_pTxtObj;
  
        FrameBuffer   *_pFrameBuffer;
        FragFuncPtr   _pFragFuncPtr;
       
      // Methods
      private:
      protected:
        inline void loadVtxLst(Vtx3 *pVtx,const Vtx3 *pV0,const Vtx3 *pV1,const Vtx3 *pV2)
        {
          (pVtx + 0)->_V = _mMV * glm::vec4(pV0->_V,1);
          (pVtx + 0)->_N = _mN  * pV0->_N;      
          (pVtx + 0)->_T = pV0->_T;

          (pVtx + 1)->_V = _mMV * glm::vec4(pV1->_V,1);
          (pVtx + 1)->_N = _mN  * pV1->_N;      
          (pVtx + 1)->_T = pV1->_T;

          (pVtx + 2)->_V = _mMV * glm::vec4(pV2->_V,1);
          (pVtx + 2)->_N = _mN  * pV2->_N;      
          (pVtx + 2)->_T = pV2->_T;
        }

        inline void calculateCoordinates(Vtx3 *pVtxLst,Coords *pCrdLst,const uint32_t n)
        {
        Vtx3        *pVtx    = pVtxLst;
        Vtx3        *pVtxEnd = pVtx + n;
        Coords      *pCrds   = pCrdLst;
     
          while (pVtx < pVtxEnd)
          {
            pCrds->_Vvs   =  pVtx->_V;        
            pCrds->_Ni    =  pVtx->_N;        
            pCrds->_T     =  pVtx->_T;           

            pCrds->_Vcs   =  _mP * glm::vec4(pVtx->_V,1);
            pCrds->_Vndc  =  pCrds->_Vcs / pCrds->_Vcs.w;

            pCrds->_vRas.x = _vVpPos.x + (0.5f * (pCrds->_Vndc.x + 1.0f) * _vVpDim.x);
            pCrds->_vRas.y = _vVpPos.y + (0.5f * (pCrds->_Vndc.y + 1.0f) * _vVpDim.y);

            pVtx++;
            pCrds++;
          }
        } 

        // Shoelace algorithm
        inline bool cullPolygon(const Coords *pCrd,const uint32_t n)
        {
        bool     k  = true;
        float    a2 = 0;

          for (uint32_t i = 0; i < n - 1; i++)
          {
            a2 += (pCrd + i + 0)->_vRas.x * (pCrd + i + 1)->_vRas.y;
            a2 -= (pCrd + i + 1)->_vRas.x * (pCrd + i + 0)->_vRas.y;
          }

          a2 += (pCrd + n - 1)->_vRas.x * (pCrd + 0 + 0)->_vRas.y;
          a2 -= (pCrd + 0 + 0)->_vRas.x * (pCrd + n - 1)->_vRas.y;

          if (a2 <= 0)
            k = false;

          return k;
        }    

        inline bool  processDepth(float *pD,float d)
        {
        bool      keep    = false;

          keep = d < *pD;

          if (keep)
            *pD = d;

          return keep;
        }

        void processLightFragment (uint8_t *pC,const Coords *pC0,const Coords *pC1,const Coords *pC2,const glm::vec3 &vBC);
        void processFragment      (uint8_t *pC,const Coords *pC0,const Coords *pC1,const Coords *pC2,const glm::vec3 &vBC);

        void rasterize(const Coords *pC0,const Coords *pC1,const Coords *pC2);

      public:
        EXPORT void bindFrameBuffer(FrameBuffer *pFB)
        { _pFrameBuffer = pFB; }

        EXPORT void bindCullFace(const bool cF)
        { _cullFace = cF; }

        EXPORT void bindDepthScale(const float dS)
        { _depthScale = dS; }

        EXPORT void bindViewport(glm::vec2 &vP,const glm::vec2 &hS)
        { 
          _vVpPos = vP;
          _vVpDim = hS;
        };

        EXPORT virtual void bindTexture(TxtObj *pT)
        { _pTxtObj = pT; }

        EXPORT void bindNormalScale(const float s) 
        {
          if (s < 0)
            _nS = -1.0f;
          else
            _nS = 1.0f;
        }

        EXPORT void bindLight(const glm::vec3 &vP,
                              const glm::vec4 &cA,const glm::vec4 &cD,const glm::vec4 &cS,
                              const float att)
        {
          _lgtLst.emplace_back(vP,cA,cD,cS,att);

          _pFragFuncPtr = &Shader::processLightFragment;
        } 

        EXPORT void bindProjection(const glm::mat4 &m)
        { 
          _mP = m; 

          _clipper.set(_mP);
        }

        EXPORT void bindView(const glm::mat4 &m)
        { _mV = m; }

        EXPORT void bindModel(const glm::mat4 &m)
        { _mT = m; }

        EXPORT virtual void determine(void);
 
        EXPORT virtual void render(const Vtx3 *pV0,const Vtx3 *pV1,const Vtx3 *pV2);

        EXPORT Shader(const char *pName);
        EXPORT virtual ~Shader();
	  };
  };
};

//---------------------------------------------------------------------