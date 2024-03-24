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
// Mesh.cpp


//---------------------------------------------------------------------
// Includes
// System
#include <assert.h>

//3rdPartyLibs

// RenderEngine

#include "Render/Mesh.h"
//#include "Common/Light.h"

using namespace Lf;
using namespace Render;
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// Globals
//extern Common::LightLst         lightLst;
//---------------------------------------------------------------------



//---------------------------------------------------------------------
// render
//---------------------------------------------------------------------
void Mesh::render(const Camera &camera,const Shader &shader,const glm::mat4 &mT)
{
bool      visible(true);
  
 // if (control.state(Control::FrustumCulling))
 // {
//  glm::vec3 vC = glm::vec3(mT * glm::vec4(_vCen,1));

 //   visible = camera.isVisible(vC,_radius); 
 // }

  if (visible)
  {
  glm::mat4   mMV   = camera.view() * mT;
  glm::mat4   mMVP  = camera.projection() * mMV;
  glm::mat3   mN    = glm::inverseTranspose(glm::mat3(mMV));

    shader.bindMVP(mMVP);
    shader.bindMV(mMV);
    shader.bindN(mN);
  //  shader.bindMaterial(_pTexture->properties());

    _pTexture->bind();
    _pObject->render();
  }
}


//---------------------------------------------------------------------
// print
//---------------------------------------------------------------------
void Mesh::print(std::ostream &s,std::string idt,bool detail)
{
char  buf[256];

const char  *p  = "Triangles";
 
  sprintf_s(buf,"%20s: %-12s","Mesh",_mName.c_str());
  s << idt << buf << std::endl;

  sprintf_s(buf,"%22s %-12s: %-10d","",p,_numFaces);
  s << idt << buf << std::endl;

  sprintf_s(buf,"%22s %-12s: %-10d","","Vertices",_numVertices);
  s << idt << buf << std::endl;

  sprintf_s(buf,"%22s %-12s: %-10d","","Normals",_numNormals);
  s << idt << buf << std::endl;

  sprintf_s(buf,"%22s %-12s: %-10d","","TexCoords",_numTexCoords);
  s << idt << buf << std::endl;

  sprintf_s(buf,"%22s %-12s: (%f,%f,%f)","","vMin",vMin().x,vMin().y,vMin().z);
  s << idt << buf << std::endl;

  sprintf_s(buf,"%22s %-12s: (%f,%f,%f)","","vMax",vMax().x,vMax().y,vMax().z);
  s << idt << buf << std::endl;

  sprintf_s(buf,"%22s %-12s: (%f,%f,%f)","","vCen",cen().x,cen().y,cen().z);
  s << idt << buf << std::endl;

  sprintf_s(buf,"%22s %-12s: %f","","Radius",radius());
  s << idt << buf << std::endl;

 // if (detail)
//    _pMaterial->print(s,idt,detail);

  s << idt <<std::endl;
}


//---------------------------------------------------------------------
// Mesh
//---------------------------------------------------------------------
Mesh::Mesh(void) : Bound(),
                   _pTexture(0),
                   _pObject(0),
                   _mName(),
                   _numFaces(0),
                   _numVertices(0),
                   _numNormals(0),
                   _numTexCoords(0)
{
 
}


//---------------------------------------------------------------------
// ~Mesh
//---------------------------------------------------------------------
Mesh::~Mesh(void)
{
  if (_pObject)
    delete _pObject;
}



















