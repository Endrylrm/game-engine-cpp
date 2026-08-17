set(ENGINE_SOURCES
    Engine.cpp
    backend/SDL/graphics/SDLRenderer.cpp
    backend/SDL/graphics/SDLTexture.cpp
    backend/SDL/input/SDLInputManager.cpp
    backend/SDL/window/SDLWindowManager.cpp
    core/log/Logger.cpp
    core/string/StringTable.cpp
    scenes/Scene.cpp
    scenes/SceneManager.cpp
    ecs/registry/managers/EntityManager.cpp
    ecs/registry/managers/SystemManager.cpp
    ecs/systems/LifetimeSystem.cpp
    ecs/systems/MovementSystem.cpp
    ecs/systems/RenderSystem.cpp
    ecs/world/World.cpp
    time/Time.cpp
    time/Timer.cpp
    time/TimerManager.cpp
)

set(LIBS
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_mixer::SDL3_mixer
    SDL3_ttf::SDL3_ttf
    glm::glm # math
    nlohmann_json::nlohmann_json
    glad::glad
)

add_library(Engine STATIC ${ENGINE_SOURCES})
target_include_directories(Engine PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(Engine PUBLIC ${LIBS})
