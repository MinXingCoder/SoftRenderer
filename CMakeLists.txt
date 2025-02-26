cmake_minimum_required(VERSION 3.24)
project(SoftRenderer)

include_directories(global)
add_subdirectory(application)
add_subdirectory(gpu)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} "main.cpp")
add_executable(testMath "testMath.cpp")
target_link_libraries(${PROJECT_NAME} applicationlib gpulib)