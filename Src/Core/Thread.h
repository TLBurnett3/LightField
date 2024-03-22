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

// Thread.h
// Thomas Burnett

#pragma once


//---------------------------------------------------------------------
// Includes
// System
#include <atomic>
#include <thread>
#include <assert.h>

// 3rdPartyLibs

// LightField
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace Core
  {
    class	Thread
    {
      // Defines
      private:
      protected:
      public:

      // Members
      private:
      protected:
        std::thread       _thread;
        std::atomic<bool> _run; 
      public:

      // Methods
      private:
      protected:
        void  sleep(const double seconds)
        {
          if (_run)
          {
          long long t = (long long)(seconds * 1000.0);

            std::this_thread::sleep_for(std::chrono::milliseconds(t));
          }
        }

      public:
        EXPORT bool  isRunning(void)
        { return _run; }

        EXPORT virtual void exec(void) = 0;

        EXPORT virtual void start(void)
        {
          assert(!_run); // thread is already started.
          _run    = true;
          _thread = std::thread(&Thread::exec,this);
        }

        EXPORT virtual void  stop(void)
        { 
          _run = false; 
        }

        // do not call this from within in this thread.
        // it should only be called by the parent thread
        EXPORT virtual void  join(void)
        { 
          _thread.join();
        }
   
        EXPORT Thread(void) : _thread(),
                              _run(false)
        {}
    
		    EXPORT virtual ~Thread()
        {}
    };
  };
};

//---------------------------------------------------------------------
