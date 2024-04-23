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

// VtxIdxLstObj.h
// Thomas Burnett

#pragma once

//---------------------------------------------------------------------
// Includes
// System

// 3rdPartyLibs

// Lightfield
#include "RenderCPP/VtxLstObj.h"
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace RenderCPP
  {
    class VtxIdxLstObj : public VtxLstObj
    {
      // Defines
      private:
      protected:
      public:
        typedef std::vector<uint32_t> IdxLst;

      // Members
      private:
      protected:
      public:   
        IdxLst    _idxLst;

      // Methods
      private:
      protected:
      public:
        void reserveIndices(const uint32_t n)
        { _idxLst.reserve(n); }

        void pushIndex(const uint32_t idx)
        { _idxLst.push_back(idx); }

        void setIdxLst(const uint32_t *pI,const uint32_t n);

        virtual void render(Shader *pShader);        

        VtxIdxLstObj(void);
        virtual ~VtxIdxLstObj();
    };

    typedef std::shared_ptr<VtxIdxLstObj> SpVtxIdxLstObj;
  };
};
//---------------------------------------------------------------------

