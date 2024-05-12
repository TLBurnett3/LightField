cmake_minimum_required (VERSION 3.6)

project(LfRadImg)

include_directories(${CMAKE_INCLUDE_PATH})
include_directories(${3RDPARTY_INC_DIR})
include_directories(${LIGHTFIELD_SRC_DIR})


link_directories(${CMAKE_LIBRARY_PATH})

set(HEADERS
  Image.h
  MultCamImage.h
  PlenOptImage.h
  ImageSet.h
  MultCamImageSet.h
  PlenOptImageSet.h
  EPIHorImageSet.h
  EPIVerImageSet.h
  )

set(SOURCE
  Image.cpp
  MultCamImage.cpp
  PlenOptImage.cpp
  ImageSet.cpp
  MultCamImageSet.cpp
  PlenOptImageSet.cpp
  EPIHorImageSet.cpp
  EPIVerImageSet.cpp
  )

add_library(${PROJECT_NAME} ${HEADERS} ${SOURCE})

target_link_libraries(${PROJECT_NAME} LfCore)
target_link_libraries(${PROJECT_NAME} ${OPENCV_DEBUG_LIB} ${OPENCV_RELEASE_LIB})

