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
#include "Core/Camera.h"

//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace HogelDef
  {
    class Camera : public Core::Camera
    {
    // Defines
      private:
      protected:
      public:

      // Members
      private:
      protected:
      public:

      // Methods
      private:
      protected:
 
      public:
        void setBowTiePerspective(const float fov,const float aR)
        {
        float tanHalfFovy = tan(glm::radians(fov) / 2.0f);

	        _mProj = glm::mat4(0);
	        _mProj[0][0] = -1.0f / tanHalfFovy;
	        _mProj[1][1] = -1.0f / tanHalfFovy;
	        _mProj[2][3] = -1.0f;
	        _mProj[3][2] = -1.0f;

          _aR    = aR;
        }
 
        void setBackFrustum(const glm::vec3 &vE,const glm::vec3 &vD,const glm::vec3 &vU)
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
        }
      
        void setFrontFrustum(const glm::vec3 &vE,const glm::vec3 &vD,const glm::vec3 &vU)
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
        }

        Camera(void) : Core::Camera()
        {
        }
    };
  };
};

 //---------------------------------------------------------------------

