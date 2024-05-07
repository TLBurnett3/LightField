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

// Sar.h
// Thomas Burnett

#pragma once


//---------------------------------------------------------------------
// Includes
// System

// 3rdPartyLibs

// LightField
#include "RenderGL/Texture.h"
#include "RenderGL/VtxArrayObj.h"
#include "RenderGL/BasicShader.h"

//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace Aperture
  {
    class Sar
    {
      // Defines
      private:
      protected:
        typedef std::vector<glm::mat4>  MatrixLst;

      public:

      // Members
      private:
      protected:
        std::string     _sName;

        glm::ivec2      _iS;
        glm::ivec2      _nI;
        glm::ivec2      _wS;
        glm::ivec2      _iIdx;
        float           _aP;

        const MatrixLst *_pMHLst;
      public:   

      // Methods
      private:
      protected:
      public:

        std::string name(void)
        { return _sName; }

        virtual void setWindowSize(const glm::ivec2 &wS)
        { _wS = wS; }

        virtual void bindAperture(float a)
        { _aP = a; }

        virtual void bindSubImageIdx(const glm::ivec2 &iIdx)
        { _iIdx = iIdx; }

        virtual void bindSubImageSize(const glm::ivec2 &iS)
        { _iS = iS; }

        virtual void bindNumImages(const glm::ivec2 &nI)
        { _nI = nI; }

        virtual void bindHomographies(const MatrixLst *pHMLst)
        { _pMHLst = pHMLst; }

        virtual void render(const glm::mat4 &mP,const glm::mat4 &mV,
                            RenderGL::BasicShader *pS,RenderGL::Texture &mcTex,RenderGL::VtxArrayObj &vao) = 0;
  
        Sar(const char *pName);
        virtual ~Sar();
    };
  };
};
//---------------------------------------------------------------------

