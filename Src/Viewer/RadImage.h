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

// RadImage.h
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
  namespace Viewer
  {
    class RadImage : public Core::Thread
    {
      // Defines
      private:
      protected:
        enum 
        {
          MaxNumViews      = 256,
          MaxViewSize      = 256,
        };

        typedef std::vector<cv::Mat>  MatArray;

      public:

      // Members
      private:
      protected:
        MatArray                  _matArray;
        std::filesystem::path     _dPath;

        glm::ivec2    _nH;
        glm::ivec2    _hS;
        glm::ivec2    _nV;
        glm::ivec2    _vS;

        float         _aR;
        glm::vec2     _hInc;
      public:   

      // Methods
      private:
      protected:  
      public:
        int examine(const std::filesystem::path &dPath); 

        int init(void);
        virtual void exec(void);
  
        RadImage(void);
        ~RadImage();
    };
  };
};
//---------------------------------------------------------------------

