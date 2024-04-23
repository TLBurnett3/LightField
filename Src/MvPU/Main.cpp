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
// Main.cpp 

//---------------------------------------------------------------------
// Includes
#include <string>
#include <iostream>

// 3rd Party Libs

// Lightfield
#include "MvPU/DoubleFrustum.h"
#include "MvPU/BowTie.h"

//---------------------------------------------------------------------


//---------------------------------------------------------------------
// main
//---------------------------------------------------------------------
int main(int argc,char *argv[])
{
int               rc    = 0;
char              *p    = "Cfg/Default.json";
Lf::MvPU::SpJob   spJob = std::make_shared<Lf::MvPU::Job>();

  if (argc > 1)
    p = argv[1];
    
  std::cout << "MvPU Initialization\n";

  std::cout << "Parsing job file: " << p << std::endl;

  rc = spJob->parse(std::filesystem::path(p));

  std::cout << "Job file parsed: " << ((rc == 0) ? "Successful" : "Failed") << std::endl;

  if (rc == 0)
  {
  MvPU::Executor *pE = 0;

    spJob->print(std::cout);

    if (spJob->renderType() == Lf::Core::Job::DoubleFrustum)
      pE = new MvPU::DoubleFrustum();
    else if (spJob->renderType() == Lf::MvPU::Job::BowTie)
      pE = new MvPU::BowTie();

    if (pE)
    {
      rc = pE->init(spJob);

      if (rc == 0)
        rc = pE->exec();

      if (rc == 0)
        pE->record();

      if (rc == 0)
        rc = pE->process();

      pE->destroy();
    }
  }

  std::cout << "MvPU Exit: RC " << rc << std::endl;

  return rc;
}

