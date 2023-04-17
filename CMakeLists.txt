cmake_minimum_required(VERSION 3.10)

# set the project name
project(linking-test VERSION 1.0.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CXXFLAGS "-fPIC -g -O2")
option(USE_A_TYPE "Directly use a type from the types lib to make it work" OFF)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(factory_lib SHARED factory.cpp)

add_library(registry_lib SHARED registry.cpp)
target_link_libraries(registry_lib PUBLIC factory_lib)

add_library(types_lib SHARED custom_types.cpp)
target_link_libraries(types_lib PUBLIC registry_lib)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE factory_lib registry_lib types_lib)

if (USE_A_TYPE)
  target_compile_definitions(main PRIVATE USE_A_TYPE)
endif()
