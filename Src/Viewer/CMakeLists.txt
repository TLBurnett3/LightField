
cmake_minimum_required (VERSION 3.6)

project(LfViewer)

include_directories(${CMAKE_INCLUDE_PATH})
include_directories(${3RDPARTY_INC_DIR})
include_directories(${LIGHTFIELD_SRC_DIR})

link_directories(${CMAKE_LIBRARY_PATH})

set(HEADERS
  RadImage.h
  Executor.h
)

set(SOURCE
  RadImage.cpp
  Executor.cpp
  Main.cpp
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCE})

target_link_libraries(${PROJECT_NAME} LfCore)
target_link_libraries(${PROJECT_NAME} LfRender)
target_link_libraries(${PROJECT_NAME} ${GLFW3_RELEASE_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${OPENCV_DEBUG_LIB} ${OPENCV_RELEASE_LIB})

if (WIN32)
  target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})
endif (WIN32)

install (TARGETS ${PROJECT_NAME})
