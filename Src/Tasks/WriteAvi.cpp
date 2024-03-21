// WriteAvi.cpp 
// Thomas Burnett
// November 24, 2014


//---------------------------------------------------------------------
// Includes
// System
#include <filesystem>

// 3rdPartyLibs

// LightField
#include "Tasks/WriteAvi.h"

using namespace Lf;
using namespace Task;
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// open
//---------------------------------------------------------------------
int WriteAvi::open(cv::Mat &img,const glm::ivec2 &idx)
{
int                     rc     = 0;
std::filesystem::path   fPath  = _dPath;
int                     fourcc = cv::VideoWriter::fourcc('M','P','4','3');
cv::Size                sz(img.cols,img.rows);
char                    buf[16];

  sprintf_s(buf,"_%d.avi",idx.y);
  
  fPath /= _fName;
  fPath += buf;

  _videoWriter.open(fPath.string().c_str(),fourcc,60,sz,true);

  if (!_videoWriter.isOpened())
  {
    std::cout << "Failed to open: " << fPath << std::endl;

    rc = -1;
  }

  return rc;
}


//---------------------------------------------------------------------
// process()
//---------------------------------------------------------------------
void WriteAvi::process(cv::Mat &img,glm::ivec2 &idx)
{
  if (idx.x == 0)
  {
    if (isOpen())
      close();

    open(img,idx);
  }

  if (img.data)
  {
    if (_videoWriter.isOpened())
      _videoWriter << img;
  }
}
