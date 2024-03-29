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

// LightField
#include "Render/Def.h"
#include "Core/Export.h"
//---------------------------------------------------------------------

//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace Render
  {
	  class Shader
	  {
	    // Defines
      private:
      protected:
        typedef std::vector<std::filesystem::path>  ShaderSrcLst;
      public:

      // Members
      private:
      protected: 
        std::string       _sName;

        ShaderSrcLst      _vertexShaderLst;      
        ShaderSrcLst      _geometryShaderLst;
        ShaderSrcLst      _fragmentShaderLst;

        GLuint            _programShaderId;
        GLuint            _vertexShaderId;
        GLuint            _geometryShaderId;
        GLuint            _fragmentShaderId;

        GLint             _locMatMVP;
        GLint             _locMatMV;
        GLint             _locMatN;
        GLint             _locTexSampler;

        GLint             _locLightPosition;
        GLint             _locLightAmbient;
        GLint             _locLightDiffuse;
        GLint             _locLightSpecular;

        GLint             _locCameraPosition;

      public:

      // Methods
      private:
      protected:
        EXPORT int     addSourceFile(const std::filesystem::path &filePath,ShaderSrcLst &shaderSrcLst);
        int     loadShaderSource(const GLuint sId,ShaderSrcLst &shaderSrcLst);
        int     checkStatus(const char *pStr,const int check);
        int     createShader(GLuint sId,const int sType,ShaderSrcLst &shaderSrcLst);
        void    detachShaders(void);

      public:
        GLint programId(void)
        { return _programShaderId; }

        void use(void)
        { glUseProgram(_programShaderId); }

        void setName(const char *pName)
        { _sName = pName; }

        EXPORT int addVertexShader(const std::filesystem::path &fName)
        { return addSourceFile(fName,_vertexShaderLst); }

        EXPORT int addGeometryShader(const std::filesystem::path &fName)
        { return addSourceFile(fName,_geometryShaderLst); }

        EXPORT int addFragmentShader(const std::filesystem::path &fName)
        { return addSourceFile(fName,_fragmentShaderLst); }

        EXPORT void bindMVP(const glm::mat4 &mT) const
        { 
          glUniformMatrix4fv(_locMatMVP,1,false,glm::value_ptr(mT)); 
        }

        EXPORT void setTextureSampler(const int t) const
        { 
          glUniform1i(_locTexSampler,t);
        }

        EXPORT void bindMV(const glm::mat4 &mT) const
        { 
          glUniformMatrix4fv(_locMatMV,1,false,glm::value_ptr(mT)); 
        }

        EXPORT void bindN(const glm::mat3 &mT) const
        { 
          glUniformMatrix3fv(_locMatN,1,false,glm::value_ptr(mT)); 
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
 
        EXPORT Shader(void);
        EXPORT virtual ~Shader();
	  };
  };
};

//---------------------------------------------------------------------