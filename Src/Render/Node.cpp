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
// Node.cpp


//---------------------------------------------------------------------
// Includes
#include <assert.h>


#include "Render/Node.h"

using namespace Lf;
using namespace Render;
//---------------------------------------------------------------------



//---------------------------------------------------------------------
// printMatrix
//---------------------------------------------------------------------
void Node::printMatrix(std::ostream &s,std::string idt,const char *str,const glm::mat4 &m)
{
  s << idt << str << std::endl;
  s << idt << " " << m[0].x << " " << m[0].y << " " << m[0].z << " " << m[0].w << std::endl; 
  s << idt << " " << m[1].x << " " << m[1].y << " " << m[1].z << " " << m[1].w << std::endl; 
  s << idt << " " << m[2].x << " " << m[2].y << " " << m[2].z << " " << m[2].w << std::endl; 
  s << idt << " " << m[3].x << " " << m[3].y << " " << m[3].z << " " << m[3].w << std::endl; 
}


//---------------------------------------------------------------------
// print
//---------------------------------------------------------------------
void Node::print(std::ostream &s,std::string idt)
{
  idt += "  ";

  s << idt << "Node: " << _sName << std::endl;

  idt += "  ";

  printMatrix(s,idt,"Transform Matrix:",_mT);

  s << idt << "Num Meshes: " << _meshLst.size() << std::endl;
  for (size_t i = 0;i < _meshLst.size();i++)
    _meshLst[i]->print(s,idt);

  s << idt << "Num Nodes: " << _nodeLst.size() << std::endl;
  for (size_t i = 0;i < _nodeLst.size();i++)
    _nodeLst[i]->print(s,idt);
}


//---------------------------------------------------------------------
// render
//---------------------------------------------------------------------
void Node::render(const Camera &camera,const glm::mat4 &mT)
{
bool      visible(true);

  //if (control.state(Control::FrustumCulling))
  //{
 // glm::vec3 vC = glm::vec3(mT * glm::vec4(_vCen,1));

 //   visible = camera.isVisible(vC,_radius); 
 // }

 // printf("%s\n",visible ? "true" : "false");

  if (visible)
  {
  glm::mat4 m = mT * _mT;

    // Meshes
    {
    MeshLst::iterator  ii    = _meshLst.begin();
    MeshLst::iterator  iEnd  = _meshLst.end();

      while (ii < iEnd)
      {
        (*ii)->render(camera,m);

        ii++;
      }
    }

    // Nodes
    {
    NodeList::iterator  ii    = _nodeLst.begin();
    NodeList::iterator  iEnd  = _nodeLst.end();

      while (ii < iEnd)
      {
        (*ii)->render(camera,m);

        ii++;
      }
    }
  }
}

//---------------------------------------------------------------------
// Node
//---------------------------------------------------------------------
Node::Node(void) : _sName(),
                   _mT(),
                   _meshLst(),
                   _nodeLst()
{
 
}


//---------------------------------------------------------------------
// ~Node
//---------------------------------------------------------------------
Node::~Node(void)
{
  while (!_nodeLst.empty())
  {
    delete _nodeLst.back();
    _nodeLst.pop_back();
  }
}





