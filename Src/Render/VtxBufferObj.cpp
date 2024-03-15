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

// VtxBufferObj.cpp
// Thomas Burnett


//---------------------------------------------------------------------
// Includes
// System
#include <float.h>

// Engine
#include "Render/VtxBufferObj.h"

using namespace Lf;
using namespace Render;
//---------------------------------------------------------------------



//---------------------------------------------------------------------
// renderIV
//---------------------------------------------------------------------
void VtxBufferObj::renderIV(void)
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_idIBO);
  glBindBuffer(GL_ARRAY_BUFFER,_idVBO);

  glEnableVertexAttribArray(PositionAttribute);
  glVertexAttribPointer(PositionAttribute,3,GL_FLOAT,GL_FALSE,sizeof(glm::vec3),0);

  glDrawElements(_mode,(GLsizei)_num,GLZ_TYPE,0);

  glDisableVertexAttribArray(PositionAttribute);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
  glBindBuffer(GL_ARRAY_BUFFER,0);
}


//---------------------------------------------------------------------
// upload 
// Thomas Burnett
// March 24, 2014
//---------------------------------------------------------------------
void  VtxBufferObj::upload(const VtxVLst &vLst,const IdxLst &iLst,const GLuint mode)
{
  if (vLst._vtxLst.size() && iLst.size())
  {
    if (!_idIBO)
      glGenBuffers(1,&_idIBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_idIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLZ) * iLst.size(),&iLst[0],_usage);

    if (!_idVBO)
      glGenBuffers(1,&_idVBO);

    glBindBuffer(GL_ARRAY_BUFFER,_idVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(VtxV) * vLst._vtxLst.size(),&vLst._vtxLst[0],_usage);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindBuffer(GL_ARRAY_BUFFER,0);

    _num          = (GLZ)iLst.size();
    _vMax         = vLst.vMax();
    _vMin         = vLst.vMin();
    _mode         = mode;
    _renderFunc   = &VtxBufferObj::renderIV;
  }
}



//---------------------------------------------------------------------
// renderIVT
//---------------------------------------------------------------------
void VtxBufferObj::renderIVT(void)
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_idIBO);
  glBindBuffer(GL_ARRAY_BUFFER,_idVBO);

  glEnableVertexAttribArray(PositionAttribute);
  glVertexAttribPointer(PositionAttribute,3,GL_FLOAT,GL_FALSE,sizeof(glm::vec3),0);
 
  glEnableVertexAttribArray(TexCoordAttribute);  
  glVertexAttribPointer(TexCoordAttribute,2,GL_FLOAT,GL_FALSE,sizeof(VtxVNT),(void *)(sizeof(glm::vec3))); 

  glDrawElements(_mode,(GLsizei)_num,GLZ_TYPE,0);

  glDisableVertexAttribArray(PositionAttribute);
  glDisableVertexAttribArray(TexCoordAttribute);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
  glBindBuffer(GL_ARRAY_BUFFER,0);
}



//---------------------------------------------------------------------
// upload 
// Thomas Burnett
// March 24, 2014
//---------------------------------------------------------------------
void  VtxBufferObj::upload(const VtxVTLst &vLst,const IdxLst &iLst,const GLuint mode)
{
  if (vLst._vtxLst.size() && iLst.size())
  {
    if (!_idIBO)
      glGenBuffers(1,&_idIBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_idIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLZ) * iLst.size(),&iLst[0],_usage);

    if (!_idVBO)
      glGenBuffers(1,&_idVBO);

    glBindBuffer(GL_ARRAY_BUFFER,_idVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(VtxVT) * vLst._vtxLst.size(),&vLst._vtxLst[0],_usage);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindBuffer(GL_ARRAY_BUFFER,0);

    _num            = (GLZ)iLst.size();
    _vMax           = vLst.vMax();
    _vMin           = vLst.vMin();
    _mode           = mode;
    _renderFunc     = &VtxBufferObj::renderIVT;
  }
}



//---------------------------------------------------------------------
// renderIVN
//---------------------------------------------------------------------
void VtxBufferObj::renderIVN(void)
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_idIBO);
  glBindBuffer(GL_ARRAY_BUFFER,_idVBO);

  glEnableVertexAttribArray(PositionAttribute);
  glVertexAttribPointer(PositionAttribute,3,GL_FLOAT,GL_FALSE,sizeof(VtxVN),0);

  glEnableVertexAttribArray(NormalAttribute);  
  glVertexAttribPointer(NormalAttribute,3,GL_FLOAT,GL_FALSE,sizeof(VtxVN),(void *)sizeof(glm::vec3));  

  glDrawElements(_mode,(GLsizei)_num,GLZ_TYPE,0);

  glDisableVertexAttribArray(PositionAttribute);
  glDisableVertexAttribArray(NormalAttribute);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
  glBindBuffer(GL_ARRAY_BUFFER,0);
}




//---------------------------------------------------------------------
// upload 
// Thomas Burnett
// March 24, 2014
//---------------------------------------------------------------------
void  VtxBufferObj::upload(const VtxVNLst &vLst,const IdxLst &iLst,const GLuint mode)
{
  if (vLst._vtxLst.size() && iLst.size())
  {
    if (!_idIBO)
      glGenBuffers(1,&_idIBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_idIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLZ) * iLst.size(),&iLst[0],_usage);

    if (!_idVBO)
      glGenBuffers(1,&_idVBO);

    glBindBuffer(GL_ARRAY_BUFFER,_idVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(VtxVN) * vLst._vtxLst.size(),&vLst._vtxLst[0],_usage);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindBuffer(GL_ARRAY_BUFFER,0);

    _num            = (GLZ)iLst.size();
    _vMax           = vLst.vMax();
    _vMin           = vLst.vMin();
    _mode           = mode;
    _renderFunc     = &VtxBufferObj::renderIVN;
  }
}



//---------------------------------------------------------------------
// renderIVN
//---------------------------------------------------------------------
void VtxBufferObj::renderIVNT(void)
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_idIBO);
  glBindBuffer(GL_ARRAY_BUFFER,_idVBO);

  glEnableVertexAttribArray(PositionAttribute);
  glVertexAttribPointer(PositionAttribute,3,GL_FLOAT,GL_FALSE,sizeof(VtxVNT),0);

  glEnableVertexAttribArray(NormalAttribute);  
  glVertexAttribPointer(NormalAttribute,3,GL_FLOAT,GL_FALSE,sizeof(VtxVNT),(void *)sizeof(glm::vec3)); 

  glEnableVertexAttribArray(TexCoordAttribute);  
  glVertexAttribPointer(TexCoordAttribute,2,GL_FLOAT,GL_FALSE,sizeof(VtxVNT),(void *)(sizeof(glm::vec3) * 2)); 

  glDrawElements(_mode,(GLsizei)_num,GLZ_TYPE,0);

  glDisableVertexAttribArray(PositionAttribute);
  glDisableVertexAttribArray(NormalAttribute);
  glDisableVertexAttribArray(TexCoordAttribute);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
  glBindBuffer(GL_ARRAY_BUFFER,0);
}



//---------------------------------------------------------------------
// upload 
// Thomas Burnett
// March 24, 2014
//---------------------------------------------------------------------
void  VtxBufferObj::upload(const VtxVNTLst &vLst,const IdxLst &iLst,const GLuint mode)
{
  if (vLst._vtxLst.size() && iLst.size())
  {
    if (!_idIBO)
      glGenBuffers(1,&_idIBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_idIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLZ) * iLst.size(),&iLst[0],_usage);

    if (!_idVBO)
      glGenBuffers(1,&_idVBO);

    glBindBuffer(GL_ARRAY_BUFFER,_idVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(VtxVNT) * vLst._vtxLst.size(),&vLst._vtxLst[0],_usage);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindBuffer(GL_ARRAY_BUFFER,0);

    _num            = (GLZ)iLst.size();
    _vMax           = vLst.vMax();
    _vMin           = vLst.vMin();
    _mode           = mode;
    _renderFunc     = &VtxBufferObj::renderIVNT;
  }
}




//---------------------------------------------------------------------
// renderVT
//---------------------------------------------------------------------
void VtxBufferObj::renderVT(void)
{
  glBindBuffer(GL_ARRAY_BUFFER,_idVBO);

  glEnableVertexAttribArray(PositionAttribute);
  glVertexAttribPointer(PositionAttribute,3,GL_FLOAT,GL_FALSE,sizeof(VtxVT),0);

  glEnableVertexAttribArray(TexCoordAttribute);  
  glVertexAttribPointer(TexCoordAttribute,2,GL_FLOAT,GL_FALSE,sizeof(VtxVT),(void *)sizeof(glm::vec3)); 

  glDrawArrays(_mode,0,(GLsizei)_num);

  glDisableVertexAttribArray(PositionAttribute);
  glDisableVertexAttribArray(TexCoordAttribute);

  glBindBuffer(GL_ARRAY_BUFFER,0);
}


//---------------------------------------------------------------------
// upload 
// Thomas Burnett
// March 25, 2014
//---------------------------------------------------------------------
void  VtxBufferObj::upload(const VtxVTLst &vLst,const GLuint mode)
{
  if (vLst._vtxLst.size())
  {
    if (!_idVBO)
      glGenBuffers(1,&_idVBO);

    glBindBuffer(GL_ARRAY_BUFFER,_idVBO);

    glBufferData(GL_ARRAY_BUFFER,sizeof(VtxVT) * vLst._vtxLst.size(),&vLst._vtxLst[0]._V,_usage);

    glBindBuffer(GL_ARRAY_BUFFER,0);

    _num            = (GLZ)vLst._vtxLst.size();
    _vMax           = vLst.vMax();
    _vMin           = vLst.vMin();
    _mode           = mode;
    _renderFunc     = &VtxBufferObj::renderVT;
  }
}


//---------------------------------------------------------------------
// renderVD
//---------------------------------------------------------------------
void VtxBufferObj::renderVD(void)
{
  glBindBuffer(GL_ARRAY_BUFFER,_idVBO);

  glEnableVertexAttribArray(PositionAttribute);
  glVertexAttribPointer(PositionAttribute,3,GL_FLOAT,GL_FALSE,sizeof(VtxVN),0);
 
  glEnableVertexAttribArray(DimensionAttribute);  
  glVertexAttribPointer(DimensionAttribute,3,GL_FLOAT,GL_FALSE,sizeof(VtxVN),(void *)sizeof(glm::vec3)); 

  glDrawArrays(_mode,0,(GLsizei)_num);

  glDisableVertexAttribArray(PositionAttribute);
  glDisableVertexAttribArray(DimensionAttribute);

  glBindBuffer(GL_ARRAY_BUFFER,0);
}


//---------------------------------------------------------------------
// upload 
// Thomas Burnett
// March 25, 2014
//---------------------------------------------------------------------
void  VtxBufferObj::upload(const VtxVNLst &vLst,const GLuint mode)
{
  if (vLst._vtxLst.size())
  {
    if (!_idVBO)
      glGenBuffers(1,&_idVBO);

    glBindBuffer(GL_ARRAY_BUFFER,_idVBO);

    glBufferData(GL_ARRAY_BUFFER,sizeof(VtxVN) * vLst._vtxLst.size(),&vLst._vtxLst[0]._V,_usage);

    glBindBuffer(GL_ARRAY_BUFFER,0);

    _num            = (GLZ)vLst._vtxLst.size();
    _vMax           = vLst.vMax();
    _vMin           = vLst.vMin();
    _mode           = mode;
    _renderFunc     = &VtxBufferObj::renderVD;
  }
}


//---------------------------------------------------------------------
// renderVD
//---------------------------------------------------------------------
void VtxBufferObj::renderV(void)
{
  glBindBuffer(GL_ARRAY_BUFFER,_idVBO);

  glEnableVertexAttribArray(PositionAttribute);
  glVertexAttribPointer(PositionAttribute,3,GL_FLOAT,GL_FALSE,sizeof(VtxVT),0);

  glDrawArrays(_mode,0,(GLsizei)_num);

  glDisableVertexAttribArray(PositionAttribute);

  glBindBuffer(GL_ARRAY_BUFFER,0);
}



//---------------------------------------------------------------------
// upload 
// Thomas Burnett
// March 25, 2014
//---------------------------------------------------------------------
void  VtxBufferObj::upload(const VtxVLst &vLst,const GLuint mode)
{
  if (vLst._vtxLst.size())
  {
    if (!_idVBO)
      glGenBuffers(1,&_idVBO);

    glBindBuffer(GL_ARRAY_BUFFER,_idVBO);

    glBufferData(GL_ARRAY_BUFFER,sizeof(VtxVT) * vLst._vtxLst.size(),&vLst._vtxLst[0]._V,_usage);

    glBindBuffer(GL_ARRAY_BUFFER,0);

    _num            = (GLZ)vLst._vtxLst.size();
    _vMax           = vLst.vMax();
    _vMin           = vLst.vMin();
    _mode           = mode;
    _renderFunc     = &VtxBufferObj::renderV; 
  }
}



//---------------------------------------------------------------------
// renderVT
//---------------------------------------------------------------------
void VtxBufferObj::renderVNT(void)
{
  glBindBuffer(GL_ARRAY_BUFFER,_idVBO);

  glEnableVertexAttribArray(PositionAttribute);
  glVertexAttribPointer(PositionAttribute,3,GL_FLOAT,GL_FALSE,sizeof(VtxVNT),0);

  glEnableVertexAttribArray(NormalAttribute);  
  glVertexAttribPointer(NormalAttribute,3,GL_FLOAT,GL_FALSE,sizeof(VtxVNT),(void *)sizeof(glm::vec3)); 

  glEnableVertexAttribArray(TexCoordAttribute);  
  glVertexAttribPointer(TexCoordAttribute,2,GL_FLOAT,GL_FALSE,sizeof(VtxVNT),(void *)(sizeof(glm::vec3) * 2)); 
  
  glDrawArrays(_mode,0,(GLsizei)_num);

  glDisableVertexAttribArray(PositionAttribute);
  glDisableVertexAttribArray(NormalAttribute);
  glDisableVertexAttribArray(TexCoordAttribute);

  glBindBuffer(GL_ARRAY_BUFFER,0);
}


//---------------------------------------------------------------------
// upload 
// Thomas Burnett
// March 25, 2014
//---------------------------------------------------------------------
void  VtxBufferObj::upload(const VtxVNTLst &vLst,const GLuint mode)
{
  if (vLst._vtxLst.size())
  {
    if (!_idVBO)
      glGenBuffers(1,&_idVBO);

    glBindBuffer(GL_ARRAY_BUFFER,_idVBO);

    glBufferData(GL_ARRAY_BUFFER,sizeof(VtxVNT) * vLst._vtxLst.size(),&vLst._vtxLst[0]._V,_usage);

    glBindBuffer(GL_ARRAY_BUFFER,0);

    _num            = (GLZ)vLst._vtxLst.size();
    _vMax           = vLst.vMax();
    _vMin           = vLst.vMin();
    _mode           = mode;
    _renderFunc     = &VtxBufferObj::renderVNT; 
  }
}


//---------------------------------------------------------------------
// ~VtxBufferObj 
// Thomas Burnett
// March 25, 2014
//---------------------------------------------------------------------
VtxBufferObj::~VtxBufferObj() 
{
  if (_idVBO)
    glDeleteBuffers(1,&_idVBO);

  if (_idIBO)
    glDeleteBuffers(1,&_idIBO);
}
