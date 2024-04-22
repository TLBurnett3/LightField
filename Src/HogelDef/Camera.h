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

// Thomas Burnett
// Camera.h

#pragma once


//---------------------------------------------------------------------
// Includes
// System

// 3rdPartyLibs
#include <glm/ext.hpp>

// Lightfield


//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace HogelDef
  {
    class Camera
    {
    // Defines
      private:
      protected:
      public:
        enum 
        {
          BackFrustum   = 1,
          NormalFrustum = 0,
          FrontFrustum  = -1,
        };


      // Members
      private:
      protected:
        glm::mat4         _mProj;
        float             _zNear;
        float             _zFar;
        float             _aR;
        glm::vec2         _sF;
        float             _tang;

        glm::mat4         _mView;
        glm::vec3         _vE;
        glm::vec3         _vD;  // maintain these for isVisible test
        glm::vec3         _vU;
        glm::vec3         _vR;

        int               _frustum;

      public:

      // Methods
      private:
      protected:
 
      public:
        const glm::vec3 &vE(void)
        { return _vE; }

        const glm::vec3 &vD(void)
        { return _vD; }

        const glm::vec3 &vU(void)
        { return _vU; }

        const glm::vec3 &vR(void)
        { return _vR; }      

        const float zNear(void)
        { return _zNear; }

        const float zFar(void)
        { return _zFar; }

        const int frustum(void)
        { return _frustum; }

        const glm::quat orientation(void)
        { return glm::quat_cast(_mView); }

        const glm::mat4 &projection(void) const
        { return _mProj; }

        const glm::mat4 &view(void) const
        { return _mView; }

        void setOrthographic(const float left,const float right,
                              const float bottom,const float top,
                              const float zNear,const float zFar)
        { 
          _mProj = glm::ortho(left,right,bottom,top,zNear,zFar);
        }

        void setPerspective(const float fov,const float aR,const float zN,const float zF)
        { 
        float  hA = glm::radians(fov * 0.5f);

          _mProj = glm::perspective(glm::radians(fov),aR,zN,zF);
          _aR    = aR;
          _zNear = zN;
          _zFar  = zF;
          _tang  = (float)glm::tan(hA);
          _sF    = glm::vec2(1.0f/glm::cos(glm::atan(_tang*aR)),1.0f/glm::cos(hA));
        }

        void setPerspective(const float fov)
        {
        float tanHalfFovy = tan(glm::radians(fov) / 2.0f);

	        _mProj = glm::mat4(0);
	        _mProj[0][0] = 1.0f / tanHalfFovy;
	        _mProj[1][1] = 1.0f / tanHalfFovy;
	        _mProj[2][3] = -1.0f;
	        _mProj[3][2] = -1.0f;
        }
            
        void lookAt(const glm::vec3 &vE,const glm::vec3 &vD,const glm::vec3 &vU)
        { 
        glm::vec3 f(normalize(vD));
		    glm::vec3 s(normalize(cross(f,vU)));
		    glm::vec3 u(cross(s,f));

          _vE    = vE;
          _vD    = f;
          _vU    = u;
          _vR    = s;

          _mView[0][0] = s.x;  
		      _mView[1][0] = s.y;
		      _mView[2][0] = s.z;
		      _mView[3][0] = -glm::dot(s,vE);

		      _mView[0][1] = u.x;
		      _mView[1][1] = u.y;
		      _mView[2][1] = u.z;
		      _mView[3][1] = -glm::dot(u,vE);

		      _mView[0][2] = -f.x;
		      _mView[1][2] = -f.y;
		      _mView[2][2] = -f.z;
		      _mView[3][2] = glm::dot(f,vE);

		      _mView[0][3] = 0;
		      _mView[1][3] = 0;
		      _mView[2][3] = 0;
		      _mView[3][3] = 1;

          _frustum = NormalFrustum;
        }

        void lookAt(const glm::vec3 &vE,const glm::quat &qO)
        { 
        glm::mat3 mR = glm::mat3_cast(qO);

          lookAt(vE,mR[2],mR[1]);
        }

        void backFrustum(const glm::vec3 &vE,const glm::vec3 &vD,const glm::vec3 &vU)
        {      
        glm::vec3 f(normalize(vD));
		    glm::vec3 s(normalize(cross(f,vU)));
		    glm::vec3 u(cross(s,f));

           _vE    = vE;
           _vD    = f;
           _vU    = u;
           _vR    = s;

          _mView[0][0] = s.x;
		      _mView[1][0] = s.y;
		      _mView[2][0] = s.z;
		      _mView[3][0] = -glm::dot(s,vE);

		      _mView[0][1] = u.x;
		      _mView[1][1] = u.y;
		      _mView[2][1] = u.z;
		      _mView[3][1] = -glm::dot(u,vE);

		      _mView[0][2] = -f.x;
		      _mView[1][2] = -f.y;
		      _mView[2][2] = -f.z;
		      _mView[3][2] = glm::dot(f,vE);

		      _mView[0][3] = 0;
		      _mView[1][3] = 0;
		      _mView[2][3] = 0;
		      _mView[3][3] = 1;

          _frustum = BackFrustum;
        }
      
        void frontFrustum(const glm::vec3 &vE,const glm::vec3 &vD,const glm::vec3 &vU)
        {       
        glm::vec3 f(normalize(vD));
		    glm::vec3 s(normalize(cross(f,vU)));
		    glm::vec3 u(cross(s,f));

          _vE    = vE;
          _vD    = f;
          _vU    = u;
          _vR    = s;

          _mView[0][0] = -s.x;  // notice, this is opposite of s/vR;
		      _mView[1][0] = -s.y;
		      _mView[2][0] = -s.z;
		      _mView[3][0] = glm::dot(s,vE);

		      _mView[0][1] = u.x;
		      _mView[1][1] = u.y;
		      _mView[2][1] = u.z;
		      _mView[3][1] = -glm::dot(u,vE);

		      _mView[0][2] = -f.x;
		      _mView[1][2] = -f.y;
		      _mView[2][2] = -f.z;
		      _mView[3][2] = glm::dot(f,vE);

		      _mView[0][3] = 0;
		      _mView[1][3] = 0;
		      _mView[2][3] = 0;
		      _mView[3][3] = 1;
        
          _frustum = FrontFrustum;
        }

        bool isVisible(const glm::vec3 &vC,const float r) const
        {
        glm::vec3 vP = vC - _vE;
        float     aZ(glm::dot(vP,_vD));

          if ((aZ > (_zFar + r)) || (aZ < (_zNear - r)))
            return false;
          else
          {
          float aY(glm::dot(vP,_vU));
          float d(_sF.y * r);

            aZ *= _tang;

            if ((aY > (aZ + d)) || (aY < (-aZ - d)))
              return false;
            else
            {
            float aX(glm::dot(vP,_vR));

              aZ *= _aR;
              d  =  _sF.x * r;

              if ((aX > (aZ + d)) || (aX < (-aZ - d)))
                return false;
            }
          }

          return true;
        }  
     
        Camera(void) :  _mProj(),
                        _mView(),
                        _vE(),
                        _vD(),
                        _vU(),
                        _vR(),
                        _zNear(0.01f),
                        _zFar(1.0f),
                        _aR(1),
                        _sF(1),
                        _tang(0)
        {
        }
    };
  };
};

 //---------------------------------------------------------------------

