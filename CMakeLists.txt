cmake_minimum_required(VERSION 3.23)
project(game-engine-cpp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out/$<CONFIG>/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out/$<CONFIG>/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out/$<CONFIG>/obj")

add_subdirectory(vendors)

set(ENGINE_SOURCES
    src/engine/Engine.cpp
    src/engine/backend/SDL/graphics/SDLRenderer.cpp
    src/engine/backend/SDL/graphics/SDLTexture.cpp
    src/engine/backend/SDL/input/SDLInputManager.cpp
    src/engine/backend/SDL/window/SDLWindowManager.cpp
    src/engine/core/log/Logger.cpp
    src/engine/core/string/StringTable.cpp
    src/engine/scenes/Scene.cpp
    src/engine/scenes/SceneManager.cpp
    src/engine/ecs/registry/managers/EntityManager.cpp
    src/engine/ecs/registry/managers/SystemManager.cpp
    src/engine/ecs/systems/MovementSystem.cpp
    src/engine/ecs/systems/RenderSystem.cpp
    src/engine/ecs/world/World.cpp
    src/engine/time/Time.cpp
    src/engine/time/Timer.cpp
    src/engine/time/TimerManager.cpp
)

set(GAME_SOURCES
    src/main.cpp
    src/game/SpaceShooterGame.cpp
    src/game/ecs/systems/common/OutOfBoundsSystem.cpp
    src/game/ecs/systems/common/ScreenClampSystem.cpp
    src/game/ecs/systems/common/WeaponCooldownSystem.cpp
    src/game/ecs/systems/player/PlayerInputSystem.cpp
    src/game/ecs/systems/player/PlayerMoveSystem.cpp
    src/game/ecs/systems/player/PlayerShootSystem.cpp
    src/game/scenes/SceneFactory.cpp
)

set(LIBS
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_mixer::SDL3_mixer
    SDL3_ttf::SDL3_ttf
    glm::glm # math
)

add_executable(main ${ENGINE_SOURCES} ${GAME_SOURCES})
target_link_libraries(main PRIVATE ${LIBS})
target_include_directories(main PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)