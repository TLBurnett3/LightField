cmake_minimum_required (VERSION 3.6)

project(LfCore)

include_directories(${CMAKE_INCLUDE_PATH})
include_directories(${3RDPARTY_INC_DIR})
include_directories(${LIGHTFIELD_SRC_DIR})

set (HEADERS
  Export.h  
  Camera.h
  Barycentric.h
  Thread.h
  JSon.h
  Job.h
  Timer.h
  Template.h
)

set(SOURCE
  JSon.cpp
  Job.cpp
  Template.cpp
)

add_library(${PROJECT_NAME} SHARED ${HEADERS} ${SOURCE} )


##########################################################################################################################################
# Installation
install (TARGETS ${PROJECT_NAME})
install (FILES   ${HEADERS}      DESTINATION include/LightField/Core)
##########################################################################################################################################
