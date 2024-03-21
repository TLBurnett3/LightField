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


// WriteAvi.h
// Thomas Burnett

#pragma once


//---------------------------------------------------------------------
// Include
#include <filesystem>
#include <iostream>

// 3rd Party Libs
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <glm/glm.hpp>

// Hogel Tasks
#include "Tasks/Base.h"
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace Task
  {
    class	WriteAvi : public Task::Base
    {
      // Defines
      private:
      protected:
      public:

      // Members
      private:
      protected:
        cv::VideoWriter         _videoWriter;

        std::filesystem::path   _dPath;
        std::filesystem::path   _fName;

      public:

      // Methods
      private:
      protected:
        bool  isOpen(void)
        { return _videoWriter.isOpened(); } 
      
        void close(void)
        {
          if (_videoWriter.isOpened())
            _videoWriter.release();
        }

        int open(cv::Mat &img,const glm::ivec2 &idx);

      public:
        EXPORT void setPathFile(const std::filesystem::path &dPath,const char *pN)
        {   
          makeDir(dPath);

          _dPath = dPath;
          _fName = pN; 
        }

        EXPORT virtual void process(cv::Mat &img,glm::ivec2 &idx);

        EXPORT WriteAvi(const char *pN) : Task::Base(pN),
                                          _videoWriter(),                                                                
                                          _dPath(),
                                          _fName()                                                   
        {}

		    EXPORT virtual ~WriteAvi()
        {
          close();
        }
    };
  };
};
//---------------------------------------------------------------------


