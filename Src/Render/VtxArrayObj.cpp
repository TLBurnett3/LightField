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

// VtxArrayObj.cpp
// Thomas Burnett

#ifndef _GLES2

//---------------------------------------------------------------------
// Includes
// System
#include <float.h>

// Engine
#include "Render/VtxArrayObj.h"

using namespace Lf;
using namespace Render;
//---------------------------------------------------------------------



//---------------------------------------------------------------------
// upload 
// Thomas Burnett
// March 24, 2014
//---------------------------------------------------------------------
void  VtxArrayObj::upload(const VtxVLst &vLst,const IdxLst &iLst,const GLuint mode)
{
  if (vLst._vtxLst.size() && iLst.size())
  {
    if (!_idVAO)
      glGenVertexArrays(1,&_idVAO);

    assert(_idVAO);

    glBindVertexArray(_idVAO);

    if (!_idIBO)
      glGenBuffers(1,&_idIBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_idIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLZ) * iLst.size(),&iLst[0],_usage);

    if (!_idVBO)
      glGenBuffers(1,&_idVBO);

    glBindBuffer(GL_ARRAY_BUFFER,_idVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(VtxV) * vLst._vtxLst.size(),&vLst._vtxLst[0],_usage);

    glEnableVertexAttribArray(PositionAttribute);
    glVertexAttribPointer(PositionAttribute,3,GL_FLOAT,GL_FALSE,sizeof(glm::vec3),0);

    glBindVertexArray(0);

    _num  = (GLZ)iLst.size();
    _vMax = vLst.vMax();
    _vMin = vLst.vMin();
    _mode = mode;
  }
}



//---------------------------------------------------------------------
// upload 
// Thomas Burnett
// March 24, 2014
//---------------------------------------------------------------------
void  VtxArrayObj::upload(const VtxVTLst &vLst,const IdxLst &iLst,const GLuint mode)
{
  if (vLst._vtxLst.size() && iLst.size())
  {
    if (!_idVAO)
      glGenVertexArrays(1,&_idVAO);

    assert(_idVAO);

    glBindVertexArray(_idVAO);

    if (!_idIBO)
      glGenBuffers(1,&_idIBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_idIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLZ) * iLst.size(),&iLst[0],_usage);

    if (!_idVBO)
      glGenBuffers(1,&_idVBO);

    glBindBuffer(GL_ARRAY_BUFFER,_idVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(VtxVT) * vLst._vtxLst.size(),&vLst._vtxLst[0],_usage);

    glEnableVertexAttribArray(PositionAttribute);
    glVertexAttribPointer(PositionAttribute,3,GL_FLOAT,GL_FALSE,sizeof(glm::vec3),0);
 
    glEnableVertexAttribArray(TexCoordAttribute);  
    glVertexAttribPointer(TexCoordAttribute,2,GL_FLOAT,GL_FALSE,sizeof(VtxVNT),(void *)(sizeof(glm::vec3))); 

    glBindVertexArray(0);

    _num  = (GLZ)iLst.size();
    _vMax = vLst.vMax();
    _vMin = vLst.vMin();
    _mode = mode;
  }
}



//---------------------------------------------------------------------
// upload 
// Thomas Burnett
// March 24, 2014
//---------------------------------------------------------------------
void  VtxArrayObj::upload(const VtxVNLst &vLst,const IdxLst &iLst,const GLuint mode)
{
  if (vLst._vtxLst.size() && iLst.size())
  {
    if (!_idVAO)
      glGenVertexArrays(1,&_idVAO);

    assert(_idVAO);

    glBindVertexArray(_idVAO);

    if (!_idIBO)
      glGenBuffers(1,&_idIBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_idIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLZ) * iLst.size(),&iLst[0],_usage);

    if (!_idVBO)
      glGenBuffers(1,&_idVBO);

    glBindBuffer(GL_ARRAY_BUFFER,_idVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(VtxVN) * vLst._vtxLst.size(),&vLst._vtxLst[0],_usage);

    glEnableVertexAttribArray(PositionAttribute);
    glVertexAttribPointer(PositionAttribute,3,GL_FLOAT,GL_FALSE,sizeof(VtxVN),0);

    glEnableVertexAttribArray(NormalAttribute);  
    glVertexAttribPointer(NormalAttribute,3,GL_FLOAT,GL_FALSE,sizeof(VtxVN),(void *)sizeof(glm::vec3)); 
  
    glBindVertexArray(0);

    _num  = (GLZ)iLst.size();
    _vMax = vLst.vMax();
    _vMin = vLst.vMin();
    _mode = mode;
  }
}





//---------------------------------------------------------------------
// upload 
// Thomas Burnett
// March 24, 2014
//---------------------------------------------------------------------
void  VtxArrayObj::upload(const VtxVNTLst &vLst,const IdxLst &iLst,const GLuint mode)
{
  if (vLst._vtxLst.size() && iLst.size())
  {
    if (!_idVAO)
      glGenVertexArrays(1,&_idVAO);

    assert(_idVAO);

    glBindVertexArray(_idVAO);

    if (!_idIBO)
      glGenBuffers(1,&_idIBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_idIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLZ) * iLst.size(),&iLst[0],_usage);

    if (!_idVBO)
      glGenBuffers(1,&_idVBO);

    glBindBuffer(GL_ARRAY_BUFFER,_idVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(VtxVNT) * vLst._vtxLst.size(),&vLst._vtxLst[0],_usage);

    glEnableVertexAttribArray(PositionAttribute);
    glVertexAttribPointer(PositionAttribute,3,GL_FLOAT,GL_FALSE,sizeof(VtxVNT),0);

    glEnableVertexAttribArray(NormalAttribute);  
    glVertexAttribPointer(NormalAttribute,3,GL_FLOAT,GL_FALSE,sizeof(VtxVNT),(void *)sizeof(glm::vec3)); 

    glEnableVertexAttribArray(TexCoordAttribute);  
    glVertexAttribPointer(TexCoordAttribute,2,GL_FLOAT,GL_FALSE,sizeof(VtxVNT),(void *)(sizeof(glm::vec3) * 2)); 
  
    glBindVertexArray(0);

    _num  = (GLZ)iLst.size();
    _vMax = vLst.vMax();
    _vMin = vLst.vMin();
    _mode = mode;
  }
}




//---------------------------------------------------------------------
// upload 
// Thomas Burnett
// March 25, 2014
//---------------------------------------------------------------------
void  VtxArrayObj::upload(const VtxVTLst &vLst,const GLuint mode)
{
  if (vLst._vtxLst.size())
  {
    if (!_idVAO)
      glGenVertexArrays(1,&_idVAO);

    assert(_idVAO);

    glBindVertexArray(_idVAO);

    if (!_idVBO)
      glGenBuffers(1,&_idVBO);

    glBindBuffer(GL_ARRAY_BUFFER,_idVBO);

    glBufferData(GL_ARRAY_BUFFER,sizeof(VtxVT) * vLst._vtxLst.size(),&vLst._vtxLst[0]._V,_usage);

    glEnableVertexAttribArray(PositionAttribute);
    glVertexAttribPointer(PositionAttribute,3,GL_FLOAT,GL_FALSE,sizeof(VtxVT),0);

    glEnableVertexAttribArray(TexCoordAttribute);  
    glVertexAttribPointer(TexCoordAttribute,2,GL_FLOAT,GL_FALSE,sizeof(VtxVT),(void *)sizeof(glm::vec3)); 

    glBindVertexArray(0);

    _num  = (GLZ)vLst._vtxLst.size();
    _vMax = vLst.vMax();
    _vMin = vLst.vMin();
    _mode = mode;
  }
}


//---------------------------------------------------------------------
// upload 
// Thomas Burnett
// March 25, 2014
//---------------------------------------------------------------------
void  VtxArrayObj::upload(const VtxVNLst &vLst,const GLuint mode)
{
  if (vLst._vtxLst.size())
  {
    if (!_idVAO)
      glGenVertexArrays(1,&_idVAO);

    assert(_idVAO);

    glBindVertexArray(_idVAO);

    if (!_idVBO)
      glGenBuffers(1,&_idVBO);

    glBindBuffer(GL_ARRAY_BUFFER,_idVBO);

    glBufferData(GL_ARRAY_BUFFER,sizeof(VtxVN) * vLst._vtxLst.size(),&vLst._vtxLst[0]._V,_usage);

    glEnableVertexAttribArray(PositionAttribute);
    glVertexAttribPointer(PositionAttribute,3,GL_FLOAT,GL_FALSE,sizeof(VtxVN),0);

    glEnableVertexAttribArray(DimensionAttribute);  
    glVertexAttribPointer(DimensionAttribute,3,GL_FLOAT,GL_FALSE,sizeof(VtxVN),(void *)sizeof(glm::vec3)); 

    glBindVertexArray(0);

    _num  = (GLZ)vLst._vtxLst.size();
    _vMax = vLst.vMax();
    _vMin = vLst.vMin();
    _mode = mode;
  }
}


//---------------------------------------------------------------------
// upload 
// Thomas Burnett
// March 25, 2014
//---------------------------------------------------------------------
void  VtxArrayObj::upload(const VtxVLst &vLst,const GLuint mode)
{
  if (vLst._vtxLst.size())
  {
    if (!_idVAO)
      glGenVertexArrays(1,&_idVAO);

    assert(_idVAO);

    glBindVertexArray(_idVAO);

    if (!_idVBO)
      glGenBuffers(1,&_idVBO);

    glBindBuffer(GL_ARRAY_BUFFER,_idVBO);

    glBufferData(GL_ARRAY_BUFFER,sizeof(VtxVT) * vLst._vtxLst.size(),&vLst._vtxLst[0]._V,_usage);

    glEnableVertexAttribArray(PositionAttribute);
    glVertexAttribPointer(PositionAttribute,3,GL_FLOAT,GL_FALSE,sizeof(VtxVT),0);

    glBindVertexArray(0);

    _num  = (GLZ)vLst._vtxLst.size();
    _vMax = vLst.vMax();
    _vMin = vLst.vMin();
    _mode = mode;
  }
}

//---------------------------------------------------------------------
// upload 
// Thomas Burnett
// March 25, 2014
//---------------------------------------------------------------------
void  VtxArrayObj::upload(const VtxVNTLst &vLst,const GLuint mode)
{
  if (vLst._vtxLst.size())
  {
    if (!_idVAO)
      glGenVertexArrays(1,&_idVAO);

    assert(_idVAO);

    glBindVertexArray(_idVAO);

    if (!_idVBO)
      glGenBuffers(1,&_idVBO);

    glBindBuffer(GL_ARRAY_BUFFER,_idVBO);

    glBufferData(GL_ARRAY_BUFFER,sizeof(VtxVNT) * vLst._vtxLst.size(),&vLst._vtxLst[0]._V,_usage);

    glEnableVertexAttribArray(PositionAttribute);
    glVertexAttribPointer(PositionAttribute,3,GL_FLOAT,GL_FALSE,sizeof(VtxVNT),0);

    glEnableVertexAttribArray(NormalAttribute);  
    glVertexAttribPointer(NormalAttribute,3,GL_FLOAT,GL_FALSE,sizeof(VtxVNT),(void *)sizeof(glm::vec3)); 

    glEnableVertexAttribArray(TexCoordAttribute);  
    glVertexAttribPointer(TexCoordAttribute,2,GL_FLOAT,GL_FALSE,sizeof(VtxVNT),(void *)(sizeof(glm::vec3) * 2)); 
 
    glBindVertexArray(0);
    
    _num  = (GLZ)vLst._vtxLst.size();
    _vMax = vLst.vMax();
    _vMin = vLst.vMin();
    _mode = mode;
  }
}


//---------------------------------------------------------------------
// ~VtxArrayObj 
// Thomas Burnett
// March 25, 2014
//---------------------------------------------------------------------
VtxArrayObj::~VtxArrayObj() 
{
  if (_idVBO)
    glDeleteBuffers(1,&_idVBO);

  if (_idIBO)
    glDeleteBuffers(1,&_idIBO);

  if (_idVAO)
    glDeleteVertexArrays(1,&_idVAO);}


#endif