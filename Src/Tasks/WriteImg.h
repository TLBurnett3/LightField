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

// WriteImg.h
// Thomas Burnett

#pragma once

//---------------------------------------------------------------------
// Include

// 3rd Party Libs
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <filesystem>
#include <glm/glm.hpp>

// LightField
#include "Tasks/Base.h"
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace Task
  {
    class	WriteImg : public Task::Base
    {
      // Defines
      private:
      protected:
      public:

      // Members
      private:
      protected:
        std::filesystem::path _dPath;
        std::string           _fName;
        std::string           _ext;

        float                 _zNear;
        float                 _zFar;

      public:

      // Methods
      private:
      protected:
        uint16_t toUShort(float v)
        {
        float z = (v * 2.0f) - 1.0f;
        float c = (2.0f * _zNear * _zFar) / (_zFar + _zNear - z * (_zFar - _zNear));

          c = glm::clamp(1.0f - (c / _zFar),0.0f,1.0f);
      
          return (uint16_t)(c * (float)0xffff);
        }

      public:     
        EXPORT void setZNear(const float zN)
        { _zNear = zN; }

        EXPORT void setZFar(const float zF)
        { _zFar  = zF; }


        EXPORT virtual void process(cv::Mat &img,glm::ivec2 &idx);

        void setPathFile(const std::filesystem::path &dPath,const char *pName,const char *pExt)
        {
          makeDir(dPath);

          _dPath = dPath,
          _fName = pName;
          _ext   = pExt;
        }

        WriteImg(const char *pN) :  Task::Base(pN),
                                    _fName(),
                                    _ext("png"),
                                    _zNear(0.1f),
                                    _zFar(1.0f)
        {}
    
		    virtual ~WriteImg()
        {}
    };
  };
};
//---------------------------------------------------------------------


