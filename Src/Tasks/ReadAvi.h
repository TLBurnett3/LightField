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

// ReadAvi.h
// Thomas Burnett


#pragma once


//---------------------------------------------------------------------
// Include
// System
#include <filesystem>

// 3rd Party Libs
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// Lightfield
#include "Core/Export.h"
#include "Core/Thread.h"
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace Task
  {
    class	ReadAvi : public Core::Thread
    {
      // Defines
      private:
      protected:
      public:

      // Members
      private:
      protected:
        std::string             _tName;
        cv::VideoCapture        _videoReader;

      public:

      // Methods
      private:
      protected:
      public:
        EXPORT bool  isOpen(void)
        { return _videoReader.isOpened(); }

        EXPORT int open(const std::filesystem::path &fPath);

        EXPORT void close(void)
        {
          if (_videoReader.isOpened())
            _videoReader.release();
        }

        EXPORT virtual void operator()();

        EXPORT ReadAvi(const char *pN) :      Core::Thread(),
                                             _tName(pN),
                                             _videoReader()
        {
        }

		    EXPORT virtual ~ReadAvi()
        {
          if (_videoReader.isOpened())
            _videoReader.release();
        }
    };
  };
};
//---------------------------------------------------------------------


