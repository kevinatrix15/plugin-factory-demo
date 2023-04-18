######################################################
# Project Setup
######################################################
cmake_minimum_required(VERSION 3.13)

# set the project name
project(linking-test VERSION 1.0.0)

######################################################
# Project-Specific Options
######################################################

option(USE_A_TYPE "Directly use symbols from types_lib to force library loading" OFF)
option(USE_LINK_OPTS "Add linker options to force all libs to be linked and loaded" OFF)

######################################################
# Global Compiler Options
######################################################
# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)
add_compile_options(-fPIC -g -O2)

add_library(factory_lib SHARED src/factory.cpp)

add_library(registry_lib SHARED src/registry.cpp)
target_link_libraries(registry_lib PUBLIC factory_lib)

add_library(types_lib SHARED src/custom_types.cpp)
target_link_libraries(types_lib PUBLIC registry_lib)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE factory_lib registry_lib types_lib)

if(USE_A_TYPE)
  # If we specify '-DUSE_A_TYPE' when invoking cmake,
  # we'll directly use a custom type from the types lib
  target_compile_definitions(main PRIVATE USE_A_TYPE)
endif()

if(USE_LINK_OPTS)
  # The "--no-as-needed" flag tells the linker to not ignore libraries
  # regardless of whether they satisfy an undefined symbol ref or not
  target_link_options(main PRIVATE LINKER:--no-as-needed)
endif()
