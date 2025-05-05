file(GLOB_RECURSE GPU ./ *.cpp *.h)
find_package(glm REQUIRED)
add_library(gpulib STATIC ${GPU}
        shader.h
        shader.cpp
        shader/defaultshader.h
        shader/defaultshader.cpp
        raster.h
        raster.cpp)
target_link_libraries(gpulib PRIVATE glm::glm)
target_include_directories(gpulib PUBLIC .)