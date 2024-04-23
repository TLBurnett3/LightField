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

// VtxMeshObj.h
// Thomas Burnett

#pragma once

//---------------------------------------------------------------------
// Includes
// System
#include <vector>

// 3rdPartyLibs

// Lightfield
#include "RenderCPP/VtxObj.h"
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace RenderCPP
  {
    class VtxMeshObj : public VtxObj
    {
      // Defines
      private:
      protected:      
      public:
        typedef std::vector<float> HeightMap;

      // Members
      private:
      protected:
        float     _maxDimension;
        float     _heightOffset;
        glm::vec2 _minMaxHeight;

      public:   
        HeightMap   _hMap;
        glm::ivec2 _dim;

      // Methods
      private:
      protected:
      public:

        float maxDimension()
        { return _maxDimension; }

        float heightOffset()
        { return _heightOffset; }

        glm::vec2 minMaxHeight()
        { return _minMaxHeight; }

        void setHeightMap(const float *pI,const glm::ivec2 &dim);
  
        VtxMeshObj(void);
        virtual ~VtxMeshObj();
    };

    typedef std::shared_ptr<VtxMeshObj> SpVtxMeshObj;
  };
};

//---------------------------------------------------------------------

