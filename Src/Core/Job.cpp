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
// Job.cpp

//---------------------------------------------------------------------

// Includes
// System
#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>

// 3rdPartyLibs
#include "glm/gtc/type_ptr.hpp"

// LightField
#include "Core/Job.h"

using namespace Lf;
using namespace Core;
//---------------------------------------------------------------------


#if (0)
//---------------------------------------------------------------------
// parseLights
//---------------------------------------------------------------------
int Job::parseLights(JSon::Value &doc)
{
int               rc = 0;
JSon::Value&  v = doc["Lights"];

  if (!v.is_null() && v.is_object())
  {
  JSon::Value::size_type n = v.size();

    for (JSon::Value::size_type i = 0; i < n; i++)
    {
    std::string lite = "Light_" + std::to_string(i);
    Light       lt;
    glm::mat4   mL;
    JSonConfig::parseLight(v, lite.c_str(), mL);

      //uncomment line below to print string representation
      //of lights from hrd file
      //std::cout << v[0].dump() << std::endl;
      lt.setProperties(mL);
  
      _lightLst.push_back(lt);
    }
  }
  else
  {
    std::cout << "Error parsing Lights" << std::endl;
    rc = -1;
  }

  return rc;
}
#endif


//---------------------------------------------------------------------
// printMatrix
//---------------------------------------------------------------------
void printMatrix(std::ostream &s,std::string idt,const char *str,const glm::mat4 &m)
{
  s << idt << str << std::endl;
  s << idt << " " << m[0].x << " " << m[0].y << " " << m[0].z << " " << m[0].w << std::endl; 
  s << idt << " " << m[1].x << " " << m[1].y << " " << m[1].z << " " << m[1].w << std::endl; 
  s << idt << " " << m[2].x << " " << m[2].y << " " << m[2].z << " " << m[2].w << std::endl; 
  s << idt << " " << m[3].x << " " << m[3].y << " " << m[3].z << " " << m[3].w << std::endl; 
}


//---------------------------------------------------------------------
// parseModels
//---------------------------------------------------------------------
int Job::parseModels(JSon::Value &doc)
{
int              rc = 0;
JSon::Value &v = doc["Models"];

  if (!v.is_null() && v.is_array())
  {
		JSon::Value::size_type n = v.size();

    for (JSon::Value::size_type i = 0;i < n;i++)
    {
    ModelDef          md;
    int               r = 0;
  	std::string       fName;

			JSon::parse(v[i],"Transform",md._mT);

      rc |= r = JSon::parse(v[i],"File",fName);

      if (r == 0)
      {
      std::filesystem::path fPath = _dirPath;

        fPath /= fName;
          
        if (std::filesystem::exists(fPath))
        {
          md._mPath = fPath.string();

          _modelDefs.push_back(md);
        }
        else
        {
          std::cout << "Model_Path not found: " << fPath << std::endl;
          rc |= -1;
        }        
      }
    }
  }
  else 
  {
    std::cout << "Models is incorrect" << std::endl;
    rc = -1;
  }

  return rc;
}


//---------------------------------------------------------------------
// parseLight
//---------------------------------------------------------------------
int Job::parseLight(JSon::Value &doc)
{
int              rc = 0;
JSon::Value &v = doc["Light"];

  if (!v.is_null())
  {
		std::cout << std::endl;

		JSon::parse(v, "Ambient",        _lightDef._ambient,          false);
		JSon::parse(v, "Diffuse",        _lightDef._diffuse,          false);
		JSon::parse(v, "Specular",       _lightDef._specular,         false);
		JSon::parse(v, "Position",       _lightDef._position,         false);

		rc = 0;
  }

  return rc;
}


//---------------------------------------------------------------------
// parseTasks
//---------------------------------------------------------------------
int Job::parseTasks(JSon::Value &doc)
{
int              rc = -1;
JSon::Value &v = doc["Tasks"];

  if (!v.is_null())
  {
		std::cout << std::endl;

		JSon::parse(v, "ProofImage",         _tasks[ProofImage],          false);
		JSon::parse(v, "WriteAvi",           _tasks[WriteAvi],            false);
		JSon::parse(v, "WriteImg",           _tasks[WriteImg],            false);
		JSon::parse(v, "WriteDemo",          _tasks[WriteDemo],           false);
		JSon::parse(v, "WriteDepthImg",      _tasks[WriteDepthImg],       false);
		JSon::parse(v, "ProofDepth",         _tasks[ProofDepth],          false);

    if (_renderType == Oblique)
		  JSon::parse(v, "SliceNDice",       _tasks[SliceOblique],        false);

		rc = 0;
  }

  return rc;
}


//---------------------------------------------------------------------
// parseDocument
//---------------------------------------------------------------------
int Job::parseDocument(JSon::Value &doc)
{
int rc = 0;

	JSon::parse(doc, "JobName",    _jobName);
	JSon::parse(doc, "Renderer",   _renderer);
	JSon::parse(doc, "OutputPath", _outputPath);

  if ((_renderer == "DF") || (_renderer == "DoubleFrustum"))
    _renderType = DoubleFrustum;
  else if (_renderer == "Oblique")
    _renderType = Oblique;
  else
    assert(0);

  {
		JSon::parse(doc, "FieldOfView",          _fov);
		JSon::parse(doc, "HogelSize",            _hogelSize);
    _hogelPitch = _hogelSize;
		JSon::parse(doc, "HogelPitch",           _hogelPitch);
		JSon::parse(doc, "NumHogels",            _numHogels);
		JSon::parse(doc, "zNearFar",             _zNearFar);
		JSon::parse(doc, "SliceMem",             _sliceMem);
  }

  rc |= JSon::parse(doc,"ViewVolume",_mVVT);
  rc |= JSon::parse(doc,"Scene",_mScT);

  rc |= parseModels(doc);
  rc |= parseLight(doc);
  rc |= parseTasks(doc);
 
  return rc;
}


//---------------------------------------------------------------------
// parse
//---------------------------------------------------------------------
int Job::parse(const std::filesystem::path &fPath)
{
int rc    = -1;

  if (std::filesystem::exists(fPath))
  {
	JSon::Value doc;

		_filePath = fPath.string();
		_dirPath = fPath.parent_path().string();

		rc = JSon::read(_filePath,doc);

		if (rc == 0)
			rc = parseDocument(doc);
  }

  return rc;
}


//---------------------------------------------------------------------
// print
//---------------------------------------------------------------------
void Job::print(std::ostream &o)
{
  o << "               Job Name: "  << _jobName << std::endl;
  o << "         Directory Path: "  << _dirPath << std::endl;
  o << "               Renderer: "  << _renderer << std::endl;
  o << "            Output Path: "  << _outputPath << std::endl;
  o << "             Num Hogels: (" << _numHogels.x << ","  << _numHogels.y  << ")" << std::endl;
  o << "             Hogel Size: (" << _hogelSize.x << ","  << _hogelSize.y  << ")" << std::endl;
  o << "            Hogel Pitch: (" << _hogelPitch.x << "," << _hogelPitch.y << ")" << std::endl;
  o << "                    FoV: "  << _fov << std::endl;
  o << "         Z Near and Far: (" << _zNearFar.x << ","   << _zNearFar.y << ")" << std::endl;
  o << "           Slice Memory: "  << _sliceMem << "g" << std::endl;

	o << "        ProofImage Task: " << (_tasks[ProofImage]         ? "true" : "false") << std::endl;
	o << "          WriteAvi Task: " << (_tasks[WriteAvi]           ? "true" : "false") << std::endl;
	o << "          WriteImg Task: " << (_tasks[WriteImg]           ? "true" : "false") << std::endl;
	o << "         WriteDemo Task: " << (_tasks[WriteDemo]          ? "true" : "false") << std::endl;
	o << "        ProofDepth Task: " << (_tasks[ProofDepth]         ? "true" : "false") << std::endl;
	o << "     WriteDepthImg Task: " << (_tasks[WriteDepthImg]      ? "true" : "false") << std::endl;
	o << "      SliceOblique Task: " << (_tasks[SliceOblique]       ? "true" : "false") << std::endl;

	o << std::endl;

  {
  size_t n = _modelDefs.size();
  char buf2[32];

   o << "Model Definition" << std::endl;

    for (size_t i = 0;i < n;i++)
      o << "  Model Path[" << i << "]: " << _modelDefs[i]._mPath << std::endl;
  }

  o << "Light Definition" << std::endl;

  o << "  Position: " << _lightDef._position.x << "  " 
                      << _lightDef._position.y << "  " 
                      << _lightDef._position.z << std::endl;
  o << "  Ambient: "  << _lightDef._ambient.x << "  " 
                      << _lightDef._ambient.y << "  " 
                      << _lightDef._ambient.z << std::endl;
  o << "  Diffuse: "  << _lightDef._diffuse.x << "  " 
                      << _lightDef._diffuse.y << "  " 
                      << _lightDef._diffuse.z << std::endl;
  o << "  Specular: " << _lightDef._specular.x << "  " 
                      << _lightDef._specular.y << "  " 
                      << _lightDef._specular.z << std::endl;
}


//---------------------------------------------------------------------
// Job
//---------------------------------------------------------------------
Job::Job(void) : _filePath(),
                 _dirPath(),
                 _jobName(),
                 _renderer("DoubleFrustum"),
                 _renderType(DoubleFrustum),
                 _modelDefs(),   
                 _lightDef(),
                 _numHogels(0),
                 _hogelSize(0),
                 _hogelPitch(_hogelSize),
                 _mVVT(1),
                 _mScT(1),
                 _fov(90),
                 _zNearFar(0.001f,1.0f),
                 _sliceMem(8),
                 _outputPath(),
                 _tasks()
{
  for (int i = 0;i < TaskDefsNum;i++)
    _tasks[i] = false;

  _tasks[ProofImage] = true;
}


//---------------------------------------------------------------------
// ~Job
//---------------------------------------------------------------------
Job::~Job()
{

}

