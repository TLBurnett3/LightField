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

// BtIntMapShader.h
// Thomas Burnett


#pragma once

//---------------------------------------------------------------------
// Includes


// 3rdPartyLibs


// Lightfield
#include "RenderCPP/BtBasicShader.h"
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
	  class BtIntMapShader : public BtBasicShader
	  {
	    // Defines
      private:
      protected:
        typedef std::vector<BtClipper>  ClipperLst;

      public:

      // Members
      private:
      protected: 
        glm::mat4         _mTVoli;

        glm::vec3         _vC;
        glm::vec3         _vN;

        glm::vec3         _frustumDirs[4];
      public:

       
      // Methods
      private:
      protected:   
 
        bool determineHogelPlaneIndices(const Vtx3 *pV0,const Vtx3 *pV1,const Vtx3 *pV2,
                                        glm::ivec2 *pVMin,glm::ivec2 *pVMax);

      public:
        EXPORT virtual void clear(void);

        EXPORT virtual void determine(void);

        EXPORT virtual void render(const Vtx3 *pV0,const Vtx3 *pV1,const Vtx3 *pV2);

        EXPORT BtIntMapShader(const char *pName);
        EXPORT virtual ~BtIntMapShader();
	  };
  };
};

//---------------------------------------------------------------------