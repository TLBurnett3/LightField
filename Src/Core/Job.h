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
#include <string>
#include <vector>
#include <filesystem>

// 3rdPartyLibs
#include "glm/glm.hpp"
#include "glm/ext.hpp"

// LightField
#include "Core/JSon.h"
//#include "Light.h"

//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace Core
  {
    class ModelDef
    {
    // Defines
      private:
      protected:
      public:

        // Members
      private:
      protected:
      public:
        std::filesystem::path   _mPath;
        glm::mat4               _mT;

      // Methods
      private:
      protected:
      public:
        ModelDef(void) : _mPath(),
                         _mT(1)
        {}
    };

    class Job
    {
      // Defines
      private:
        enum RequiredDef
        {
          Required    = -1,
          NotRequired = 0,
        };
      protected:
        typedef std::vector<ModelDef>   ModelDefs;

      public:
        enum  TaskDefs
        {
          ProofImage = 0,
          WriteAVI,
          WritePNG,
          WriteDemo,
          HogelView,
          DisplayDepthBuffer,
          WriteDepth,
          ProofDepth,
          TaskDefsNum,
        };

        enum RenderTypes
        {
          Unknown   = -1,
          DoubleFrustum,
          ObliqueSliceDice,
          Slice,
          MVP,
        };

      // Members
      private:
      protected:
        std::string						  _filePath;
        std::string						  _dirPath;

        std::string             _jobName;
        std::string             _renderer;
        int                     _renderType;

        ModelDefs               _modelDefs;
  //      LightLst                _lightLst;

        glm::ivec2              _numHogels;
        glm::ivec2              _hogelSize;             
        glm::ivec2              _hogelPitch;             

        glm::mat4               _mVVT;
        glm::mat4               _mScT;

        float                   _fov;     
        glm::vec2               _zNearFar;
        uint32_t                _sliceMem;

        std::string							_outputPath;

        bool                    _tasks[TaskDefsNum];

      public:   

      // Methods
      private:
      protected:

 //       int  parseLights    (JSon::Value &doc);
        int  parseModels    (JSon::Value &doc);
        int  parseTasks     (JSon::Value &doc);
        int  parseDocument  (JSon::Value &doc);

      public:

        const std::string &jobName(void)
        { return _jobName; }

        const std::string &renderer(void)
        { return _renderer; }

        const int renderType(void)
        { return _renderType; }

 //       const LightLst &lightList(void)
 //       { return _lightLst; }

        const size_t numModels(void)
        { return _modelDefs.size(); }

        const std::filesystem::path &modelPath(const size_t i)
        { return _modelDefs[i]._mPath; }

        const glm::mat4 &modelTransform(const size_t i)
        { return _modelDefs[i]._mT; }

        const std::string &outputPath(void)
        { return _outputPath; }

        const glm::ivec2 &hogelSize(void)
        { return _hogelSize; }

        const glm::ivec2 &numHogels(void)
        { return _numHogels; }

        const float &zNear(void)
        { return _zNearFar.x; }

        const float &zFar(void)
        { return _zNearFar.y; }

        const uint16_t sliceMem(void)
        { return _sliceMem; }

        const glm::mat4 &viewVolumeTransform(void)
        { return _mVVT; }

        const glm::mat4 &sceneTransform(void)
        { return _mScT; }

        const float fov(void)
        { return _fov; }

        const bool isTask(TaskDefs t)
        { return _tasks[t]; }

        EXPORT void print(std::ostream &o);

        EXPORT int parse(const std::filesystem::path &fPath);
  
        EXPORT Job(void);
        EXPORT virtual ~Job();
    };
  };
};
 //---------------------------------------------------------------------

