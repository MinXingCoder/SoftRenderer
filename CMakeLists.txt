cmake_minimum_required(VERSION 3.24)
project(SoftRenderer)

set(CMAKE_CXX_STANDARD 17)

file(GLOB copyResources "./assets")
file(COPY ${copyResources} DESTINATION ${CMAKE_BINARY_DIR})

include_directories(global)
add_subdirectory(application)
add_subdirectory(gpu)

add_executable(${PROJECT_NAME} "main.cpp")
add_executable(testMath "testMath.cpp")
target_link_libraries(${PROJECT_NAME} applicationlib gpulib)