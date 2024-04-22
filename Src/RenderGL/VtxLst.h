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

// VtxLst.h
// Thomas Burnett


#pragma once

//---------------------------------------------------------------------
// Includes
// System
#include <vector>
#include <float.h>

// 3rd party
#include <glm/ext.hpp>

// LightField
#include "RenderGL/Def.h"
#include "Core/Export.h"
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace RenderGL
  {
    class VtxLst
    {
      public:
        glm::vec3             _vMin;
        glm::vec3             _vMax;

      public:
        EXPORT void  reset(void)
        {
          _vMin = glm::vec3(FLT_MAX);
          _vMax = glm::vec3(-FLT_MAX);
        }

        EXPORT const glm::vec3 vMin(void) const
        { return _vMin; }

        EXPORT const glm::vec3 vMax(void) const
        { return _vMax; }

        EXPORT glm::vec3 dim(void)
        { return (_vMax - _vMin); }
      
        EXPORT void  bound(const glm::vec3 &v)
        {
          _vMin = glm::min(_vMin,v);
          _vMax = glm::max(_vMax,v);
        }

        EXPORT VtxLst() : _vMin(FLT_MAX),
                          _vMax(-FLT_MAX)
        {}
    };

    class VtxVNT
    {
      public:
        glm::vec3 _V;
        glm::vec3 _N;
        glm::vec2 _T;

      EXPORT VtxVNT(const glm::vec3 &v,const glm::vec3 &n,const glm::vec2 &t) : _V(v),_N(n),_T(t)
      {}

      EXPORT VtxVNT(void) : _V(),_N(),_T()
      {}
    };

    class VtxVNTLst : public VtxLst
    {
      public:
        std::vector<VtxVNT>   _vtxLst;

      public:
        EXPORT void  reserve(size_t n)
        { _vtxLst.reserve(n); }

        EXPORT void  multiply(const glm::mat4 &m)
        {
        size_t n = _vtxLst.size();

          for (size_t i = 0;i < n;i++)
            _vtxLst[i]._V = glm::vec3(m * glm::vec4(_vtxLst[i]._V,1));

          _vMin = glm::vec3(m * glm::vec4(_vMin,1));
          _vMax = glm::vec3(m * glm::vec4(_vMax,1));
        }

        EXPORT void  normalize(void)
        {
        glm::vec3 vS  = (_vMax - _vMin);
        glm::vec3 vT  = (_vMax + _vMin) * 0.5f;
        float     s   = 1.0f / (glm::max(glm::max(vS.x,vS.y),vS.z));
        glm::mat4 mT  = glm::scale(glm::mat4(),glm::vec3(s));

          mT = glm::translate(mT,-vT);

          multiply(mT);
        }

        EXPORT void  normalizeAndTransform(const glm::mat4 &m)
        {
        glm::vec3 vS  = (_vMax - _vMin);
        glm::vec3 vT  = (_vMax + _vMin) * 0.5f;
        float     s   = 1.0f / (glm::max(glm::max(vS.x,vS.y),vS.z));
        glm::mat4 mT  = glm::scale(glm::mat4(),glm::vec3(s));

          mT = glm::translate(mT,-vT);
          mT = m * mT;

          multiply(mT);
        }

        EXPORT void  add(const VtxVNT &vtx)
        { 
          bound(vtx._V);

          _vtxLst.push_back(vtx); 
        }

        EXPORT void  add(const glm::vec3 &v,const glm::vec3 &n,const glm::vec2 &t)
        { add(VtxVNT(v,n,t)); }

        EXPORT int createQuadXY(const glm::vec3 &vP,glm::vec2 &vS);
        EXPORT int createQuadXZ(const glm::vec3 &vP,glm::vec2 &vS);

        EXPORT VtxVNTLst(void) : VtxLst(),
                                _vtxLst()
        {
        }
    };


    class VtxVN
    {
      public:
        glm::vec3 _V;
        glm::vec3 _N;

      EXPORT VtxVN(const glm::vec3 &V,const glm::vec3 &N) : _V(V),_N(N)
      {}

      EXPORT VtxVN(void) : _V(),_N()
      {}
    };

    class VtxVNLst : public VtxLst
    {
      public:
        std::vector<VtxVN>   _vtxLst;

      public:
        EXPORT void  reserve(const uint16_t n)
        { _vtxLst.reserve(n); }

        EXPORT void  multiply(const glm::mat4 &m)
        {
        size_t n = _vtxLst.size();

          for (size_t i = 0;i < n;i++)
            _vtxLst[i]._V = glm::vec3(m * glm::vec4(_vtxLst[i]._V,1));

          _vMin = glm::vec3(m * glm::vec4(_vMin,1));
          _vMax = glm::vec3(m * glm::vec4(_vMax,1));
        }

        EXPORT void  normalize(void)
        {
        glm::vec3 vS  = (_vMax - _vMin);
        glm::vec3 vT  = (_vMax + _vMin) * 0.5f;
        float     s   = 1.0f / glm::max(glm::max(vS.x,vS.y),vS.z);
        glm::mat4 mT  = glm::scale(glm::mat4(),glm::vec3(s));

          mT = glm::translate(mT,-vT);

          multiply(mT);
        }

        EXPORT void  normalizeAndTransform(const glm::mat4 &m)
        {
        glm::vec3 vS  = (_vMax - _vMin);
        glm::vec3 vT  = (_vMax + _vMin) * 0.5f;
        float     s   = 1.0f / glm::max(glm::max(vS.x, vS.y), vS.z);
        glm::mat4 mT  = glm::scale(glm::mat4(),glm::vec3(s));

          mT = glm::translate(mT,-vT);
          mT = m * mT;

          multiply(mT);
        }

        EXPORT void  add(const VtxVN &vtx)
        { 
          bound(vtx._V);

          _vtxLst.push_back(vtx); 
        }

        EXPORT void  add(const glm::vec3 &V,const glm::vec3 &N)
        { add(VtxVN(V,N)); }

        EXPORT VtxVNLst(void) : VtxLst(),
                                _vtxLst()
        {
        }
    };



    class VtxVT
    {
      public:
        glm::vec3 _V;
        glm::vec2 _T;

      EXPORT VtxVT(const glm::vec3 &v,const glm::vec2 &t) : _V(v),_T(t)
      {}

      EXPORT VtxVT(void) : _V(),_T()
      {}
    };

    
    class VtxVTLst : public VtxLst
    {
      public:
        std::vector<VtxVT>    _vtxLst;

      public:
        EXPORT void  reset(void)
        {
          _vtxLst.clear();

          VtxLst::reset();
        }

        EXPORT void  reserve(const uint16_t n)
        { _vtxLst.reserve(n); }

        EXPORT void  multiply(const glm::mat4 &m)
        {
        size_t n = _vtxLst.size();

          for (size_t i = 0;i < n;i++)
            _vtxLst[i]._V = glm::vec3(m * glm::vec4(_vtxLst[i]._V,1));

          _vMin = glm::vec3(m * glm::vec4(_vMin,1));
          _vMax = glm::vec3(m * glm::vec4(_vMax,1));
        }

        EXPORT void  normalize(void)
        {
        glm::vec3 vS  = (_vMax - _vMin);
        glm::vec3 vT  = (_vMax + _vMin) * 0.5f;
        float     s   = 1.0f / glm::max(glm::max(vS.x,vS.y),vS.z);
        glm::mat4 mT  = glm::scale(glm::mat4(),glm::vec3(s));

          mT = glm::translate(mT,-vT);

          multiply(mT);
        }

        EXPORT void  normalizeAndTransform(const glm::mat4 &m)
        {
        glm::vec3 vS  = (_vMax - _vMin);
        glm::vec3 vT  = (_vMax + _vMin) * 0.5f;
        float     s   = 1.0f / glm::max(glm::max(vS.x,vS.y),vS.z);
        glm::mat4 mT  = glm::scale(glm::mat4(),glm::vec3(s));

          mT = glm::translate(mT,-vT);
          mT = m * mT;

          multiply(mT);
        }

        EXPORT void  add(const VtxVT &vtx)
        { 
          bound(vtx._V);

          _vtxLst.push_back(vtx); 
        }

        EXPORT void  add(const glm::vec3 &v,const glm::vec2 &t)
        { 
          bound(v);
       
          add(VtxVT(v,t));      
        }

        EXPORT VtxVTLst(void) : VtxLst(),
                         _vtxLst()
        {
        }
    };


    class VtxV
    {
      public:
        glm::vec3 _V;

      EXPORT VtxV(const glm::vec3 &v) : _V(v)
      {}

      EXPORT VtxV(void) : _V()
      {}
    };


    class VtxVLst : public VtxLst
    {
      public:
        std::vector<VtxV>     _vtxLst;

      public:
        EXPORT void  reserve(const uint16_t n)
        { _vtxLst.reserve(n); }

        EXPORT void  multiply(const glm::mat4 &m)
        {
        size_t n = _vtxLst.size();

          for (size_t i = 0;i < n;i++)
            _vtxLst[i]._V = glm::vec3(m * glm::vec4(_vtxLst[i]._V,1));

          _vMin = glm::vec3(m * glm::vec4(_vMin,1));
          _vMax = glm::vec3(m * glm::vec4(_vMax,1));
        }

        EXPORT void  normalize(void)
        {
        glm::vec3 vS  = (_vMax - _vMin);
        glm::vec3 vT  = (_vMax + _vMin) * 0.5f;
        float     s   = 1.0f / glm::max(glm::max(vS.x,vS.y),vS.z);
        glm::mat4 mT  = glm::scale(glm::mat4(),glm::vec3(s));

          mT = glm::translate(mT,-vT);

          multiply(mT);
        }

        EXPORT void  normalizeAndTransform(const glm::mat4 &m)
        {
        glm::vec3 vS  = (_vMax - _vMin);
        glm::vec3 vT  = (_vMax + _vMin) * 0.5f;
        float     s   = 1.0f / glm::max(glm::max(vS.x,vS.y),vS.z);
        glm::mat4 mT  = glm::scale(glm::mat4(),glm::vec3(s));

          mT = glm::translate(mT,-vT);
          mT = m * mT;

          multiply(mT);
        }

        EXPORT void  add(const VtxV &vtx)
        { 
          bound(vtx._V);

          _vtxLst.push_back(vtx); 
        }

        EXPORT void  add(const glm::vec3 &v)
        { add(VtxV(v)); }

        EXPORT VtxVLst(void) : VtxLst(),
                               _vtxLst()
        {
        }
    };
    //---------------------------------------------------------------------


    //---------------------------------------------------------------------   
    typedef std::vector<GLZ>      IdxLst; 
    //---------------------------------------------------------------------
  };
};
//---------------------------------------------------------------------


