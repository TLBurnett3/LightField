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

// Base.h
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
#include <Core/Export.h>
#include <Core/Thread.h>
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace Task
  {
    class Base : public Core::Thread
    {
      // Defines
      private:
      protected:
      public:
        typedef std::shared_ptr<std::pair<cv::Mat,glm::ivec2>>    SpImg;
        typedef std::queue<SpImg>                                 ImgQ;

      // Members
      private:
      protected:
        std::string               _tName;
        ImgQ                      _imgQ;
        std::mutex                _access;
        std::condition_variable   _workCondition;

      public:   

      // Methods
      private:
      protected:
        EXPORT void makeDir(const std::filesystem::path &dPath)
        {
          if (!dPath.empty() && !std::filesystem::exists(dPath))
            std::filesystem::create_directory(dPath);
        }      

      public:
        EXPORT std::string name(void)
        { return _tName; }

        EXPORT bool finished(void)
        {
        bool  f = false;
    
          {
          std::unique_lock<std::mutex> lock(_access);
            
            f = _imgQ.empty();
          }
          
          return f;
        }

        EXPORT virtual void  stop(void)
        { 
          Core::Thread::stop();
          _workCondition.notify_one();       
        }

        EXPORT void  queue(SpImg &spImg)
        { 
          {
          std::unique_lock<std::mutex> lock(_access);

            _imgQ.push(spImg); 
          }

          _workCondition.notify_one();
        }

        EXPORT virtual void process(cv::Mat &img,glm::ivec2 &idx) = 0;

        EXPORT virtual void exec(void);
  
        EXPORT Base(const char *pN);
        EXPORT ~Base();
    };
  };
};
//---------------------------------------------------------------------

