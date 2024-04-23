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
// Mesh.h

#pragma once

//---------------------------------------------------------------------
// Includes

// System
#include <string>
#include <ostream>

// 3rdPartyLibs
#include <glm/glm.hpp>

// Lightfield
#include "RenderCPP/VtxObj.h"
#include "RenderCPP/TxtObj.h"
#include "HogelDef/Camera.h"
#include "RenderCPP/Shader.h"
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace RenderCPP
  {
    class Mesh 
    {
      friend class Model;

      // Definitions
      private:
      protected:
      public:   

      // Members
      private:
      protected:
        std::string         _mName;

        TxtObj              *_pTxtObj;
        VtxObj              *_pVtxObj;

      public:

      // Methods
      private:
 
      protected:
      public:
        void  setName(const std::string &name)
        { _mName = name; }

        void  setTxtObj(TxtObj *pM)
        { _pTxtObj = pM; }

        void  setVtxObj(VtxObj *pRO)
        { _pVtxObj = pRO; }      
      
        void print(std::ostream &s,std::string idt,bool detail = false);

        void render(const HogelDef::Camera &camera,Shader *pShader,const glm::mat4 &mT);

        Mesh(void);
        ~Mesh();
    };
  };
};
//---------------------------------------------------------------------



