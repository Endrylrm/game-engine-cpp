#pragma once
#include <memory>

#include "engine/assets/AssetDatabase.hpp"
#include "engine/core/events/EventBus.hpp"
#include "engine/ecs/world/World.hpp"
#include "engine/input/InputManager.hpp"
#include "engine/renderer/RenderDevice.hpp"
#include "engine/renderer/Renderer.hpp"
#include "engine/scenes/SceneManager.hpp"
#include "engine/time/Time.hpp"
#include "engine/time/TimerManager.hpp"
#include "engine/window/Window.hpp"

#include "Game.hpp"

class Engine
{
public:
    Engine(Game &gameRef) : game(gameRef) {}

    // Prevent copying and moving of the engine
    Engine(const Engine &) = delete;
    Engine &operator=(const Engine &) = delete;
    Engine(Engine &&) = delete;
    Engine &operator=(Engine &&) = delete;

    void initialize(const char *title, int width, int height);
    void main_loop();

private:
    void begin_frame();
    void physics_step(float fixedDeltaTime);
    void pre_update();
    void update(float deltaTime);
    void post_update();
    void render();
    void process_commands();
    void process_lifecycle();
    void end_frame();
    void shutdown();

    std::unique_ptr<Window> window{};
    std::unique_ptr<RenderDevice> render_device{};
    std::unique_ptr<InputManager> input_manager{};
    Renderer renderer{};
    AssetDatabase asset_db{};
    SceneManager scene_manager{world};
    World world{};
    TimerManager timer_manager{};
    Time time{};
    EventBus event_bus{};
    Game &game;
    bool running{true};
};
