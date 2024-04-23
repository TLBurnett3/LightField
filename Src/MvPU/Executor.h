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

// Executor.h
// Thomas Burnett

#pragma once


//---------------------------------------------------------------------
// Includes
// System
#include <filesystem>
#include <vector>

// 3rdPartyLibs

// Lightfield
#include "MvPU/Job.h"
#include "Core/Timer.h"
#include "RenderCPP/Scene.h"
#include "HogelDef/Plane.h"
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Classes
namespace MvPU
{
  class Executor
  {
    // Defines
    private:
    protected:
    public:

    // Members
    private:
    protected:

      Lf::MvPU::SpJob            _spJob;
      std::string                _name;

      Lf::RenderCPP::Scene       *_pScene;
      Lf::HogelDef::Plane        *_pHogelPlane;
      Lf::RenderCPP::FrameBuffer *_pFrameBuffer;

      double                     _rSec;
      double                     _rFps;

    public:   

    // Methods
    private:
    protected:

      int createFrameBuffer (void);
      int createHogelPlane  (void);
      int loadModels        (std::filesystem::path &cPath);

    public:

      virtual int   exec    (void) = 0;

      virtual int   process (void);

      virtual void  record  (void);

      virtual int   init    (Lf::MvPU::SpJob &spJob);
      virtual void  destroy (void);

      Executor(void);
      virtual ~Executor();
  };
};
//---------------------------------------------------------------------

