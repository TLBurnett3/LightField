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
// Model.h


#pragma once

//---------------------------------------------------------------------
// Includes

// System
#include <string>
#include <vector>
#include <ostream>

// 3rdPartyLibs
#include <glm/glm.hpp>
#include <filesystem>

// LightField
#include "RenderGL/Node.h"
#include "RenderGL/Bound.h"
#include "Core/Camera.h"
//---------------------------------------------------------------------



//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace RenderGL
  {
    class Model : public Bound
    {
      // Definitions
      private:
      protected:
        typedef   std::vector<Texture *>    TextureLst;
        typedef   std::vector<Mesh *>       MeshLst;
      public:
   
      // Members
      private:
      protected:
        std::string           _sName;
        std::filesystem::path _mPath;

        TextureLst     _textureLst;
        MeshLst        _meshLst;    
        Node           *_pRoot;

      public:


      // Methods
      private:
        void  walkNode(const struct aiNode  *pAINode);

        Texture           *createTexture   (const struct aiMaterial *pAIMaterial);
        Mesh              *createMesh      (const struct aiMesh *pAIMesh);
        Node              *createNode      (const struct aiNode *pAINode);

        void  walkTextures  (const struct aiScene *pAIScene);
        void  walkMeshes    (const struct aiScene *pAIScene);
        void  walkScene     (const struct aiScene *pAIScene,const glm::mat4 &mT,const uint32_t f);

        void  printVec3(std::ostream &s,std::string idt,const char *name,const glm::vec3 v);

        void  normalizeModel(void);
        void  moveToOrigin(void);

      protected:
      public:
        void   addTexture(Texture *pT)
        { _textureLst.push_back(pT); }

        void   addMesh(Mesh *pM)
        { _meshLst.push_back(pM); }

        void  setRootNode(Node *pN)
        { _pRoot = pN; }

        Node *root(void)
        { return _pRoot; }

        int   load(const std::filesystem::path &mFile,
                   const glm::mat4 &mT,
                   const uint32_t aFlags = 0,
                   const uint32_t flags = 0);

        void  print(std::ostream &s,bool detail = false);

        void  render(const Core::Camera *pCamera,const PhongShader *pShader,const glm::mat4 &mT);

        Model(void);
        ~Model();
    };
  };
};
//---------------------------------------------------------------------



