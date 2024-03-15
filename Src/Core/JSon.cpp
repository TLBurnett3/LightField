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

// JSon.cpp 
// Thomas Burnett


//---------------------------------------------------------------------
// Includes
// System
#include <iomanip>

// 3rdPartyLibs
#include <glm/ext.hpp>
#include <glm/gtc/type_ptr.hpp>

// LightField
#include "Core/JSon.h"

using namespace Lf;
using namespace Core;
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// parse
//---------------------------------------------------------------------
void JSon::printParseError(const char *pT)
{
  printf("Fatal config parse error: %s not found\n",pT);
}


//---------------------------------------------------------------------
// parse
//---------------------------------------------------------------------
int JSon::parse(Value &v, const char *pT, std::string &val, bool req, bool quiet)
{
int rc = -1;

  if (!v[pT].is_null())
  {
    if (v[pT].is_string())
  	{
	    val = v[pT].get<std::string>();
  	  rc = 0;
  	}
  }

  if ((rc == -1) && (!req))
	rc = 0;
 
  if (rc && !quiet)
    JSon::printParseError(pT);

	return rc;
}


//---------------------------------------------------------------------
// parse
//---------------------------------------------------------------------
int JSon::parse(Value &v, const char *pT, float &val, bool req, bool quiet)
{
int rc = -1;

	if (!v[pT].is_null())
	{
		if (v[pT].is_number_float())
		{
			val = v[pT].get<float>();
			rc = 0;
		}
		else if (v[pT].is_number_integer())
		{
			val = (float)v[pT].get<int64_t>();
			rc = 0;
		}
	}

	if ((rc == -1) && !req)
		rc = 0;

  if (rc && !quiet)
    JSon::printParseError(pT);

	return rc;
}

//---------------------------------------------------------------------
// parse
//---------------------------------------------------------------------
int JSon::parse(Value &v, const char *pT, double &val, bool req, bool quiet)
{
int rc = -1;

	if (!v[pT].is_null())
	{
		if (v[pT].is_number_float())
		{
			val = v[pT].get<double>();
			rc = 0;
		}
		else if (v[pT].is_number_integer())
		{
			val = (double)v[pT].get<int64_t>();
			rc = 0;
		}
	}

	if ((rc == -1) && !req)
		rc = 0;

  if (rc && !quiet)
    JSon::printParseError(pT);

	return rc;
}

//---------------------------------------------------------------------
// parse
//---------------------------------------------------------------------
int JSon::parse(Value &v, const char *pT, int32_t &val, bool req, bool quiet)
{
int rc = -1;

	if (!v[pT].is_null())
	{
		if (v[pT].is_number_integer())
		{
			val = v[pT].get<int32_t>();
			rc = 0;
		}
	}

	if ((rc == -1) && !req)
		rc = 0;

  if (rc && !quiet)
    JSon::printParseError(pT);

	return rc;
}

//---------------------------------------------------------------------
// parse
//---------------------------------------------------------------------
int JSon::parse(Value &v, const char *pT, int64_t &val, bool req, bool quiet)
{
int rc = -1;

	if (!v[pT].is_null())
	{
		if (v[pT].is_number_integer())
		{
			val = v[pT].get<int64_t>();
			rc = 0;
		}
	}

	if ((rc == -1) && !req)
		rc = 0;

  if (rc && !quiet)
    JSon::printParseError(pT);

	return rc;
}

//---------------------------------------------------------------------
// parse
//---------------------------------------------------------------------
int JSon::parse(Value &v, const char *pT, uint8_t &val, bool req, bool quiet)
{
int rc = -1;

	if (!v[pT].is_null())
	{
		if (v[pT].is_number_unsigned())
		{
			val = v[pT].get<uint8_t>();
			rc = 0;
		}
	}

	if ((rc == -1) && !req)
		rc = 0;

  if (rc && !quiet)
    JSon::printParseError(pT);

	return rc;
}

//---------------------------------------------------------------------
// parse
//---------------------------------------------------------------------
int JSon::parse(Value &v, const char *pT, uint16_t &val, bool req, bool quiet)
{
int rc = -1;

	if (!v[pT].is_null())
	{
		if (v[pT].is_number_unsigned())
		{
			val = v[pT].get<uint16_t>();
			rc = 0;
		}
	}

	if ((rc == -1) && !req)
		rc = 0;

  if (rc && !quiet)
    JSon::printParseError(pT);

	return rc;
}

//---------------------------------------------------------------------
// parse
//---------------------------------------------------------------------
int JSon::parse(Value &v, const char *pT, uint32_t &val, bool req, bool quiet)
{
int rc = -1;

	if (!v[pT].is_null())
	{
		if (v[pT].is_number_unsigned())
		{
			val = v[pT].get<uint32_t>();
			rc = 0;
		}
	}

	if ((rc == -1) && !req)
		rc = 0;

  if (rc && !quiet)
    JSon::printParseError(pT);

	return rc;
}

//---------------------------------------------------------------------
// parse
//---------------------------------------------------------------------
int JSon::parse(Value &v, const char *pT, uint64_t &val, bool req, bool quiet)
{
int rc = -1;

	if (!v[pT].is_null())
	{
		if (v[pT].is_number_unsigned())
		{
			val = v[pT].get<uint64_t>();
			rc = 0;
		}
	}

	if ((rc == -1) && !req)
		rc = 0;

  if (rc && !quiet)
    JSon::printParseError(pT);

	return rc;
}

//---------------------------------------------------------------------
// parse
//---------------------------------------------------------------------
int JSon::parse(Value &v, const char *pT, bool &val, bool req, bool quiet)
{
int rc = -1;

	if (!v[pT].is_null())
	{
		if (v[pT].is_boolean())
		{
			val = v[pT].get<bool>();
			rc = 0;
		}
	}

	if ((rc == -1) && !req)
		rc = 0;

  if (rc && !quiet)
    JSon::printParseError(pT);

	return rc;
}

//---------------------------------------------------------------------
// parse
//---------------------------------------------------------------------
int JSon::parse(Value &v, const char *pT, glm::vec2 &val, bool req, bool quiet)
{
int rc = -1;

	if (!v[pT].is_null())
	{
		if (v[pT].is_array())
		{
			if (v[pT].size() == 2)
			{
				Value::iterator it = v[pT].begin();

				val.x = (*it++).get<float>();
				val.y = (*it++).get<float>();
				rc = 0;
			}
		}
	}

	if ((rc == -1) && !req)
		rc = 0;

  if (rc && !quiet)
    JSon::printParseError(pT);

	return rc;
}


//---------------------------------------------------------------------
// parse
//---------------------------------------------------------------------
int JSon::parse(Value &v, const char *pT, glm::vec3 &val, bool req, bool quiet)
{
int rc = -1;

	if (!v[pT].is_null())
	{
		if (v[pT].is_array())
		{
			if (v[pT].size() == 3)
			{
		  Value::iterator it = v[pT].begin();

				val.x = (*it++).get<float>();
				val.y = (*it++).get<float>();
				val.z = (*it++).get<float>();
				rc = 0;
			}
		}
	}

	if ((rc == -1) && !req)
		rc = 0;

  if (rc && !quiet)
    JSon::printParseError(pT);

	return rc;
}

int JSon::parse(Value &v, const char *pT, glm::vec4 &val, bool req, bool quiet)
{
int rc = -1;

	if (!v[pT].is_null())
	{
		if (v[pT].is_array())
		{
			if (v[pT].size() == 4)
			{
			Value::iterator it = v[pT].begin();

				val.x = (*it++).get<float>();
				val.y = (*it++).get<float>();
				val.z = (*it++).get<float>();
				val.w = (*it++).get<float>();
				rc = 0;
			}
		}
	}

	if ((rc == -1) && !req)
		rc = 0;

  if (rc && !quiet)
    JSon::printParseError(pT);

	return rc;
}


//---------------------------------------------------------------------
// parse
//---------------------------------------------------------------------
int JSon::parse(Value &v, const char *pT, glm::dvec2 &val, bool req, bool quiet)
{
int rc = -1;

	if (!v[pT].is_null())
	{
		if (v[pT].is_array())
		{
			if (v[pT].size() == 2)
			{
				Value::iterator it = v[pT].begin();

				val.x = (*it++).get<double>();
				val.y = (*it++).get<double>();
				rc = 0;
			}
		}
	}

	if ((rc == -1) && !req)
		rc = 0;

  if (rc && !quiet)
    JSon::printParseError(pT);

	return rc;
}


//---------------------------------------------------------------------
// parse
//---------------------------------------------------------------------
int JSon::parse(Value &v, const char *pT, glm::dvec3 &val, bool req, bool quiet)
{
int rc = -1;

	if (!v[pT].is_null())
	{
		if (v[pT].is_array())
		{
			if (v[pT].size() == 3)
			{
		  Value::iterator it = v[pT].begin();

				val.x = (*it++).get<double>();
				val.y = (*it++).get<double>();
				val.z = (*it++).get<double>();
				rc = 0;
			}
		}
	}

	if ((rc == -1) && !req)
		rc = 0;

  if (rc && !quiet)
    JSon::printParseError(pT);

	return rc;
}

int JSon::parse(Value &v, const char *pT, glm::dvec4 &val, bool req, bool quiet)
{
int rc = -1;

	if (!v[pT].is_null())
	{
		if (v[pT].is_array())
		{
			if (v[pT].size() == 4)
			{
				Value::iterator it = v[pT].begin();

				val.x = (*it++).get<double>();
				val.y = (*it++).get<double>();
				val.z = (*it++).get<double>();
				val.w = (*it++).get<double>();
				rc = 0;
			}
		}
	}

	if ((rc == -1) && !req)
		rc = 0;

  if (rc && !quiet)
    JSon::printParseError(pT);

	return rc;
}


//---------------------------------------------------------------------
// parse
//---------------------------------------------------------------------
int JSon::parse(Value &v, const char *pT, glm::ivec2 &val, bool req, bool quiet)
{
int rc = -1;

	if (!v[pT].is_null())
	{
		if (v[pT].is_array())
		{
			if (v[pT].size() == 2)
			{
			Value::iterator it = v[pT].begin();

				val.x = (*it++).get<int>();
				val.y = (*it++).get<int>();

				rc = 0;
			}
		}
	}

	if ((rc == -1) && !req)
		rc = 0;

  if (rc && !quiet)
    JSon::printParseError(pT);

	return rc;
}


//---------------------------------------------------------------------
// parse
//---------------------------------------------------------------------
int JSon::parse(Value &v, const char *pT, glm::ivec3 &val, bool req, bool quiet)
{
int rc = -1;

	if (!v[pT].is_null())
	{
		if (v[pT].is_array())
		{
			if (v[pT].size() == 3)
			{
				Value::iterator it = v[pT].begin();

				val.x = (*it++).get<int>();
				val.y = (*it++).get<int>();
				val.z = (*it++).get<int>();
				rc = 0;
			}
		}
	}

	if ((rc == -1) && !req)
		rc = 0;

  if (rc && !quiet)
    JSon::printParseError(pT);

	return rc;
}


//---------------------------------------------------------------------
// parse
//---------------------------------------------------------------------
int JSon::parse(Value &v, const char *pT, glm::ivec4 &val, bool req, bool quiet)
{
int rc = -1;

	if (!v[pT].is_null())
	{
		if (v[pT].is_array())
		{
			if (v[pT].size() == 4)
			{
				Value::iterator it = v[pT].begin();

				val.x = (*it++).get<int>();
				val.y = (*it++).get<int>();
				val.z = (*it++).get<int>();
				val.w = (*it++).get<int>();
				rc = 0;
			}
		}
	}

	if ((rc == -1) && !req)
		rc = 0;

  if (rc && !quiet)
    JSon::printParseError(pT);

	return rc;
}


//---------------------------------------------------------------------
// parse
//---------------------------------------------------------------------
int JSon::parse(Value &v, const char *pT, glm::tvec2<unsigned short> &val, bool req, bool quiet)
{
int rc = -1;

	if (!v[pT].is_null())
	{
		if (v[pT].is_array())
		{
			if (v[pT].size() == 2)
			{
				Value::iterator it = v[pT].begin();

				val.x = (*it++).get<int>();
				val.y = (*it++).get<int>();
				rc = 0;
			}
		}
	}

	if ((rc == -1) && !req)
		rc = 0;

  if (rc && !quiet)
    JSon::printParseError(pT);

	return rc;
}


//---------------------------------------------------------------------
// parse
//---------------------------------------------------------------------
int JSon::parse(Value &v, const char *pT, glm::tvec2<unsigned char> &val, bool req, bool quiet)
{
int rc = -1;

	if (!v[pT].is_null())
	{
		if (v[pT].is_array())
		{
			if (v[pT].size() == 2)
			{
				Value::iterator it = v[pT].begin();

				val.x = (*it++).get<int>();
				val.y = (*it++).get<int>();
				rc = 0;
			}
		}
	}

	if ((rc == -1) && !req)
		rc = 0;

  if (rc && !quiet)
    JSon::printParseError(pT);

	return rc;
}


//---------------------------------------------------------------------
// parse
//---------------------------------------------------------------------
int JSon::parse(Value &v, const char *pT, glm::tvec2<signed char> &val, bool req, bool quiet)
{
int rc = -1;

	if (!v[pT].is_null())
	{
		if (v[pT].is_array())
		{
			if (v[pT].size() == 2)
			{
				Value::iterator it = v[pT].begin();

				val.x = (*it++).get<int>();
				val.y = (*it++).get<int>();
				rc = 0;
			}
		}
	}

	if ((rc == -1) && !req)
		rc = 0;

  if (rc && !quiet)
    JSon::printParseError(pT);

	return rc;
}


//---------------------------------------------------------------------
// parse
//---------------------------------------------------------------------
int JSon::parse(Value &v, const char *pT, glm::tvec2<uint32_t> &val, bool req, bool quiet)
{
int rc = -1;

	if (!v[pT].is_null())
	{
		if (v[pT].is_array())
		{
			if (v[pT].size() == 2)
			{
				Value::iterator it = v[pT].begin();

				val.x = (*it++).get<int>();
				val.y = (*it++).get<int>();
				rc = 0;
			}
		}
	}

	if ((rc == -1) && !req)
		rc = 0;

  if (rc && !quiet)
    JSon::printParseError(pT);

	return rc;
}


//---------------------------------------------------------------------
// parse
//---------------------------------------------------------------------
int JSon::parse(Value &v, const char *pT, glm::quat &val, bool req, bool quiet)
{
int rc = -1;

	if (!v[pT].is_null())
	{
		if (v[pT].is_array())
		{
			if (v[pT].size() == 4)
			{
				Value::iterator it = v[pT].begin();

				val.x = (*it++).get<float>();
				val.y = (*it++).get<float>();
				val.z = (*it++).get<float>();
				val.w = (*it++).get<float>();
				rc = 0;
			}
			else if (v[pT].size() == 3)
			{
				Value::iterator it = v[pT].begin();
				glm::vec3 vR;

				vR.x = (*it++).get<float>();
				vR.y = (*it++).get<float>();
				vR.z = (*it++).get<float>();
				vR = glm::radians(vR);

				val = glm::quat(vR);
			}
		}
	}

	if ((rc == -1) && !req)
		rc = 0;

  if (rc && !quiet)
    JSon::printParseError(pT);

	return rc;
}


//---------------------------------------------------------------------
// parse
//---------------------------------------------------------------------
int JSon::parse(Value &v, const char *pT, glm::mat3 &val, bool req, bool quiet)
{
int rc = -1;

	if (!v[pT].is_null())
	{
		if (v[pT].is_array())
		{
			if (v[pT].size() == 9)
			{
				Value::iterator it = v[pT].begin();

				val[0][0] = (*it++).get<float>();
				val[0][1] = (*it++).get<float>();
				val[0][2] = (*it++).get<float>();

				val[1][0] = (*it++).get<float>();
				val[1][1] = (*it++).get<float>();
				val[1][2] = (*it++).get<float>();

				val[2][0] = (*it++).get<float>();
				val[2][1] = (*it++).get<float>();
				val[2][2] = (*it++).get<float>();

				rc = 0;
			}
		}
	}

	if ((rc == -1) && !req)
		rc = 0;

  if (rc && !quiet)
    JSon::printParseError(pT);

	return rc;
}


//---------------------------------------------------------------------
// parse
//---------------------------------------------------------------------
int JSon::parse(Value &v, const char *pT, glm::mat4 &val, bool req, bool quiet)
{
int rc = -1;

	if (!v[pT].is_null())
	{
		if (v[pT].is_object())
		{
		glm::vec3 vT(0);
		glm::vec3 vS(1);
		glm::vec3 vR(0);
		glm::quat qO;

			JSon::parse(v[pT], "Translate",    vT);
			JSon::parse(v[pT], "Scale",        vS);
			JSon::parse(v[pT], "Rotate",       vR);

			qO = glm::quat(glm::radians(glm::vec3(vR.x,vR.y,vR.z)));

			val = glm::translate(val,vT);
			val = val * glm::mat4(qO);
			val = glm::scale(val,vS);

			rc = 0;
		}
		else
		if (v[pT].is_array())
		{
			if (v[pT].size() == 16)
			{
				Value::iterator it = v[pT].begin();

				val[0][0] = (*it++).get<float>();
				val[0][1] = (*it++).get<float>();
				val[0][2] = (*it++).get<float>();
				val[0][3] = (*it++).get<float>();

				val[1][0] = (*it++).get<float>();
				val[1][1] = (*it++).get<float>();
				val[1][2] = (*it++).get<float>();
				val[1][3] = (*it++).get<float>();

				val[2][0] = (*it++).get<float>();
				val[2][1] = (*it++).get<float>();
				val[2][2] = (*it++).get<float>();
				val[2][3] = (*it++).get<float>();

				val[3][0] = (*it++).get<float>();
				val[3][1] = (*it++).get<float>();
				val[3][2] = (*it++).get<float>();
				val[3][3] = (*it++).get<float>();

				rc = 0;
			}
		}
	}

	if ((rc == -1) && !req)
		rc = 0;

  if (rc && !quiet)
    JSon::printParseError(pT);

	return rc;
}


//---------------------------------------------------------------------
// parse
//---------------------------------------------------------------------
int JSon::parse(Value &v, const char *pT, std::vector<int> &val, bool req, bool quiet)
{
int rc = -1;

	if (!v[pT].is_null())
	{
		if (v[pT].is_array())
		{
			rc = 0;
			val.clear();
			for (Value::iterator it = v[pT].begin(); it != v[pT].end(); it++) {
				val.push_back((*it).get<int>());
			}
		}
	}

	if ((rc == -1) && !req)
		rc = 0;

  if (rc && !quiet)
    JSon::printParseError(pT);

	return rc;
}


//---------------------------------------------------------------------
// parse
//---------------------------------------------------------------------
int JSon::parse(Value &v, const char *pT, std::vector<uint32_t> &val, bool req, bool quiet)
{
int rc = -1;

	if (!v[pT].is_null())
	{
		if (v[pT].is_array())
		{
			rc = 0;
			val.clear();
			for (Value::iterator it = v[pT].begin(); it != v[pT].end(); it++) {
				val.push_back((*it).get<uint32_t>());
			}
		}
	}

	if ((rc == -1) && !req)
		rc = 0;

  if (rc && !quiet)
    JSon::printParseError(pT);

	return rc;
}


//---------------------------------------------------------------------
// parse
//---------------------------------------------------------------------
int JSon::parse(Value &v, const char *pT, std::vector<float> &val, bool req, bool quiet)
{
int rc = -1;

	if (!v[pT].is_null())
	{
		if (v[pT].is_array())
		{
			rc = 0;

			val.clear();

			for (Value::iterator it = v[pT].begin(); it != v[pT].end(); it++) 
      {
				val.push_back((*it).get<float>());
			}
		}
	}

	if ((rc == -1) && !req)
		rc = 0;

  if (rc && !quiet)
    JSon::printParseError(pT);

	return rc;
}


//---------------------------------------------------------------------
// parse
//---------------------------------------------------------------------
int JSon::parse(Value &v, const char *pT,std::vector<std::string> &val, bool req, bool quiet)
{
int rc = -1;

	if (!v[pT].is_null())
	{
		if (v[pT].is_array())
		{
			rc = 0;

			val.clear();

			for (Value::iterator it = v[pT].begin(); it != v[pT].end(); it++) 
      {
				val.push_back((*it).get<std::string>());
			}
		}
	}

	if ((rc == -1) && !req)
		rc = 0;

  if (rc && !quiet)
    JSon::printParseError(pT);

	return rc;
}


//---------------------------------------------------------------------
// parse
//---------------------------------------------------------------------
int JSon::parse(Value &v, const char *pT, std::vector<glm::vec2> &val, bool req, bool quiet)
{
int rc = -1;

	if (!v[pT].is_null())
	{
		if (v[pT].is_array())
		{
			rc = 0;

			val.clear();

			for (Value::iterator iT = v[pT].begin();iT != v[pT].end();iT++) 
      {
      glm::vec2  crd;

        if (iT->is_array() && (iT->size() == 2))
        {
				Value::iterator jT = iT->begin(); 
          
          crd.x = (*jT).get<float>(); jT++;   
          crd.y = (*jT).get<float>(); jT++;   

          val.push_back(crd);
        }
			}
		}
	}

	if ((rc == -1) && !req)
		rc = 0;

  if (rc && !quiet)
    JSon::printParseError(pT);

	return rc;
}


//---------------------------------------------------------------------
// parse
//---------------------------------------------------------------------
int JSon::parse(Value &v, const char *pT, std::vector<glm::dvec2> &val, bool req, bool quiet)
{
int rc = -1;

	if (!v[pT].is_null())
	{
		if (v[pT].is_array())
		{
			rc = 0;

			val.clear();

			for (Value::iterator iT = v[pT].begin();iT != v[pT].end();iT++) 
      {
      glm::vec2  crd;

        if (iT->is_array() && (iT->size() == 2))
        {
				Value::iterator jT = iT->begin(); 
          
          crd.x = (float)(*jT).get<double>(); jT++;   
          crd.y = (float)(*jT).get<double>(); jT++;   

          val.push_back(crd);
        }
			}
		}
	}

	if ((rc == -1) && !req)
		rc = 0;

  if (rc && !quiet)
    JSon::printParseError(pT);

	return rc;
}




//---------------------------------------------------------------------
// parse
//---------------------------------------------------------------------
int JSon::parse(Value &v, const char *pT, std::list<glm::vec2> &val, bool req, bool quiet)
{
int rc = -1;

	if (!v[pT].is_null())
	{
		if (v[pT].is_array())
		{
			rc = 0;

			val.clear();

			for (Value::iterator iT = v[pT].begin();iT != v[pT].end();iT++) 
      {
      glm::vec2  crd;

        if (iT->is_array() && (iT->size() == 2))
        {
				Value::iterator jT = iT->begin(); 
          
          crd.x = (*jT).get<float>(); jT++;   
          crd.y = (*jT).get<float>(); jT++;   

          val.push_back(crd);
        }
			}
		}
	}

	if ((rc == -1) && !req)
		rc = 0;

  if (rc && !quiet)
    JSon::printParseError(pT);

	return rc;
}


//---------------------------------------------------------------------
// parse
//---------------------------------------------------------------------
int JSon::parse(Value &v, const char *pT, std::list<glm::dvec2> &val, bool req, bool quiet)
{
int rc = -1;

	if (!v[pT].is_null())
	{
		if (v[pT].is_array())
		{
			rc = 0;

			val.clear();

			for (Value::iterator iT = v[pT].begin();iT != v[pT].end();iT++) 
      {
      glm::dvec2  crd;

        if (iT->is_array() && (iT->size() == 2))
        {
				Value::iterator jT = iT->begin(); 
          
          crd.x = (*jT).get<double>(); jT++;   
          crd.y = (*jT).get<double>(); jT++;   

          val.push_back(crd);
        }
			}
		}
	}

	if ((rc == -1) && !req)
		rc = 0;

  if (rc && !quiet)
    JSon::printParseError(pT);

	return rc;
}


//---------------------------------------------------------------------
// insert
//---------------------------------------------------------------------
void JSon::insert(Value &v, const char* pT, const std::string &val)
{
	if (v.is_array())
		v.push_back(val);
	else
		v[pT] = val;
}

//---------------------------------------------------------------------
// insert
//---------------------------------------------------------------------
void JSon::insert(Value &v, const char* pT, const float &val)
{
	if (v.is_array())
		v.push_back(val);
	else
		v[pT] = val;
}

//---------------------------------------------------------------------
// insert
//---------------------------------------------------------------------
void JSon::insert(Value &v, const char* pT, const double &val)
{
	if (v.is_array())
		v.push_back(val);
	else
		v[pT] = val;
}

//---------------------------------------------------------------------
// insert
//---------------------------------------------------------------------
void JSon::insert(Value &v, const char* pT, const int32_t &val)
{
	if (v.is_array())
		v.push_back(val);
	else
		v[pT] = val;
}

//---------------------------------------------------------------------
// insert
//---------------------------------------------------------------------
void JSon::insert(Value &v, const char* pT, const int64_t &val)
{
	if (v.is_array())
		v.push_back(val);
	else
		v[pT] = val;
}

//---------------------------------------------------------------------
// insert
//---------------------------------------------------------------------
void JSon::insert(Value &v, const char* pT, const uint16_t &val)
{
	if (v.is_array())
		v.push_back(val);
	else
		v[pT] = val;
}

//---------------------------------------------------------------------
// insert
//---------------------------------------------------------------------
void JSon::insert(Value &v, const char* pT, const uint32_t &val)
{
	if (v.is_array())
		v.push_back(val);
	else
		v[pT] = val;
}

//---------------------------------------------------------------------
// insert
//---------------------------------------------------------------------
void JSon::insert(Value &v, const char* pT, const uint64_t &val)
{
	if (v.is_array())
		v.push_back(val);
	else
		v[pT] = val;
}

//---------------------------------------------------------------------
// insert
//---------------------------------------------------------------------
void JSon::insert(Value &v, const char* pT, const bool &val)
{
	if (v.is_array())
		v.push_back(val);
	else
		v[pT] = val;
}

//---------------------------------------------------------------------
// insert
//---------------------------------------------------------------------
void JSon::insert(Value &v, const char* pT, const glm::vec2 &val)
{
	v[pT] = { val.x, val.y };
}

//---------------------------------------------------------------------
// insert
//---------------------------------------------------------------------
void JSon::insert(Value &v, const char* pT, const glm::vec3 &val)
{
	v[pT] = { val.x, val.y, val.z };
}

//---------------------------------------------------------------------
// insert
//---------------------------------------------------------------------
void JSon::insert(Value &v, const char* pT, const glm::vec4 &val)
{
	v[pT] = { val.x, val.y, val.z, val.w };
}

//---------------------------------------------------------------------
// insert
//---------------------------------------------------------------------
void JSon::insert(Value &v, const char* pT, const glm::quat &val)
{
	v[pT] = { val.x, val.y, val.z, val.w };
}

//---------------------------------------------------------------------
// insert
//---------------------------------------------------------------------
void JSon::insert(Value &v, const char* pT, const glm::ivec2 &val)
{
	v[pT] = { val.x, val.y };
}

//---------------------------------------------------------------------
// insert
//---------------------------------------------------------------------
void JSon::insert(Value &v, const char* pT, const glm::tvec2<unsigned short> &val)
{
	v[pT] = { val.x, val.y };
}

//---------------------------------------------------------------------
// insert
//---------------------------------------------------------------------
void JSon::insert(Value &v, const char* pT, const glm::tvec2<unsigned char> &val)
{
	v[pT] = { val.x, val.y };
}

//---------------------------------------------------------------------
// insert
//---------------------------------------------------------------------
void JSon::insert(Value &v, const char* pT, const glm::tvec2<signed char> &val)
{
	v[pT] = { val.x, val.y };
}

//---------------------------------------------------------------------
// insert
//---------------------------------------------------------------------
void JSon::insert(Value &v, const char* pT, const glm::tvec2<uint32_t> &val)
{
	v[pT] = { val.x, val.y };
}


//---------------------------------------------------------------------
// insert
//---------------------------------------------------------------------
void JSon::insert(Value &v, const char* pT, const glm::mat4 &val)
{
	v[pT] = { val[0][0], val[0][1], val[0][2], val[0][3],
						val[1][0], val[1][1], val[1][2], val[1][3],
						val[2][0], val[2][1], val[2][2], val[2][3],
						val[3][0], val[3][1], val[3][2], val[3][3]
	};
}


//---------------------------------------------------------------------
// insert
//---------------------------------------------------------------------
void JSon::insert(Value &v, const char* pT, const std::vector<int> &val)
{
	v[pT] = val;
}


//---------------------------------------------------------------------
// insert
//---------------------------------------------------------------------
void JSon::insert(Value &v, const char* pT, const std::vector<float> &val)
{
	v[pT] = val;
}


//---------------------------------------------------------------------
// read
//---------------------------------------------------------------------
int JSon::read(const char *pFP,Value &v)
{
int rc = -1;
std::ifstream file(pFP);

	if (file.is_open())
	{
		v = Value::parse(file);

    rc = 0;
	}

	return rc;
}


//---------------------------------------------------------------------
// read
//---------------------------------------------------------------------
int JSon::read(const std::string &filePath,Value &v)
{
int rc = read(filePath.c_str(),v);

	return rc;
}


//---------------------------------------------------------------------
// write
//---------------------------------------------------------------------
int JSon::write(const char *pFP,Value &v)
{
int rc = -1;
std::ofstream goodDest(pFP);

	if (goodDest)
	{
		// writing to file with nicer formating
		goodDest << std::setw(2) << v << std::endl;

    goodDest.close();

		rc = 0;
	}

	return rc;
}


//---------------------------------------------------------------------
// write
//---------------------------------------------------------------------
int JSon::write(const std::string &filePath,Value &v)
{
	int rc = write(filePath.c_str(),v);

	return rc;
}