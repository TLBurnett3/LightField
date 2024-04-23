
cmake_minimum_required (VERSION 3.6)

project(MvPU)

include_directories(${CMAKE_INCLUDE_PATH})
include_directories(${3RDPARTY_INC_DIR})
include_directories(${LIGHTFIELD_SRC_DIR})

link_directories(${CMAKE_LIBRARY_PATH})

set(HEADERS
  Job.h
  BowTie.h
  DoubleFrustum.h
  Executor.h
)

set(SOURCE
  Job.cpp
  BowTie.cpp
  DoubleFrustum.cpp
  Executor.cpp
  Main.cpp
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCE})

target_link_libraries(${PROJECT_NAME} LfCore)
target_link_libraries(${PROJECT_NAME} LfHogelDef)
target_link_libraries(${PROJECT_NAME} LfRenderCPP)
target_link_libraries(${PROJECT_NAME} ${OPENCV_DEBUG_LIB} ${OPENCV_RELEASE_LIB})

install (TARGETS ${PROJECT_NAME})
