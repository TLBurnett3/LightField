
cmake_minimum_required (VERSION 3.6)

project(LightField)

include_directories(${CMAKE_INCLUDE_PATH})
include_directories(${3RDPARTY_INC_DIR})
include_directories(${LIGHTFIELD_SRC_DIR})

link_directories(${CMAKE_LIBRARY_PATH})

set(HEADERS
  Executor.h
)

set(SOURCE
  Executor.cpp
  Main.cpp
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCE})

target_link_libraries(${PROJECT_NAME} LfCore)
target_link_libraries(${PROJECT_NAME} ${GLFW3_DEBUG_LIBRARY} ${GLFW3_RELEASE_LIBRARY})

install (TARGETS ${PROJECT_NAME})
