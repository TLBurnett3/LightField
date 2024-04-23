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

// LightField
#include "RenderGL/Def.h"
#include "RenderGL/Bound.h"
#include "RenderGL/Texture.h"
#include "RenderGL/Object.h"
#include "Core/Camera.h"
#include "RenderGL/Shader.h"
//---------------------------------------------------------------------



//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace RenderGL
  {
    class Mesh : public Bound
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

        Texture             *_pTexture;
        Object              *_pObject;

        unsigned long       _numFaces;
        unsigned long       _numVertices;
        unsigned long       _numNormals;
        unsigned long       _numTexCoords;

      public:

      // Methods
      private:
 
      protected:
      public:
        void  setName(const std::string &name)
        { _mName = name; }

        void  setTexture(Texture *pM)
        { _pTexture = pM; }

        void  setRenderObject(Object *pRO)
        { _pObject = pRO; }      
      
        void  setNumFaces(const unsigned long nF)
        { _numFaces = nF; }

        void  setNumVertices(const unsigned long nV)
        { _numVertices = nV; }

        void  setNumNormals(const unsigned long nN)
        { _numNormals= nN; }

        void  setNumTexCoords(const unsigned long nTC)
        { _numTexCoords = nTC; }

        void print(std::ostream &s,std::string idt,bool detail = false);

        void render(const Core::Camera *pCamera,const Shader *pShader,const glm::mat4 &mT);

        Mesh(void);
        ~Mesh();
    };
  };
};
//---------------------------------------------------------------------



