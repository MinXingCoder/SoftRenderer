file(GLOB_RECURSE FUNCS ./ *.cpp)
add_library(applicationlib STATIC ${FUNCS})