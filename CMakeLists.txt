cmake_minimum_required(VERSION 3.23)
project(game-engine-cpp VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out/$<CONFIG>/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out/$<CONFIG>/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out/$<CONFIG>/obj")

option(ENABLE_DEBUG "Enable debug" ON)
option(RENDERER_SDL "Use SDL" OFF)
option(RENDERER_OPENGL "Use OpenGL" ON)

if(RENDERER_SDL AND RENDERER_OPENGL)
    message(FATAL_ERROR "Only one renderer can be enabled!")
endif()

if(NOT RENDERER_SDL AND NOT RENDERER_OPENGL)
    message(FATAL_ERROR "No renderer selected!")
endif()

add_subdirectory(vendors)

add_subdirectory(src/engine)
add_subdirectory(src/game)

add_executable(SpaceShooter src/main.cpp)
target_link_libraries(SpaceShooter PRIVATE Game)
