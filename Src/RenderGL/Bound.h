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
// Bound.h

#pragma once


//---------------------------------------------------------------------
// Includes

// System

// LightField

//---------------------------------------------------------------------



//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace RenderGL
  {
    class Bound
    {
      // Definitions
      private:
      protected:
      public:   

      // Members
      private:
      protected:
        glm::vec3           _vMin;
        glm::vec3           _vMax;
        glm::vec3           _vCen;
        glm::vec3           _vDim;
        float               _radius;

      public:
      
      // Methods
      private:
      protected:
        void calculate(void)
        { 
          _vCen   = (_vMax + _vMin) * 0.5f; 
          _vDim   = (_vMax - _vMin);
          _radius = glm::distance(_vMax,_vMin) * 0.5f;
        }

      public:
        void  adjustBounds(const glm::mat4 &mT)
        {
          _vMin = glm::vec3(mT * glm::vec4(_vMin,0));
          _vMax = glm::vec3(mT * glm::vec4(_vMax,0));

          calculate();
        }

        void  bound(const glm::vec3 &v)
        {
          _vMin = glm::min(_vMin,v);
          _vMax = glm::max(_vMax,v);

          calculate();
        }
      
        void  bound(const glm::vec3 &v1,const glm::vec3 &v2)
        {
          _vMin = glm::min(_vMin,v1);
          _vMax = glm::max(_vMax,v1);

          _vMin = glm::min(_vMin,v2);
          _vMax = glm::max(_vMax,v2);

          calculate();
        }

        void setMax(const glm::vec3 &v)
        { 
          _vMax = v; 

          calculate();
        }

        void setMin(const glm::vec3 &v)
        { 
          _vMin = v; 

          calculate();
        }

        const glm::vec3 &vMin(void) const
        { return _vMin; }

        const glm::vec3 &vMax(void) const
        { return _vMax; }

        const glm::vec3 &cen(void) const
        { return _vCen; }

        const float radius(void) const
        { return _radius; }
   
        Bound(void) : _vMin(FLT_MAX),
                      _vMax(-FLT_MAX),
                      _vCen(0),
                      _vDim(0),
                      _radius(0)
        {}

        ~Bound()
        {}
    };
  };
};
//---------------------------------------------------------------------



