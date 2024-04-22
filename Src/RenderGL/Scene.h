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

// 3rdPartyLibs
#include <filesystem>

// LightField
#include "RenderGL/Def.h"
#include "Core/Export.h"
#include "RenderGL/Model.h"
#include "RenderGL/Camera.h"
#include "RenderGL/Shader.h"
//---------------------------------------------------------------------



//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace RenderGL
  {
 	  class Scene 	
    {
	    // Defines
      private:
      protected:
        typedef   std::vector<Model *> ModelLst;

      public:
        enum ModelIndexDef
        {
          ImagePlaneModel = -1,
        };

        enum FrustumDef
        {
          FrontFrustum  = -1,
          NormalFrustum = 1,
          BackFrustum   = 1,
        };

      // Members
      private:
      protected:
        ModelLst             _modelLst;
        Model               *_imagePlaneModel;

        glm::vec3 _max;
        glm::vec3 _min;
        glm::vec3 _cen;

      public:

      // Methods
      private:
      protected:
      public: 
        const glm::vec3 vMax(void)
        { return _max; }

        const glm::vec3 vMin(void)
        { return _min; }

        const glm::vec3 vCen(void)
        { return _cen; }

        Model * model(const int i) const
        {
          if (i == ImagePlaneModel)
          {
            assert(_imagePlaneModel);
            return _imagePlaneModel;
          }

          return _modelLst[i];
        }

        EXPORT void print(std::ostream &s);
        EXPORT void render(const Camera &camera,const Shader *pShader,const glm::mat4 &mT);

        EXPORT int  init(const std::filesystem::path &cPath);
        EXPORT int  load(const std::filesystem::path &mPath,const glm::mat4 &mT);

   //     void  createImagePlane(const glm::mat4 &mT,const glm::vec3 &hW);

        EXPORT Scene(void);
        EXPORT virtual ~Scene();
    };
  };
};
//---------------------------------------------------------------------
