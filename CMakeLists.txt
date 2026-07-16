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
    src/engine/entities/Entity.cpp
    src/engine/entities/EntityManager.cpp
    src/engine/scenes/SceneManager.cpp
    src/engine/time/Time.cpp
    src/engine/time/Timer.cpp
    src/engine/time/TimerManager.cpp
)

set(GAME_SOURCES
    src/main.cpp
    src/game/SpaceShooterGame.cpp
    src/game/components/bullet/BulletDeleter.cpp
    src/game/components/bullet/BulletMove.cpp
    src/game/components/bullet/BulletRenderer.cpp
    src/game/components/common/ClampLR.cpp
    src/game/components/common/ClampUD.cpp
    src/game/components/common/Health.cpp
    src/game/components/player/PlayerController.cpp
    src/game/components/player/PlayerRenderer.cpp
    src/game/Factories/BulletFactory.cpp
    src/game/Factories/PlayerFactory.cpp
    src/game/managers/GameManager.cpp
    src/game/scenes/GameplayScene.cpp
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