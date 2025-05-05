cmake_minimum_required(VERSION 3.20)
project(SoftRender)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(application)
add_subdirectory(gpu)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE applicationlib gpulib)