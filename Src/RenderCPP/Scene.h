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

// Scene.h
// Thomas Burnett


#pragma once

//---------------------------------------------------------------------
// Includes
// System
#include <assert.h>
#include <vector>

// 3rdPartyLibs

// Lightfield
#include "RenderCPP/Model.h"
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace RenderCPP
  {
    class Scene
    {
      // Defines
      private:
      protected:
        typedef   std::vector<Model *> ModelLst;
      public:

      // Members
      private:
      protected:
        ModelLst   _modelLst;
      public:   


      // Methods
      private:
      protected:
      public:
  
        void  clear(void);

        void  render(const HogelDef::Camera &camera,Shader *pShader,const glm::mat4 &mT);

        int   load(const std::filesystem::path &mPath,const glm::mat4 &mT);

        int   init(const std::filesystem::path &cPath);

        Scene(void);
       ~Scene();
    };
  };
};

//---------------------------------------------------------------------

