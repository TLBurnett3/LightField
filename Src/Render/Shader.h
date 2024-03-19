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

        GLint             _locMatMatProp;
        GLint             _locMatLightProp;
        GLint             _locMatLightSwitch;

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

        EXPORT int   addVertexShader(const std::filesystem::path &fName)
        { return addSourceFile(fName,_vertexShaderLst); }

        EXPORT int addGeometryShader(const std::filesystem::path &fName)
        { return addSourceFile(fName,_geometryShaderLst); }

        EXPORT int addFragmentShader(const std::filesystem::path &fName)
        { return addSourceFile(fName,_fragmentShaderLst); }

        EXPORT void bindMVP(const glm::mat4 &mT) const
        { 
          if (_locMatMVP != -1)
            glUniformMatrix4fv(_locMatMVP,1,false,glm::value_ptr(mT)); 
        }

        EXPORT void bindMV(const glm::mat4 &mT) const
        { 
          if (_locMatMV != -1)
            glUniformMatrix4fv(_locMatMV,1,false,glm::value_ptr(mT)); 
        }

        EXPORT void bindN(const glm::mat3 &mT) const
        { 
          if (_locMatN != -1)
            glUniformMatrix3fv(_locMatN,1,false,glm::value_ptr(mT)); 
        }
  
        EXPORT void bindMaterial(const glm::mat4 &mM) const
        { 
          if (_locMatMatProp != -1)
            glUniformMatrix4fv(_locMatMatProp,1,false,glm::value_ptr(mM)); 
        }

        EXPORT void bindLight(const glm::mat4 &mL,int id,int frustum) const
        {
        std::string switchName = std::string("L[") + std::to_string(id) + "]._switch";
        std::string propName = std::string("L[") + std::to_string(id) + "]._mL";
        std::string frustName = std::string("frustum");

          //first enable switch for this light in the shader
          glUniform1i(glGetUniformLocation(_programShaderId, switchName.c_str()), true);

          //second bind the light properties matrix for the shader
          glUniformMatrix4fv(glGetUniformLocation(_programShaderId, propName.c_str()), 1, false, glm::value_ptr(mL));

          //lastly set whether rendering front or back frustums
          glUniform1i(glGetUniformLocation(_programShaderId, frustName.c_str()), frustum);
        }

        EXPORT virtual int compile(void);
 
        EXPORT Shader(void);
        EXPORT virtual ~Shader();
	  };
  };
};

//---------------------------------------------------------------------