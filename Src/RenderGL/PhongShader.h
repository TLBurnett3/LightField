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

// PhongShader.h
// Thomas Burnett


#pragma once

//---------------------------------------------------------------------
// Includes

// 3rdPartyLibs

// LightField
#include "RenderGL/BasicShader.h"
//---------------------------------------------------------------------

//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace RenderGL
  {
	  class PhongShader : public BasicShader
	  {
	    // Defines
      private:
      protected:
        typedef std::vector<std::filesystem::path>  ShaderSrcLst;
      public:

      // Members
      private:
      protected: 
        float             _nS;

        GLint             _locMatMV;
        GLint             _locMatN;

        GLint             _locLightPosition;
        GLint             _locLightAmbient;
        GLint             _locLightDiffuse;
        GLint             _locLightSpecular;

        GLint             _locCameraPosition;

      public:

      // Methods
      private:
      protected:
      public:
        EXPORT void bindNormalScale(const float s)
        { _nS = (s >= 1.0f) ? 1.0f : -1.0f; }

        EXPORT void bindMV(const glm::mat4 &mT) const
        { 
        glm::mat4   mMVs  = glm::scale(mT,glm::vec3(_nS,_nS,_nS));
        glm::mat3   mN    = glm::inverseTranspose(glm::mat3(mMVs));

          glUniformMatrix4fv(_locMatMV,1,false,glm::value_ptr(mT)); 
          glUniformMatrix3fv(_locMatN,1, false,glm::value_ptr(mN)); 
        }

        EXPORT void bindLightAmbient(const glm::vec4 &cA) const
        { 
          glUniform4fv(_locLightAmbient,1,glm::value_ptr(cA)); 
        }

        EXPORT void bindLightDiffuse(const glm::vec4 &cD) const
        { 
          glUniform4fv(_locLightDiffuse,1,glm::value_ptr(cD)); 
        }

        EXPORT void bindLightSpecular(const glm::vec4 &cS) const
        { 
          glUniform4fv(_locLightSpecular,1,glm::value_ptr(cS)); 
        }

        EXPORT void bindLightPosition(const glm::vec3 &vP) const
        { 
          glUniform3fv(_locLightPosition,1,glm::value_ptr(vP)); 
        }

        EXPORT void bindCameraPosition(const glm::vec3 &vP) const
        { 
          glUniform3fv(_locCameraPosition,1,glm::value_ptr(vP)); 
        }

        EXPORT virtual int compile(void);
 
        EXPORT PhongShader(const char *pName);
        EXPORT virtual ~PhongShader();
	  };
  };
};

//---------------------------------------------------------------------