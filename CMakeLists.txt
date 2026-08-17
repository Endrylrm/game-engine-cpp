cmake_minimum_required(VERSION 3.23)
project(game-engine-cpp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out/$<CONFIG>/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out/$<CONFIG>/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out/$<CONFIG>/obj")

add_subdirectory(vendors)

add_subdirectory(src/engine)
add_subdirectory(src/game)

add_executable(SpaceShooter src/main.cpp)
target_link_libraries(SpaceShooter PRIVATE Game)
