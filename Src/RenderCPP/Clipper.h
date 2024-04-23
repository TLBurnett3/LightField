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

// Clipper.h
// Thomas Burnett

#pragma once

//---------------------------------------------------------------------
// Includes
// System
#include <vector>

// 3rdPartyLibs
#include <glm/glm.hpp>

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
    class Clipper
    {
      // Defines
      private:
      protected:
        #define InFrontOfPlane        1.0f
        #define IntersectsPlane       0.0f      
        #define InBackOfPlane        -1.0f

        enum PlaneDef
        {
          LeftPlane = 0,
          TopPlane,
          RightPlane,
          BottomPlane,  
          FarPlane,           
          NearPlane,       
          MaxPlanes,                      
        };

       public:

      // Members
      private:   
      protected:
        glm::vec4   _cPlanes  [MaxPlanes];

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
        glm::vec3 v0 = glm::vec3(p0->_V);
        glm::vec3 v1 = glm::vec3(p1->_V);
        glm::vec3 vD = v1 - v0;
        glm::vec3 vN = glm::vec3(plane);
        float     t  = -(glm::dot(v0,vN) + plane.w) / glm::dot(vD,vN);

          p2->_V  = p0->_V  + ((p1->_V  - p0->_V)  * t);                     
          p2->_N  = p0->_N  + ((p1->_N  - p0->_N)  * t);                     
          p2->_T  = p0->_T  + ((p1->_T  - p0->_T)  * t);                                                  
        }

        void clipEdge(const glm::vec4 &plane,Vtx3 *pI0,Vtx3 *pI1,Vtx3 *pO,uint32_t *n);

      public:
   
        Vtx3 *clip  (Vtx3 *pA,Vtx3 *pB,uint32_t *n);

        void set(const glm::mat4 &m);

        Clipper(const glm::mat4 &m)
        { set(m); }

        Clipper(void)
        { set(glm::mat4()); }
    };
  };
};
//---------------------------------------------------------------------

