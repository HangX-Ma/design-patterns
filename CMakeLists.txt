cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(design-pattern LANGUAGES CXX)

# set language standard and other property
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(
  -Wall # print warning info
  -Wextra # print extra warning info
  # -Wconversion # data conversion truncation warning -Wsign-conversion # sign
  # <-> unsigned conversion warning
)
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE
      "Debug"
      CACHE STRING "Choose Release or Debug" FORCE)
endif()

if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
  message(STATUS "Maximum optimization for speed")
  add_compile_options(-Ofast)
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
  message(STATUS "Maximum optimization for speed, debug info included")
  add_compile_options(-Ofast -g)
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
  message(STATUS "Maximum optimization for size")
  add_compile_options(-Os)
else()
  message(STATUS "Minimal optimization, debug info included")
  add_compile_options(-Og -g)
endif()

if(CMAKE_SOURCE_DIR EQUAL CMAKE_BINARY_DIR)
  message(ERROR "Please select a folder to do out of source build")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(kamacoder)
