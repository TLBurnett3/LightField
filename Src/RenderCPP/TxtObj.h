//----COPYRIGHT NOTICE--------------------------------------------------
//
//	Copyright (C) FoVI3D
//
//----COPYRIGHT NOTICE--------------------------------------------------

// TxtObj.h
// Thomas Burnett

#pragma once

//---------------------------------------------------------------------
// Includes
// System
#include <memory>
#include <cstring>

// 3rdPartyLibs
#include <glm/glm.hpp>

// Lightfield

//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace RenderCPP
  {
    class TxtObj
    {
      // Defines
      private:
      protected:
      public:

      // Members
      private:
      protected:
      public:   
        glm::ivec2 _dim;
        uint16_t   _bpp;

        glm::vec4  _cA;
        glm::vec4  _cD;
        glm::vec4  _cS;
        float      _s;

        uint8_t    *_pI;

      // Methods
      private:
      protected:
      public:
        uint8_t *image(void)
        { return _pI; }

        void create(const glm::ivec2 &dim,const uint16_t bpp,const uint8_t *pI)
        {
        uint32_t n = dim.x * dim.y * bpp;

          _dim = dim;
          _bpp = bpp;

          _pI = new uint8_t[n];
          memcpy(_pI,pI,n);
        }

        void setProperties(const glm::vec4 &cA,const glm::vec4 &cD,const glm::vec4 &cS,const float s)
        {
          _cA = cA;
          _cD = cD;
          _cS = cS;
          _s  = s;
        }

        inline glm::uvec4 color(const glm::vec2 &vUV)
        {
        glm::vec2  dim(_dim - 1);
        glm::vec2  ui(vUV * dim);
        uint8_t   *pT = 0;

          ui = glm::mod(ui,dim);
       
          pT = _pI + ((uint32_t)ui.y * _dim.x * _bpp) + ((uint32_t)ui.x * _bpp);

          return glm::uvec4(*(pT + 0),*(pT + 1),*(pT + 2),255);
        }
  
        TxtObj(void) : _dim(0),
                       _bpp(0),
                       _cA(1),
                       _cD(0),
                       _cS(0),
                       _s(0),
                       _pI(0)
        {}

        virtual ~TxtObj()
        {
          delete _pI;
        }
    };

    typedef std::shared_ptr<TxtObj> SpTxtObj;
  };
};
//---------------------------------------------------------------------

