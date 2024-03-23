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
// 
// SliceNDice.h
// Thomas Burnett

#pragma once


//---------------------------------------------------------------------
// Include
#include <filesystem>

// 3rdPartyLibs
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
    class	SliceNDice : public Task::Base
    {
      // Defines
      private:
      protected:
        typedef std::vector<cv::Mat>           CvMatLst;
        typedef std::vector<CvMatLst>          CvMatLstArray;

      public:

      // Members
      private:
      protected:
        CvMatLstArray _imgArray;

        cv::Mat       _proofImg;

        size_t        _yS;
        size_t        _yN;

        std::filesystem::path   _dPath;
        std::filesystem::path   _fName;

      public:


      // Methods
      private:
      protected:
      public:
        EXPORT size_t numSliceRows(void)
        { return _imgArray.size(); }

        EXPORT void   setSliceRange(size_t yS,size_t yN)
        { 
          _yS = yS; 
          _yN = yN; 
        }

        EXPORT void setPathFile(const std::filesystem::path &dPath,const char *pN)
        {   
          _dPath = dPath;
          _fName = pN; 
        }

        EXPORT virtual void process(cv::Mat &img,glm::ivec2 &idx);

        EXPORT void writeAVIs(void);

        EXPORT void init(const glm::ivec2 &nH,const glm::ivec2 &hS,const uint16_t mS);

      
        EXPORT SliceNDice(const char *pN) :  Task::Base(pN),
                                            _imgArray(),
                                            _proofImg(),
                                            _yS(0),
                                            _yN(0)
        {
        }

		    EXPORT virtual ~SliceNDice()
        {
        }
    };
  };
};
//---------------------------------------------------------------------


