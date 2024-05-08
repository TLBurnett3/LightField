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

// Executor.cpp 
// Thomas Burnett

//---------------------------------------------------------------------
// Includes
// System
#include <string>
#include <iostream>
#include <stdio.h>

// 3rdPartyLibs
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <opencv2/imgproc.hpp>

// Lightfield

#include "MvPU/Executor.h"
#include "Core/Timer.h"

using namespace MvPU;
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// process
//---------------------------------------------------------------------
int Executor::process(void)
{
int                   rc      = 0;
int                   fourcc  = cv::VideoWriter::fourcc('M','P','4','3');
glm::ivec2            nH      = _spJob->numHogels();
glm::ivec2            hS      = _spJob->hogelSize();
std::filesystem::path dirPath = _spJob->outputPath();
std::filesystem::path aviPath = dirPath;
std::filesystem::path pngPath = dirPath;
glm::ivec2            cIdx    = hS >> 1;
uint32_t              cI      = (cIdx.y * hS.x) + cIdx.x;
glm::ivec2            idx(0);
size_t                i(0);
cv::Mat               *pProofImg(0);
cv::Mat               *pProofDth(0);

  std::cout << "Processing framebuffers" << std::endl;

  if (!dirPath.empty() && !std::filesystem::exists(dirPath))
    std::filesystem::create_directory(dirPath);

  if (_spJob->isTask(Lf::Core::Job::ProofImage))
  {
  cv::Scalar clr = cv::Scalar(255,221,244); // pink lace

    pProofImg = new cv::Mat(nH.y,nH.x,CV_8UC3);
    pProofImg->setTo(clr);
  }

  if (_spJob->isTask(Lf::Core::Job::ProofDepth))
  {
  cv::Scalar clr = cv::Scalar(0); 

    pProofDth = new cv::Mat(nH.y,nH.x,CV_32FC1);
    pProofDth->setTo(clr);
  }

  if (_spJob->isTask(Lf::Core::Job::WriteAvi))
  {
    aviPath /= "HogelAvi";

    if (!aviPath.empty() && !std::filesystem::exists(aviPath))
      std::filesystem::create_directory(aviPath);
  }

  if (_spJob->isTask(Lf::Core::Job::WriteImg))
  {
    pngPath /= "HogelImg";

    if (!pngPath.empty() && !std::filesystem::exists(pngPath))
      std::filesystem::create_directory(pngPath);
  }

  if (_spJob->isTask(Lf::Core::Job::ProofImage) || 
      _spJob->isTask(Lf::Core::Job::ProofDepth) || 
      _spJob->isTask(Lf::Core::Job::WriteImg)   ||
      _spJob->isTask(Lf::Core::Job::WriteAvi))
  {
    for (idx.y = 0;idx.y < nH.y;idx.y++)
    {
    cv::VideoWriter *pVideoWriter  = 0;

      if (_spJob->isTask(Lf::Core::Job::WriteAvi))
      {
      std::filesystem::path   fPath  = aviPath;
      char                    buf[32];

        sprintf(buf,"HogelRow_%d.avi",idx.y);
        fPath /= buf;

        pVideoWriter = new cv::VideoWriter();

        pVideoWriter->open(fPath.string().c_str(),fourcc,60,cv::Size(hS.x,hS.y),true);
      }

      for (idx.x = 0;idx.x < nH.x;idx.x++)
      {
      cv::Mat img;
      cv::Mat dth;
      cv::Mat rgb;

        _pFrameBuffer->getFrameBuffer(i,img,dth);

        cv::flip(img,img,0);

        if (pProofImg)
        {
        uint8_t *pS = img.ptr()         + (cI * 4);
        uint8_t *pD = pProofImg->ptr()  + (((idx.y * pProofImg->cols) + idx.x) * 3);

          *(pD + 0) = *(pS + 0);
          *(pD + 1) = *(pS + 1);
          *(pD + 2) = *(pS + 2);
        }

        if (pProofDth)
        {
        float *pS = (float *)img.ptr()         + cI;
        float *pD = (float *)pProofImg->ptr()  + cI;

          *pD = *pS;
        }

        if (_spJob->isTask(Lf::Core::Job::WriteImg) || (pVideoWriter && pVideoWriter->isOpened()))
          cv::cvtColor(img,rgb,cv::COLOR_RGBA2RGB);

        if (_spJob->isTask(Lf::Core::Job::WriteImg))
        {
        std::filesystem::path   fPath  = pngPath;
        char                    buf[64];

          sprintf(buf,"Hogel_%dx%d.png",idx.y,idx.x);
          fPath /= buf;

          cv::imwrite(fPath.string(),rgb);
        }

        if (pVideoWriter && pVideoWriter->isOpened())
          (*pVideoWriter) << rgb;

        i++;
      }

      if (pVideoWriter && pVideoWriter->isOpened())
      {
        pVideoWriter->release();
        delete pVideoWriter;
      }

      if (pProofImg)
      {
      std::filesystem::path filePath = dirPath;

        filePath /= _name;
        filePath += "ProofImg.png";

        cv::imwrite(filePath.string(),*pProofImg);
      }

      if (pProofDth)
      {
      std::filesystem::path filePath = dirPath;

        filePath /= _name;
        filePath += "ProofDth.png";

   //     cv::imwrite(filePath.string(),*pProofDth);
      }

      std::cout << ".";
    }
  }

  std::cout << std::endl;

  delete pProofImg;
  delete pProofDth;

  return rc;
}


//---------------------------------------------------------------------
// createHogelPlane
//---------------------------------------------------------------------
int Executor::createHogelPlane(void)
{
int         rc    = 0;
glm::ivec2  nH    = _spJob->numHogels();
glm::ivec2  hS    = _spJob->hogelSize();
float       fov   = _spJob->fov();


  _pHogelPlane = new Lf::HogelDef::Plane();

  _pHogelPlane->create(nH,hS,hS,fov);

  return rc;
}


//---------------------------------------------------------------------
// loadModels
//---------------------------------------------------------------------
int Executor::loadModels(std::filesystem::path &cPath)
{
int rc = 0;

  _pScene = new Lf::RenderCPP::Scene();

  if (_pScene)
  {
    rc =_pScene->init(cPath);

    for (size_t i = 0;i < _spJob->numModels();i++)
    {
      if (_pScene->load(_spJob->modelPath(i),_spJob->modelTransform(i)) == 0)
        std::cout << "Successful Load: " << _spJob->modelPath(i) << std::endl;
      else
      {
        std::cout << "Unsuccessful Load: " << _spJob->modelPath(i) << std::endl;
        rc |= -1;
      }
    }   
  }

  return rc;
}


//---------------------------------------------------------------------
// createFrameBuffer
//---------------------------------------------------------------------
int Executor::createFrameBuffer(void) 
{
int   rc = -1;

  _pFrameBuffer = new Lf::RenderCPP::FrameBuffer();

  {
  glm::ivec2  nH    = _spJob->numHogels();
  glm::ivec2  hS    = _spJob->hogelSize();
  uint64_t    fbMem = _spJob->memSize();
  uint64_t    iMem  = (uint64_t)nH.x * (uint64_t)nH.y * (uint64_t)hS.x * (uint64_t)hS.y * 4;
  uint64_t    dMem  = (uint64_t)nH.x * (uint64_t)nH.y * (uint64_t)hS.x * (uint64_t)hS.y * 4;

    if ((iMem + dMem) < (fbMem * 1024 * 1024 * 1024))
      rc = _pFrameBuffer->create(nH,hS);
    else
    {
      std::cout << "FrameBuffer Error" << std::endl;
      std::cout << "      Required memory for framebuffer: " << (iMem + dMem) << std::endl;
      std::cout << "Exceeded configured framebuffer limit: " << fbMem << " gigabytes" << std::endl;
      std::cout << "Increase framebuffer memory limit or decrease hogel number and size" << std::endl;
    }
  }

  return rc;
}


//---------------------------------------------------------------------
// record
//---------------------------------------------------------------------
void Executor::record(void) 
{
FILE *fp = fopen("MvPU.txt","a");

  if (fp)
  {
  glm::ivec2 hS = _spJob->hogelSize();
  glm::ivec2 nH = _spJob->numHogels();

    fprintf(fp,"%-30s",_spJob->jobName().c_str());
    fprintf(fp,"\tFoV: %.2f",_spJob->fov());
    fprintf(fp,"\thS: %dx%d",hS.y,hS.x);
    fprintf(fp,"\tnH: %dx%d",nH.y,nH.x);
    fprintf(fp,"\t%-6s",_name.c_str());
    fprintf(fp,"\t%-10s",_spJob->algorithm().c_str());
    fprintf(fp,"\trT:%.3f",_rSec);
    fprintf(fp,"\tfps:%.3f",_rFps);
    fprintf(fp,"\n");

    fclose(fp);
  }
}


//---------------------------------------------------------------------
// init
//---------------------------------------------------------------------
int Executor::init(Lf::MvPU::SpJob &spJob) 
{
int   rc = -1;

  _spJob = spJob;

  {
  std::filesystem::path cPath = std::filesystem::current_path();

    {
    std::filesystem::path outPath = _spJob->outputPath();

      if (!outPath.empty() && !std::filesystem::exists(outPath))
        std::filesystem::create_directories(outPath);
    }

    rc = loadModels(cPath);

    if (rc == 0)
      rc = createHogelPlane();

    if (rc == 0)
      rc = createFrameBuffer();
  }

  return rc;
}


//---------------------------------------------------------------------
// destroy
//---------------------------------------------------------------------
void Executor::destroy(void) 
{
  if (_pScene)
  {
    _pScene->clear();

    delete _pScene;
  }

  delete _pFrameBuffer;
  delete _pHogelPlane;
}


//---------------------------------------------------------------------
// Executor
//---------------------------------------------------------------------
Executor::Executor(void) : _spJob(),
                           _name(),
                           _pScene(0),
                           _pHogelPlane(0),
                           _pFrameBuffer(0),
                           _rSec(0),
                           _rFps(0)
{
}


//---------------------------------------------------------------------
// ~Executor
//---------------------------------------------------------------------
Executor::~Executor()
{

}

