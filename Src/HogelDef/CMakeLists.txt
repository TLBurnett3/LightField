cmake_minimum_required (VERSION 3.6)

project(LfHogelDef)

include_directories(${CMAKE_INCLUDE_PATH})
include_directories(${3RDPARTY_INC_DIR})
include_directories(${LIGHTFIELD_SRC_DIR})

set(HEADERS
  Hogel.h
  Plane.h
  Camera.h
)

set(SOURCE
  Plane.cpp
)

add_library(${PROJECT_NAME} ${HEADERS} ${SOURCE})


##########################################################################################################################################
# Installation
install (TARGETS ${PROJECT_NAME})
install (FILES   ${HEADERS}      DESTINATION include/LightField/HogelDef)
##########################################################################################################################################
