file(GLOB_RECURSE GPU ./ *.cpp)
add_library(gpulib STATIC ${GPU} "dataStructures.h")
target_include_directories(gpulib PUBLIC .)