cmake_minimum_required(VERSION 3.26)
project(SoftRenderer)

set(CMAKE_CXX_STANDARD 17)

file(GLOB ASSETS "./assets")
file(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR})

add_subdirectory(application)
add_subdirectory(gpu)

find_package(glm REQUIRED)

add_executable(SoftRenderer main.cpp)
target_link_libraries(SoftRenderer PRIVATE applicationlib)
target_link_libraries(SoftRenderer PRIVATE gpulib)
target_link_libraries(SoftRenderer PRIVATE glm::glm)
target_include_directories(SoftRenderer PRIVATE ${GLM_INCLUDE_DIRS})

add_executable(testMath testMath.cpp)
target_link_libraries(testMath PRIVATE glm::glm)
target_include_directories(testMath PRIVATE ${GLM_INCLUDE_DIRS})