cmake_minimum_required (VERSION 3.6)

project(LfRenderCPP)

include_directories(${CMAKE_INCLUDE_PATH})
include_directories(${3RDPARTY_INC_DIR})
include_directories(${LIGHTFIELD_SRC_DIR})


link_directories(${CMAKE_LIBRARY_PATH})

set(HEADERS
  Vtx.h
  VtxObj.h
  VtxLstObj.h
  VtxIdxLstObj.h
  VtxMeshObj.h
  TxtObj.h
  LgtObj.h
  Mesh.h
  Node.h
  Model.h
  Shader.h
  FrameBuffer.h
  Clipper.h
  BtClipper.h
  BtShader.h
  BtBasicShader.h
  BtIntMapShader.h
  Scene.h
)

set(SOURCE
  Vtx.cpp
  VtxLstObj.cpp
  VtxIdxLstObj.cpp
  VtxMeshObj.cpp
  Mesh.cpp
  Node.cpp
  Model.cpp
  Shader.cpp
  BtShader.cpp
  FrameBuffer.cpp
  Clipper.cpp
  BtClipper.cpp
  BtShader.cpp
  BtBasicShader.cpp
  BtIntMapShader.cpp
  Scene.cpp
  )

add_library(${PROJECT_NAME} ${HEADERS} ${SOURCE})

target_link_libraries(${PROJECT_NAME} LfCore)
target_link_libraries(${PROJECT_NAME} LfHogelDef)
target_link_libraries(${PROJECT_NAME} ${ASSIMP_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${OPENCV_DEBUG_LIB} ${OPENCV_RELEASE_LIB})

