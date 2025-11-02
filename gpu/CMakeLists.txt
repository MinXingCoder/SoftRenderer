file(GLOB_RECURSE GPUS ./ *.cpp)
add_library(gpulib STATIC ${GPUS})
target_include_directories(gpulib PUBLIC .)