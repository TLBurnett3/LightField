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

// FrameBuffer.h
// Thomas Burnett

#pragma once

//---------------------------------------------------------------------
// Includes
// System
#include <vector> 

// 3rdPartyLibs
#include <opencv2/highgui/highgui.hpp>
#include <glm/glm.hpp>

// Lightfield
#include "RenderCPP/Vtx.h"
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Classes

namespace Lf
{
  namespace RenderCPP
  {
    class FrameBuffer
    {
      // Defines
      private:
      protected:
        typedef   std::vector<std::pair<cv::Mat,cv::Mat>>   FBLst;
      public:

      // Members
      private:
      protected:
        FBLst        _fbLst;
        glm::ivec2   _hS;

        cv::Mat      *_pImg;
        cv::Mat      *_pDth;

      public:   
        
      // Methods
      private:
      protected:
      public:

        inline void createRasterIndices(glm::ivec2 &vImin,glm::ivec2 &vImax,const Coords *pC0,const Coords *pC1,const Coords *pC2)
        {
        glm::vec2  vRmin  = glm::vec2( std::numeric_limits<float>::max());
        glm::vec2  vRmax  = glm::vec2(-std::numeric_limits<float>::max());

          vRmin  = glm::min(vRmin,pC0->_vRas);
          vRmax  = glm::max(vRmax,pC0->_vRas);

          vRmin  = glm::min(vRmin,pC1->_vRas);
          vRmax  = glm::max(vRmax,pC1->_vRas);

          vRmin  = glm::min(vRmin,pC2->_vRas);
          vRmax  = glm::max(vRmax,pC2->_vRas);

          vImin  = glm::ivec2(vRmin);
          vImax  = glm::ivec2(vRmax);

          vImin  = glm::clamp(vImin,glm::ivec2(0),_hS-1);
          vImax  = glm::clamp(vImax,glm::ivec2(0),_hS-1);
        }

        float   *dthPtr(const uint32_t i)
        { return (float *)_pDth->ptr() + i; }

        uint8_t   *imgPtr(const uint32_t i)
        { return _pImg->ptr() + (i * 4); }

        glm::ivec2 hogelSize(void)
        { return _hS; }

        void  setCurrentFrameBuffer(const size_t i)
        { 
          _pImg = &_fbLst[i].first;
          _pDth = &_fbLst[i].second;
        }

        void  getFrameBuffer(const size_t i,cv::Mat &img,cv::Mat &dth)
        {
          img = _fbLst[i].first;
          dth = _fbLst[i].second;
        }

        int   create(const glm::ivec2 &nH,const glm::ivec2 &hS);

        FrameBuffer(void);
       ~FrameBuffer();
    };
  };
};
//---------------------------------------------------------------------

