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

// BtShader.h
// Thomas Burnett


#pragma once

//---------------------------------------------------------------------
// Includes


// 3rdPartyLibs


// Lightfield
#include "RenderCPP/Shader.h"
#include "RenderCPP/BtClipper.h"
#include "HogelDef/Plane.h"
#include "HogelDef/Camera.h"
//---------------------------------------------------------------------

//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace RenderCPP
  {
	  class BtShader : public Shader
	  {
	    // Defines
      private:
      protected:
        enum 
        {
          Keep        = 1,
          NoKeep      = 0,

          FrontFacing = 1,
          BackFacing  = -1
        };

        typedef struct HogelData_def
        {
          glm::mat4 _mMVP;          
          glm::mat4 _mMV;
          glm::mat3 _mN;

        } HogelData;

        typedef std::vector<uint8_t>    StateLst;
        typedef std::vector<HogelData>  HogelDataLst;

      public:

      // Members
      private:
      protected: 
        HogelDef::Plane   *_pHogelPlane;

        glm::mat4         _mVol;

        uint8_t           _objN;    // don't reset, let roll over

        StateLst          _hogelStateLst;
        HogelDataLst      _hogelDataLst;

      public:

       
      // Methods
      private:
      protected:   
        inline bool checkState(const uint32_t hId)
        {
        bool  s = false;
    
          if (_hogelStateLst[hId] != _objN)
          {
          HogelData *pHD  = &_hogelDataLst[hId];
          glm::mat4 mV    = _pHogelPlane->btHogelViewTransform(hId,_mVol);

            _hogelStateLst[hId]  = _objN;

            pHD->_mMV   = mV * _mT;
            pHD->_mN    = glm::mat3(glm::inverseTranspose(pHD->_mMV));
            pHD->_mMVP  = _mP * pHD->_mMV;

            s = true;
          }

          return s;
        }

        inline void loadVtxLst(Vtx3 *pVtx,const Vtx3 *pV0,const Vtx3 *pV1,const Vtx3 *pV2)
        {
          (pVtx + 0)->_V = glm::vec4(pV0->_V,1);
          (pVtx + 0)->_N = pV0->_N;      
          (pVtx + 0)->_T = pV0->_T;

          (pVtx + 1)->_V = glm::vec4(pV1->_V,1);
          (pVtx + 1)->_N = pV1->_N;      
          (pVtx + 1)->_T = pV1->_T;

          (pVtx + 2)->_V = glm::vec4(pV2->_V,1);
          (pVtx + 2)->_N = pV2->_N;      
          (pVtx + 2)->_T = pV2->_T;
        }

        inline void calculateCoordinates(Vtx3 *pVtxLst,Coords *pCrdLst,const uint32_t n,HogelData *pHD)
        {
        Vtx3        *pVtx    = pVtxLst;
        Vtx3        *pVtxEnd = pVtx + n;
        Coords      *pCrds   = pCrdLst;
     
          while (pVtx < pVtxEnd)
          {
            pCrds->_Vvs   =  pHD->_mMV * glm::vec4(pVtx->_V,1.0f);        
            pCrds->_Ni    =  pVtx->_N;        
            pCrds->_T     =  pVtx->_T;           

            pCrds->_Vcs   =  _mP * glm::vec4(pCrds->_Vvs,1);
            pCrds->_Vndc  =  pCrds->_Vcs / pCrds->_Vcs.w;

            pCrds->_vRas.x = _vVpPos.x + (0.5f * (pCrds->_Vndc.x + 1.0f) * _vVpDim.x);
            pCrds->_vRas.y = _vVpPos.y + (0.5f * (pCrds->_Vndc.y + 1.0f) * _vVpDim.y);

            pVtx++;
            pCrds++;
          }
        } 

        //---------------------------------------------------------------------
        // cullPolygon
        // Shoelace algorithm
        //---------------------------------------------------------------------       
        inline bool cullPolygon(const Coords *pNDC,const uint32_t n,const int f)
        {
        bool      k = true;
        float     a2 = 0;

          for (uint32_t i = 0; i < n - 1; i++)
          {
            a2 += (pNDC + i + 0)->_vRas.x * (pNDC + i + 1)->_vRas.y;
            a2 -= (pNDC + i + 1)->_vRas.x * (pNDC + i + 0)->_vRas.y;
          }

          a2 += (pNDC + n - 1)->_vRas.x * (pNDC + 0 + 0)->_vRas.y;
          a2 -= (pNDC + 0 + 0)->_vRas.x * (pNDC + n - 1)->_vRas.y;

          if (f == BackFacing)
          {
            if (a2 <= 0)
              k = false;
          }
          else
          {
            if (a2 >= 0)
              k = false;
          }

          return k;
        }      

      public:

        EXPORT virtual void bindVolume(const glm::mat4 &mVol)
        { _mVol = mVol; }

        EXPORT virtual void  bindHogelPlane(HogelDef::Plane *pHp)
        { 
          _pHogelPlane = pHp; 

          _hogelStateLst.resize(_pHogelPlane->maxHogels());
          _hogelDataLst.resize(_pHogelPlane->maxHogels());

          memset(_hogelDataLst.data(),0x00,_pHogelPlane->maxHogels());
        }
 
        EXPORT virtual void clear(void)
        {}

        EXPORT virtual void determine(void)
        { _objN++; }

        EXPORT virtual void render(const Vtx3 *pV0,const Vtx3 *pV1,const Vtx3 *pV2) = 0;

        EXPORT BtShader(const char *pName);
        EXPORT virtual ~BtShader();
	  };
  };
};

//---------------------------------------------------------------------