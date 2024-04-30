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

// ImgSet.h
// Thomas Burnett

#pragma once


//---------------------------------------------------------------------
// Includes
// System
#include <memory>
#include <queue>
#include <filesystem>

// 3rdPartyLibs
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <glm/glm.hpp>

// LightField
#include "Core/Export.h"
#include "Core/Thread.h"
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace Core
  {
    class ImgSet 
    {
      // Defines
      private:
      protected:

      public:
        typedef struct ImgData_Def
        {
          glm::ivec2  _idx;
          glm::vec2   _pos;
          glm::vec2   _uv;
          cv::Mat     _img;
        } ImgData;

        typedef std::vector<ImgData>  ISet;

      // Members
      private:
      protected:
        ISet        _imgSet;
        glm::ivec2  _nI;
        glm::ivec2  _iS;
        float       _aP;

      public:   

      // Methods
      private:
      protected:

      public:
        EXPORT float apperture(void)
        { return _aP; }

        EXPORT size_t size(void)
        { return _imgSet.size(); }

        EXPORT ImgData *get(const size_t i)
        { return &_imgSet[i]; }

        EXPORT int createPlenopticImage(cv::Mat &img,glm::ivec2 &nH,glm::ivec2 &hS);

        EXPORT int fitSize(const glm::ivec2 &mS);

        EXPORT int load(const std::filesystem::path &dPath); 
         
        EXPORT ImgSet(void);
        EXPORT ~ImgSet();
    };
  };
};
//---------------------------------------------------------------------

