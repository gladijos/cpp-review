cmake_minimum_required(VERSION 3.16)
project(stl_containers)

set (CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(
  stl_containers_executable
  ${SOURCES}
)

target_include_directories(
  stl_containers_executable 
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
