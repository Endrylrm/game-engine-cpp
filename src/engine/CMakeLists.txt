set(ENGINE_SOURCES
    Engine.cpp
    backend/SDL/input/SDLInputManager.cpp
    backend/SDL/window/SDLWindow.cpp
    core/log/Logger.cpp
    core/math/conversions/GLMConverter.cpp
    core/math/Quaternion.cpp
    core/math/Vector2D.cpp
    core/math/Vector3D.cpp
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

if(RENDERER_OPENGL)
    list(APPEND ENGINE_SOURCES
        backend/OpenGL/graphics/OpenGLMesh.cpp
        backend/OpenGL/graphics/OpenGLRenderer.cpp
        backend/OpenGL/graphics/OpenGLShader.cpp
        backend/OpenGL/graphics/OpenGLTexture.cpp
    )
elseif(RENDERER_SDL)
    list(APPEND ENGINE_SOURCES
        backend/SDL/graphics/SDLRenderer.cpp
        backend/SDL/graphics/SDLTexture.cpp
    )
endif()

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
find_package(SDL3_mixer CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)

find_package(glm CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

set(LIBS
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_mixer::SDL3_mixer
    SDL3_ttf::SDL3_ttf
    glad::glad
)

set(PUBLIC_LIBS
    glm::glm # math
    nlohmann_json::nlohmann_json
)

add_library(Engine STATIC ${ENGINE_SOURCES})
target_include_directories(Engine PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(Engine PUBLIC ${PUBLIC_LIBS} PRIVATE ${LIBS})

if(ENABLE_DEBUG)
    target_compile_definitions(Engine PUBLIC ENABLE_DEBUG)
endif()

if(RENDERER_SDL)
    target_compile_definitions(Engine PRIVATE RENDERER_SDL)
elseif(RENDERER_OPENGL)
    target_compile_definitions(Engine PRIVATE RENDERER_OPENGL)
endif()
