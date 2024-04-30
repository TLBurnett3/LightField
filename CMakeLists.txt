cmake_minimum_required(VERSION 3.26)

set (CMAKE_GENERATOR_PLATFORM x64)

project(LightField)

##############################################################################################
# Variables

set (LIGHTFIELD_VERSION_MAJOR      1)
set (LIGHTFIELD_VERSION_MINOR      2)
set (LIGHTFIELD_VERSION_PATCH      0)

set (LIGHTFIELD_SRC_DIR        ${CMAKE_CURRENT_SOURCE_DIR}/Src)
set (LIGHTFIELD_MODEL_DIR      ${CMAKE_CURRENT_SOURCE_DIR}/Models)
set (LIGHTFIELD_SHADER_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/Shaders)

if (WIN32)
set (3RDPARTY_BASE_DIR          /3rdPartyLibs)
else (WIN32)
set (3RDPARTY_BASE_DIR          /usr/local)
endif (WIN32)


set (3RDPARTY_INC_DIR          ${3RDPARTY_BASE_DIR}/include)
set (3RDPARTY_BIN_DIR          ${3RDPARTY_BASE_DIR}/bin)
set (3RDPARTY_LIB_DIR          ${3RDPARTY_BASE_DIR}/lib)


if (WIN32)
  set (CMAKE_INSTALL_PREFIX   /TLB3)
endif (WIN32)


set (CMAKE_DEBUG_POSTFIX      d)
set (CMAKE_CXX_STANDARD       17)

set (CMAKE_MODULE_PATH        ${CMAKE_INSTALL_PREFIX}
                              ${CMAKE_INSTALL_PREFIX}/cmake
                              ${CMAKE_INSTALL_PREFIX}/lib/cmake
                              )

set (CMAKE_PREFIX_PATH        ${CMAKE_INSTALL_PREFIX}
                              ${CMAKE_INSTALL_PREFIX}/cmake
                              ${CMAKE_INSTALL_PREFIX}/lib/cmake
                              )

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY			         ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DIR_RELEASE	           ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release)
set (CMAKE_RUNTIME_OUTPUT_DIR_DEBUG			         ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)
set (CMAKE_RUNTIME_OUTPUT_DIR_RELWITHDEBINFO		 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/RelWithDebInfo)

if (UNIX)
  set(CMAKE_C_COMPILER                      /usr/bin/gcc-8 CACHE PATH "" FORCE)
  set(CMAKE_CXX_COMPILER                    /usr/bin/g++-8 CACHE PATH "" FORCE)
  set(CMAKE_CXX_FLAGS                       "-fPIC")
  set(CMAKE_CXX_FLAGS_DEBUG                 "-g")
  set(CMAKE_CXX_FLAGS_RELEASE               "-O3")  
endif (UNIX)

##############################################################################################


##############################################################################################
# Messages
message("")
message(" 3RDPARTY_INC_DIR:   "          ${3RDPARTY_INC_DIR})
message(" 3RDPARTY_BIN_DIR:   "          ${3RDPARTY_BIN_DIR})
message(" 3RDPARTY_LIB_DIR:   "          ${3RDPARTY_LIB_DIR})
message("CMAKE_MODULE_PATH:   "          ${CMAKE_MODULE_PATH})
message("CMAKE_PREFIX_PATH:   "          ${CMAKE_PREFIX_PATH})
message("")
message("   CMAKE_RUNTIME_OUTPUT_DIRECTORY:   " ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
message("   CMAKE_LIBRARY_OUTPUT_DIRECTORY:   " ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
message("   CMAKE_ARCHIVE_OUTPUT_DIRECTORY:   " ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
message("   CMAKE_RUNTIME_OUTPUT_DIR_DEBUG:   " ${CMAKE_RUNTIME_OUTPUT_DIR_DEBUG})
message(" CMAKE_RUNTIME_OUTPUT_DIR_RELEASE:   " ${CMAKE_RUNTIME_OUTPUT_DIR_RELEASE})
message("")
##############################################################################################


##############################################################################################
# Includes
include (CMake/Config_GLFW.txt)
include (CMake/Config_GLM.txt)
include (CMake/Config_GL.txt)
include (CMake/Config_Assimp.txt)
include (CMake/Config_OpenCV.txt)
##############################################################################################


add_subdirectory(Src)

##############################################################################################
# Install

install (DIRECTORY      ${LIGHTFIELD_MODEL_DIR}/Orchid   CONFIGURATIONS Debug   DESTINATION Models)
install (DIRECTORY      ${LIGHTFIELD_MODEL_DIR}/Orchid   CONFIGURATIONS Release DESTINATION Models)

install (FILES          ${LIGHTFIELD_SHADER_DIR}/Phong.vtx   CONFIGURATIONS Debug   DESTINATION Shaders)
install (FILES          ${LIGHTFIELD_SHADER_DIR}/Phong.vtx   CONFIGURATIONS Release DESTINATION Shaders)

install (FILES          ${LIGHTFIELD_SHADER_DIR}/Phong.frg   CONFIGURATIONS Debug   DESTINATION Shaders)
install (FILES          ${LIGHTFIELD_SHADER_DIR}/Phong.frg   CONFIGURATIONS Release DESTINATION Shaders)

##############################################################################################



##############################################################################################
# Packaging

set (CPACK_PACKAGE_NAME                       "LightField")
set (CPACK_PACKAGE_VENDOR                     "TLBurnettIII")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY        "LightField Radiance Image Rendering and Tools")
set (CPACK_PACKAGE_VERSION_MAJOR              ${LIGHTFIELD_VERSION_MAJOR})
set (CPACK_PACKAGE_VERSION_MINOR              ${LIGHTFIELD_VERSION_MINOR})
set (CPACK_PACKAGE_VERSION_PATCH              ${LIGHTFIELD_VERSION_PATCH})
set (CPACK_PACKAGE_VERSION                    ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH})
set (CPACK_DEBIAN_PACKAGE_MAINTAINER          "Thomas Burnett") 
set (CPACK_PACKAGE_INSTALL_DIRECTORY          "LightField")
 
include (CPack)

##############################################################################################
