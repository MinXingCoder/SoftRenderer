cmake_minimum_required(VERSION 3.26)
project(SoftRenderer)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(application)
add_subdirectory(gpu)

add_executable(SoftRenderer main.cpp)
target_link_libraries(SoftRenderer PRIVATE applicationlib)
target_link_libraries(SoftRenderer PRIVATE gpulib)