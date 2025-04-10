file(GLOB_RECURSE GPU ./ *.cpp)
add_library(gpulib STATIC ${GPU} "dataStructures.h" "vao.h" "vao.cpp" "shader.h" "shader.cpp" "shader/defaulthader.h" "shader/defaultshader.cpp")
target_include_directories(gpulib PUBLIC .)