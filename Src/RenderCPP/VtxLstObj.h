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
    class VtxLstObj : public VtxObj
    {
      // Defines
      private:
      protected:
        typedef std::vector<Vtx3> VtxLst;
      public:

      // Members
      private:
      protected:     
      public:   
        VtxLst  _vtxLst;

      // Methods
      private:
      protected:
      public:
        void reserveVertices(const uint32_t n)
        { _vtxLst.reserve(n); }

        void pushVtx3(const Vtx3 &v)
        { _vtxLst.push_back(v); }

        VtxLstObj(void);
        virtual ~VtxLstObj();
    };

    typedef std::shared_ptr<VtxLstObj> SpVtxLstObj;
  };
};
//---------------------------------------------------------------------

