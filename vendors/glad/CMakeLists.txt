add_library(glad STATIC src/gl.c)
target_include_directories(glad SYSTEM PUBLIC include)
add_library(glad::glad ALIAS glad)
