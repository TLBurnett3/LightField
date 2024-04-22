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
// Node.h

#pragma once

//---------------------------------------------------------------------
// Includes
#include <string>
#include <vector>
#include <ostream>

// LightField
#include "RenderGL/Mesh.h"
#include "RenderGL/Bound.h"
#include "RenderGL/Camera.h"
//---------------------------------------------------------------------



//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace RenderGL
  {
    class Node : public Bound
    {
      friend class Model;

      // Definitions
      private:
      protected:
        typedef   std::vector<Mesh *>      MeshLst;
        typedef   std::vector<Node *>      NodeList;
      public:
    

      // Members
      private:
      protected:
        std::string   _sName;

        glm::mat4     _mT;  // transform matrix

        MeshLst       _meshLst;
        NodeList      _nodeLst;
      public:


      // Methods
      private:
      protected:
        void printMatrix(std::ostream &s,std::string idt,const char *str,const glm::mat4 &m);

      public:
        const glm::mat4 &transform(void) const
        { return _mT; }

        void  setName(const char *name)
        { _sName = name; }

        void  setTransformMatrix(glm::mat4 mT)
        { _mT  = mT; }

        void  addNode(Node *pN)
        { _nodeLst.push_back(pN); }

        void  addMesh(Mesh *pM)
        { 
          bound(pM->vMin(),pM->vMax());
          _meshLst.push_back(pM); 
        }

  //      void cullFrustum(const glm::mat4 &mView,const Control &control);

        void  print(std::ostream &s,std::string idt);

        void  render(const Camera &camera,const Shader *pShader,const glm::mat4 &mT);

        Node(void);
        ~Node();
    };
  };
};
//---------------------------------------------------------------------



