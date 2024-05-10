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

// Image.h
// Thomas Burnett

#pragma once


//---------------------------------------------------------------------
// Includes
// System
#include <memory>
#include <filesystem>
#include <iostream>

// 3rdPartyLibs
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <glm/glm.hpp>

// LightField
#include "Core/Export.h"
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace RadImg
  {
    typedef struct Coords_Def
    {
      glm::vec2 _pos;
      glm::vec2 _uv;
    } Coords;

    typedef std::vector<Coords> CoordLst;

    class Image 
    {
      // Defines
      private:
      protected:
      public:
  
      // Members
      private:
      protected:
        cv::Mat     _img;

        glm::ivec2  _nI;
        glm::ivec2  _iS;

        CoordLst    _coordLst;

      public:   

      // Methods
      private:
      protected:

      public:
        EXPORT cv::Mat getImage(void)
        { return _img; }

        EXPORT void  *getImageData(void)
        { return _img.data; }

        EXPORT glm::ivec2 numImages(void)
        { return _nI; }

        EXPORT glm::ivec2 sizeSubImages(void)
        { return _iS; }

        EXPORT void  write(const std::filesystem::path &fPath)
        { cv::imwrite(fPath.string(),_img); }

        EXPORT void  write(const char *pFPath)
        { write(std::filesystem::path(pFPath)); }
         
        EXPORT Image(void);
        EXPORT virtual ~Image();
    };

    typedef std::shared_ptr<Image>   SpImage;
  };
};
//---------------------------------------------------------------------

