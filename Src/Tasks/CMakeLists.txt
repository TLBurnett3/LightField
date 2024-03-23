cmake_minimum_required (VERSION 3.6)

project(LfTasks)

include_directories(${CMAKE_INCLUDE_PATH})
include_directories(${3RDPARTY_INC_DIR})
include_directories(${LIGHTFIELD_SRC_DIR})

set (HEADERS
  Base.h
  ProofImage.h
  WriteAvi.h
  WriteImg.h
  SliceNDice.h
)

set(SOURCE
  Base.cpp
  ProofImage.cpp
  WriteAvi.cpp
  WriteImg.cpp
  SliceNDice.cpp
)

add_library(${PROJECT_NAME} SHARED ${HEADERS} ${SOURCE} )

target_link_libraries(${PROJECT_NAME} LfCore)
target_link_libraries(${PROJECT_NAME} ${OPENCV_DEBUG_LIB} ${OPENCV_RELEASE_LIB})

##########################################################################################################################################
# Installation
install (TARGETS ${PROJECT_NAME})
install (FILES   ${HEADERS}      DESTINATION include/LightField/Tasks)
##########################################################################################################################################
