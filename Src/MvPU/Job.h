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

// Thomas Burnett
// Job.h

#pragma once


//---------------------------------------------------------------------
// Includes
// System


// 3rdPartyLibs


// Lightfield
#include "Core/Job.h"

//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace MvPU
  {
    class Job : public Core::Job
    {
      // Defines
      private:
      protected:
      public:
        enum BtRenderTypes
        {
          BowTie  = Core::Job::RenderTypes::Oblique + 1
        };

        enum BtAlgorithmTypes
        {
          Basic = Core::Job::AlgorithmTypes::Default + 1,
          IntMap
        };

      // Members
      private:
      protected:
      public:   

      // Methods
      private:
      protected:
      public:
        EXPORT virtual int Job::parseDocument(Core::JSon::Value &doc);

        EXPORT Job(void);
        EXPORT virtual ~Job();
    };

    typedef std::shared_ptr<Job>    SpJob;
  };
};
 //---------------------------------------------------------------------

