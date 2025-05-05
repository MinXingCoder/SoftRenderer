file(GLOB_RECURSE FUNCS ./ *.cpp *.h)

set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/third_party/imgui")
set(IMGUI_SOURCES
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl2.cpp
        image.h
        image.cpp)

include_directories(${IMGUI_DIR} ${IMGUI_DIR}/backends)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_library(applicationlib STATIC ${FUNCS} ${IMGUI_SOURCES})
target_link_libraries(applicationlib PUBLIC glfw OpenGL::GL)
target_include_directories(applicationlib PUBLIC .)