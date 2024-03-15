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

// JSon.h
// Thomas Burnett

#pragma once

//---------------------------------------------------------------------
// Includes
// System
#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <cstdlib>

// 3rdPartyLibs
#include <glm/glm.hpp>

// LightField
#include "nlohmann/json.hpp"
#include "Core/Export.h"
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Classes
namespace Lf
{
  namespace Core
  {
	  class JSon
	  {
		  // Defines
	  private:
	  protected:
	  public:
		  typedef nlohmann::json Value;
		  // Members
	  private:
	  public:

		  // Methods
	  private:
	  protected:

	  public:
      static void printParseError(const char *pT);

		  //parse(json structure _doc, pointer, value looking for, required or not)
		  EXPORT static int parse(Value &v, const char *pT, std::string                       &val, bool req = false, bool quiet = false);
		  EXPORT static int parse(Value &v, const char *pT, float                             &val, bool req = false, bool quiet = false);
		  EXPORT static int parse(Value &v, const char *pT, double                            &val, bool req = false, bool quiet = false);
		  EXPORT static int parse(Value &v, const char *pT, int32_t                           &val, bool req = false, bool quiet = false);
		  EXPORT static int parse(Value &v, const char *pT, int64_t                           &val, bool req = false, bool quiet = false);
		  EXPORT static int parse(Value &v, const char *pT, uint8_t                           &val, bool req = false, bool quiet = false);
		  EXPORT static int parse(Value &v, const char *pT, uint16_t                          &val, bool req = false, bool quiet = false);
		  EXPORT static int parse(Value &v, const char *pT, uint32_t                          &val, bool req = false, bool quiet = false);
		  EXPORT static int parse(Value &v, const char *pT, uint64_t                          &val, bool req = false, bool quiet = false);
		  EXPORT static int parse(Value &v, const char *pT, bool                              &val, bool req = false, bool quiet = false);
		  EXPORT static int parse(Value &v, const char *pT, glm::vec2                         &val, bool req = false, bool quiet = false);
		  EXPORT static int parse(Value &v, const char *pT, glm::vec3                         &val, bool req = false, bool quiet = false);
		  EXPORT static int parse(Value &v, const char *pT, glm::vec4                         &val, bool req = false, bool quiet = false);
		  EXPORT static int parse(Value &v, const char *pT, glm::dvec2                        &val, bool req = false, bool quiet = false);
		  EXPORT static int parse(Value &v, const char *pT, glm::dvec3                        &val, bool req = false, bool quiet = false);
		  EXPORT static int parse(Value &v, const char *pT, glm::dvec4                        &val, bool req = false, bool quiet = false);
		  EXPORT static int parse(Value &v, const char *pT, glm::ivec2                        &val, bool req = false, bool quiet = false);
		  EXPORT static int parse(Value &v, const char *pT, glm::ivec3                        &val, bool req = false, bool quiet = false);
		  EXPORT static int parse(Value &v, const char *pT, glm::ivec4                        &val, bool req = false, bool quiet = false);
		  EXPORT static int parse(Value &v, const char *pT, glm::tvec2<unsigned short>        &val, bool req = false, bool quiet = false);
		  EXPORT static int parse(Value &v, const char *pT, glm::tvec2<unsigned char>         &val, bool req = false, bool quiet = false);
		  EXPORT static int parse(Value &v, const char *pT, glm::tvec2<signed char>           &val, bool req = false, bool quiet = false);
		  EXPORT static int parse(Value &v, const char *pT, glm::tvec2<uint32_t>              &val, bool req = false, bool quiet = false);
		  EXPORT static int parse(Value &v, const char *pT, glm::quat                         &val, bool req = false, bool quiet = false);
		  EXPORT static int parse(Value &v, const char *pT, glm::mat3                         &val, bool req = false, bool quiet = false);
		  EXPORT static int parse(Value &v, const char *pT, glm::mat4                         &val, bool req = false, bool quiet = false);
		  EXPORT static int parse(Value &v, const char *pT, std::vector<int>                  &val, bool req = false, bool quiet = false);
		  EXPORT static int parse(Value &v, const char *pT, std::vector<uint32_t>             &val, bool req = false, bool quiet = false);
		  EXPORT static int parse(Value &v, const char *pT, std::vector<float>                &val, bool req = false, bool quiet = false);
		  EXPORT static int parse(Value &v, const char *pT, std::vector<std::string>          &val, bool req = false, bool quiet = false);
		  EXPORT static int parse(Value &v, const char *pT, std::vector<glm::vec2>            &val, bool req = false, bool quiet = false);
		  EXPORT static int parse(Value &v, const char *pT, std::vector<glm::dvec2>           &val, bool req = false, bool quiet = false);
		  EXPORT static int parse(Value &v, const char *pT, std::list<glm::vec2>              &val, bool req = false, bool quiet = false);
		  EXPORT static int parse(Value &v, const char *pT, std::list<glm::dvec2>             &val, bool req = false, bool quiet = false);
    
		  EXPORT static void insert(Value &v, const char* pT, const std::string                 &val);
		  EXPORT static void insert(Value &v, const char* pT, const float                       &val);
		  EXPORT static void insert(Value &v, const char* pT, const double                      &val);
		  EXPORT static void insert(Value &v, const char* pT, const int32_t                     &val);
		  EXPORT static void insert(Value &v, const char* pT, const int64_t                     &val);
		  EXPORT static void insert(Value &v, const char* pT, const uint16_t                    &val);
		  EXPORT static void insert(Value &v, const char* pT, const uint32_t                    &val);
		  EXPORT static void insert(Value &v, const char* pT, const uint64_t                    &val);
		  EXPORT static void insert(Value &v, const char* pT, const bool                        &val);
		  EXPORT static void insert(Value &v, const char* pT, const glm::vec2                   &val);
		  EXPORT static void insert(Value &v, const char* pT, const glm::vec3                   &val);
		  EXPORT static void insert(Value &v, const char* pT, const glm::vec4                   &val);
		  EXPORT static void insert(Value &v, const char* pT, const glm::quat                   &val);
		  EXPORT static void insert(Value &v, const char* pT, const glm::ivec2                  &val);
		  EXPORT static void insert(Value &v, const char* pT, const glm::tvec2<unsigned short>  &val);
		  EXPORT static void insert(Value &v, const char* pT, const glm::tvec2<unsigned char>   &val);
		  EXPORT static void insert(Value &v, const char* pT, const glm::tvec2<signed char>     &val);
		  EXPORT static void insert(Value &v, const char* pT, const glm::tvec2<uint32_t>        &val);
		  EXPORT static void insert(Value &v, const char* pT, const glm::mat4                   &val);
		  EXPORT static void insert(Value &v, const char* pT, const std::vector<int>					  &val);
		  EXPORT static void insert(Value &v, const char* pT, const std::vector<float>				  &val);

		  EXPORT static int read(const char *pFP,Value &v);
		  EXPORT static int read(const std::string &filePath,Value &v);
	    
		  EXPORT static int write(const char *pFP,Value &v);
		  EXPORT static int write(const std::string &filePath,Value &v);

		  EXPORT JSon(void)
		  {}

		  EXPORT ~JSon()
		  {}
	  };
  };
};
//---------------------------------------------------------------------

