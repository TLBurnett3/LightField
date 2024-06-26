cmake_minimum_required (VERSION 3.6)

project(LfRenderGL)

include_directories(${CMAKE_INCLUDE_PATH})
include_directories(${3RDPARTY_INC_DIR})
include_directories(${LIGHTFIELD_SRC_DIR})

set (HEADERS
  Def.h
  Object.h
  Bound.h
  Texture.h
  VtxLst.h
  Mesh.h
  Node.h
  Model.h
  VtxArrayObj.h
  VtxBufferObj.h
  Shader.h
  Shader.h
  BasicShader.h
  PhongShader.h
  Scene.h
  )

set(SOURCE
  Texture.cpp
  VtxLst.cpp
  Mesh.cpp
  Node.cpp
  Model.cpp
  VtxArrayObj.cpp
  VtxBufferObj.cpp
  Shader.cpp
  BasicShader.cpp
  PhongShader.cpp
  Scene.cpp
  )

add_library(${PROJECT_NAME} SHARED ${HEADERS} ${SOURCE} )

target_link_libraries(${PROJECT_NAME} LfCore)
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${ASSIMP_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${OPENCV_DEBUG_LIB} ${OPENCV_RELEASE_LIB})


##########################################################################################################################################
# Installation
install (TARGETS ${PROJECT_NAME})
install (FILES   ${HEADERS}      DESTINATION include/LightField/RenderGL)
##########################################################################################################################################
