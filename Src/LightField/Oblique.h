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

// Oblique.h
// Thomas Burnett

#pragma once


//---------------------------------------------------------------------
// Includes
// System


// 3rdPartyLibs


// LightField
#include "Executor.h"
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Classes
namespace Lf
{
  class Oblique : public Executor
  {
    // Defines
    private:
    protected:
    public:

    // Members
    private:
    protected:
    public:   

    // Methods
    private:
      void      renderOblique(Render::Camera &camera,const glm::vec2 &rA);

      void      renderObliquePlane       (void);
      uint32_t  renderObliqueSet         (void);
      void      renderObliqueAndSlice    (void);

      virtual void fetchAndQueue(glm::ivec2 idx);
      virtual void createTasks  (void);

    public:
      int   exec(void);

      int   init(Core::SpJob &spJob);

      Oblique(void);
      virtual ~Oblique();
  };
};
//---------------------------------------------------------------------

