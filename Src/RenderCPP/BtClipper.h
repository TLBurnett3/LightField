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

// BtClipper.h
// Thomas Burnett

#pragma once

//---------------------------------------------------------------------
// Includes
// System
#include <vector>

// 3rdPartyLibs

// Lightfield
#include "RenderCPP/Vtx.h"
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Helpful links
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
// https://www.gamedev.net/forums/topic/609769-derive-fov-from-projection-matrix-how/
// http://lektiondestages.blogspot.com/2013/11/decompose-opengl-projection-matrix.html
// http://www.songho.ca/opengl/gl_projectionmatrix.html
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/#the-projection-matrix
//---------------------------------------------------------------------

//---------------------------------------------------------------------
// Note:
// Traditionally, Clipping is done in Homegeneous Clip Space which is Left-handed,
// This means that the inputs have had the projection matrix applied,
// but not perspective division
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace RenderCPP
  {
    class BtClipper
    {
      // Defines
      private:
      protected:
        #define InFrontOfPlane        1.0f
        #define IntersectsPlane               0.0f      
        #define InBackOfPlane        -1.0f

        enum PlaneDef
        {
          LeftPlane = 0,
          TopPlane,
          RightPlane,
          BottomPlane,     
          MaxPlanes,                      
        };

       public:

        enum DirectionDef
        {
          PntNorth  =  (0x1 << TopPlane),
          PntSouth  =  (0x1 << BottomPlane),
          PntEast   =  (0x1 << RightPlane),
          PntWest   =  (0x1 << LeftPlane),

          PntAll    = PntNorth | PntSouth | PntEast | PntWest,

          Visible = 0,
        };

        enum FrustumDef
        {
          Back = 0,
          Front,
          MaxFrustums,
        };


      // Members
      private:   
      protected:
        glm::vec4   _cPlanes  [MaxFrustums][MaxPlanes];

      public:  

      // Methods
      private:
      protected:
        float classify(const glm::vec4 &plane,const glm::vec3 &v)
        {
        float d = (plane.x * v.x) + (plane.y * v.y) + (plane.z * v.z) + (plane.w);

          return (d < 0) ? InBackOfPlane : (d > 0) ? InFrontOfPlane : IntersectsPlane;
        }  

        bool approxEqual(float a,float b)
        { return std::fabs(a - b) <= std::numeric_limits<float>::epsilon(); }

        bool keepClip(Vtx3 *pVtxLst,uint32_t n)
        {
        bool v = true;

          if (n > 0)
          {
          Vtx3 *pV0 = pVtxLst + (n - 1);
          Vtx3 *pV1 = pVtxLst + n;

            v = !(approxEqual(pV0->_V.x,pV1->_V.x) && 
                  approxEqual(pV0->_V.y,pV1->_V.y) && 
                  approxEqual(pV0->_V.z,pV1->_V.z));
          }

          return v;
        }

        void intersect(const glm::vec4 &plane,const Vtx3 *p0,const Vtx3 *p1,Vtx3 *p2)
        {
        glm::vec3 vD = p1->_V - p0->_V;
        glm::vec3 vN = glm::vec3(plane);
        float     t  = -(glm::dot(p0->_V,vN) + plane.w) / glm::dot(vD,vN);

          p2->_V = p0->_V + ((p1->_V - p0->_V) * t);
          p2->_N = p0->_N + ((p1->_N - p0->_N) * t);                     
          p2->_T = p0->_T + ((p1->_T - p0->_T) * t);                               
        }
 
        void clipEdge(const glm::vec4 &plane,Vtx3 *pI0,Vtx3 *pI1,Vtx3 *pO,uint32_t *n);

      public:
        uint8_t  classify(const FrustumDef fD,const Vtx3 *pV0,const Vtx3 *pV1,const Vtx3 *pV2);
        float    classifyHogelPlane(const Vtx3 *pV0,const Vtx3 *pV1,const Vtx3 *pV2);
   
        Vtx3 *clip  (FrustumDef fD,Vtx3 *pA,Vtx3 *pB,uint32_t *n);

        void set(const glm::mat4 &m);

        BtClipper(const glm::mat4 &m)
        { set(m); }

        BtClipper(void)
        { set(glm::mat4()); }
    };
  };
};
//---------------------------------------------------------------------

