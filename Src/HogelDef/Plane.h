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

// HogelDef.h
// Thomas Burnett


#pragma once

//---------------------------------------------------------------------
// Includes
// System
#include <vector>
#include <string>

// 3rdPartyLibs


// Lightfield
#include "HogelDef/Hogel.h"
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace HogelDef
  {
    class Plane 
    {
      // Defines
      private:
      protected:
      public:

      // Members
      private:
      protected:     
        HogelLst      _hglLst;
   
        glm::ivec2    _nH;      // number of hogels in each dimension of the hogel plane
        glm::vec2     _hS;      // the dimensions, in pixels, of the rendered portion of each hogel
        glm::vec2     _hP;      // the hogel pitch, or the distance, in pixels, between adjacent hogel centers
        glm::vec2     _radDim;  // the dimensions, in pixels, of the full radiance image (_nH * _hP)
        float         _fov;     // the field of view, in degrees, of each hogel's view frustum
        float         _aR;      // Hogel aspect ratio

        glm::vec3     _vMinE;   // the minimum extent of the hogel plane in normalized hogel plane space ([-0.5,0.5] in each dimension)
        glm::vec3     _vMaxE;   // the maximum extent of the hogel plane in normalized hogel plane space ([-0.5,0.5] in each dimension)
        glm::vec3     _vHWE;

      public:   

      // Methods
      private:
      protected:    
        glm::mat4 dfBackViewFrustum (const glm::vec3 &vE,const glm::vec3 &vD,const glm::vec3 &vU);
        glm::mat4 dfFrontViewFrustum(const glm::vec3 &vE,const glm::vec3 &vD,const glm::vec3 &vU);

        glm::mat4 hogelTransform(const glm::vec3 &v)
        {
        glm::vec4 vR( 1.0f, 0.0f, 0.0f, 0.0f);
        glm::vec4 vU( 0.0f, 0.0f, 1.0f, 0.0f);
        glm::vec4 vD( 0.0f, 1.0f, 0.0f, 0.0f);
        glm::vec4 vP(v,1.0f);
        glm::mat4 mT(vR,vU,vD,vP);

          return mT;
        }

      public:
        Hogel *hogel(const glm::ivec2 &idx) 
        { return &_hglLst[(idx.y * _nH.x) + idx.x]; }

        uint32_t  hogelId(const glm::ivec2 &idx) const
        { return ((idx.y * _nH.x) + idx.x); }

        uint32_t  maxHogels(void)
        { return (_nH.x * _nH.y); }

        glm::ivec2 numHogels(void)
        { return _nH; }

        glm::ivec2 maxHogelIndex(void)
        { return _nH; }

        void setNumHogels(glm::ivec2 &nH)
        { _nH = nH; }

        glm::vec2 hogelPitch(void)
        { return _hP; }
  
        glm::vec2 hogelSize(void)
        { return _hS; }

        glm::vec2 directionalResolution(void)
        { return _hS; }

        float aspectRatio(void)
        { return _aR; }
  
        void setDirectionalResolution(glm::ivec2 &hS)
        { _hS = hS; }

        void setHogelSize(glm::ivec2 &hS)
        { _hS = hS; }

        void setHogelPitch(glm::vec2 &hP)
        { _hP = hP; }

			  void getRadianceDimensions(glm::ivec2 &rD)
			  { rD = glm::ivec2(_radDim); }

        float fov(void)
        { return _fov; }

        Hogel *hogel(const uint32_t i)
        { return &_hglLst[i]; }

        const glm::ivec2 hogelIndexFromNormalizedPlanePosition(const glm::vec2 &vP)
        {
        glm::ivec2 vI(0);
        float      x  =  glm::clamp( vP.x,_vMinE.x,_vMaxE.x);
        float      y  =  glm::clamp(-vP.y,_vMinE.z,_vMaxE.z);

          x += _vHWE.x;
          y += _vHWE.z;

          vI.x = (uint32_t)(x * (float)_nH.x-1);
          vI.y = (uint32_t)(y * (float)_nH.y-1);

          return vI;
        }

        glm::mat4 viewPort(const uint32_t id);
			  void viewPort(const uint32_t id, glm::ivec2 &vS, glm::ivec2 &hS);

        glm::mat4 btHogelViewTransform    (const uint32_t id,const glm::mat4 &mT = glm::mat4(1));
        void dfHogelViewTransforms        (const uint32_t id,glm::mat4 &mVf,glm::mat4 &mVb,const glm::mat4 &mT = glm::mat4(1));

        glm::mat4 btCameraTransform       (const uint32_t id,const glm::mat4 &mT = glm::mat4(1));
        glm::mat4 radianceImageTransform  (const glm::mat4 &mT = glm::mat4(1));
        glm::mat4 radianceViewTransform   (const glm::mat4 &mT = glm::mat4(1));

        int   create(const glm::ivec2 &nH,const glm::vec2 &hS,const glm::vec2 &hP,const float fov);

        void print(void);

        Plane(void);
       ~Plane();
    };
  };
};
//---------------------------------------------------------------------
