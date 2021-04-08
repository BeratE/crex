#### Root CMakeLists file of the project
#### Configuration file is build for GNU/Linux Systems
#### Resort to your local CMake guide for how to configure for Windows
cmake_minimum_required (VERSION 3.15)

# General Project Settings
project (RegExParser C)
set (EXECUTABLE_NAME "cexp")
set(CMAKE_BUILD_TYPE Debug)


# External dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")


# Directory Structure
set (SRC_DIR "${CMAKE_SOURCE_DIR}/src") # Source Files
set (BIN_DIR "${CMAKE_SOURCE_DIR}/bin") # Binaries
#set (LIB_DIR "${CMAKE_SOURCE_DIR}/lib") # Static libraries
set (INC_DIR "${CMAKE_SOURCE_DIR}/inc") # Addition include

set (INCS ${INC_DIR}) # Include directories for compiling
set (LIBS m)  # Libraries to link target against


# Configuration
#set (PROJECT_VERSION_MAJOR 1)
#set (PROJECT_VERSION_MINOR 0)

#configure_file (
#  "${CMAKE_SOURCE_DIR}/cmake/config.h.in"
#  "${INC_DIR}/config.h")


# Compiler Config
set(CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic -Wno-unused-variable")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O3")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Input Path
include_directories(${INCS}) # Include these targets for the compiling process
link_directories(${LIBS}) # Link targets against following libraries

# Output Path
#set(LIBRARY_OUTPUT_PATH ${LIB_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}/${CMAKE_BUILD_TYPE})


### Software Rendering Engine library
set (SRC_FILES
  # Header
  ${SRC_DIR}/parser.h
  # Source
  ${SRC_DIR}/parser.c
  ${SRC_DIR}/main.c)


### Final target executable
add_executable (${EXECUTABLE_NAME} ${SRC_FILES})
target_link_libraries(${EXECUTABLE_NAME} ${LIBS})
