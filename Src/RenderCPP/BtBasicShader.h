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

// BtBasicShader.h
// Thomas Burnett


#pragma once

//---------------------------------------------------------------------
// Includes


// 3rdPartyLibs


// Lightfield
#include "RenderCPP/BtShader.h"
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
	  class BtBasicShader : public BtShader
	  {
	    // Defines
      private:
      protected:
        typedef std::vector<BtClipper>        ClipperLst;
      public:

      // Members
      private:
      protected: 
        ClipperLst      _clipperLst;
      public:

      // Methods
      private:
      protected:   
        virtual void render(const Vtx3 *pV0,const Vtx3 *pV1,const Vtx3 *pV2,
                            const glm::ivec2 &iMin,const glm::ivec2 &iMax,
                            const float c);
      public:
        EXPORT void  bindHogelPlane(HogelDef::Plane *pHp)
        { 
          BtShader::bindHogelPlane(pHp);

          _clipperLst.resize(_pHogelPlane->maxHogels());
        }

        EXPORT virtual void render(const Vtx3 *pV0,const Vtx3 *pV1,const Vtx3 *pV2);

        EXPORT BtBasicShader(const char *pName);
        EXPORT virtual ~BtBasicShader();
	  };
  };
};

//---------------------------------------------------------------------