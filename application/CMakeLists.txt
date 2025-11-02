find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

set(IMGUI_DIR ${PROJECT_SOURCE_DIR}/third_party/imgui)
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
)
set(IMGUI_HEADERS
    ${IMGUI_DIR}/imgui.h
    ${IMGUI_DIR}/imconfig.h
    ${IMGUI_DIR}/imgui_internal.h
    ${IMGUI_DIR}/imstb_rectpack.h
    ${IMGUI_DIR}/imstb_textedit.h
    ${IMGUI_DIR}/imstb_truetype.h
)
set(IMGUI_BACKENDS
    ${IMGUI_DIR}/imgui_impl_opengl3.cpp
    ${IMGUI_DIR}/imgui_impl_opengl3.h
    ${IMGUI_DIR}/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/imgui_impl_glfw.h
)

add_library(imgui STATIC ${IMGUI_SOURCES} ${IMGUI_HEADERS} ${IMGUI_BACKENDS})
target_link_libraries(imgui PUBLIC OpenGL::GL glfw)

file(GLOB_RECURSE APPLICATIONS ./ *.cpp)
add_library(applicationlib STATIC ${APPLICATIONS})
target_link_libraries(applicationlib PRIVATE imgui)
target_include_directories(applicationlib PRIVATE ${IMGUI_DIR})
target_include_directories(applicationlib PUBLIC .)