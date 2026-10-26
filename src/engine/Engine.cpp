#include "engine/Engine.hpp"

#include <chrono>
#include <string>
#include <thread>

#include "engine/api/AssetsAPI.hpp"
#include "engine/api/EntityAPI.hpp"
#include "engine/api/EventsAPI.hpp"
#include "engine/api/InputAPI.hpp"
#include "engine/api/ScenesAPI.hpp"
#include "engine/api/TimeAPI.hpp"
#include "engine/api/TimerAPI.hpp"
#include "engine/api/WindowAPI.hpp"
#include "engine/api/WorldAPI.hpp"
#ifdef RENDERER_OPENGL
#include "engine/renderer/OpenGL/OpenGLDevice.hpp"
#elif defined(RENDERER_SDL)
#include "engine/renderer/SDL/SDLDevice.hpp"
#endif
#include "engine/core/log/Logger.hpp"
#include "engine/input/SDL/SDLInputManager.hpp"
#include "engine/renderer/resources/Texture.hpp"
#include "engine/window/SDL/SDLWindow.hpp"

void Engine::initialize(const char *title, int width, int height)
{
    running = true;

    Logger::get().init();

    window = std::make_unique<SDLWindow>(title, width, height);
    SDLWindow *window_ptr = static_cast<SDLWindow *>(window.get());
    if (!window_ptr->on_init())
    {
        return;
    }

#ifdef RENDERER_SDL
    render_device = std::make_unique<SDLDevice>(window_ptr->getWindowHandle());
    SDLDevice *device_ptr = static_cast<SDLDevice *>(render_device.get());
#elif defined(RENDERER_OPENGL)
    render_device = std::make_unique<OpenGLDevice>(window_ptr->get_window_handle());
    OpenGLDevice *device_ptr = static_cast<OpenGLDevice *>(render_device.get());
#endif

    if (!renderer.init(device_ptr))
    {
        return;
    }

    input_manager = std::make_unique<SDLInputManager>(&running);
    asset_db.register_asset_type<Texture>([this](const std::string &path)
                                          { return renderer.load_texture(path); });

    InputAPI::set_manager(input_manager.get());
    WindowAPI::set_manager(window.get());
    ScenesAPI::set_manager(&scene_manager);
    EntityAPI::set_manager(&scene_manager);
    AssetsAPI::set_manager(&asset_db);
    TimerAPI::set_manager(&timer_manager);
    TimeAPI::set_manager(&time);
    EventsAPI::set_manager(&event_bus);
    WorldAPI::set_manager(&world);

    world.init();
    game.on_init();
}

void Engine::begin_frame()
{
    input_manager->begin_frame();
    input_manager->process_event();
    event_bus.process_events();
    game.on_begin_frame();
}

void Engine::physics_step(float fixed_delta_time)
{
    world.physics(fixed_delta_time);
    game.on_physics(fixed_delta_time);
}

void Engine::pre_update()
{
    world.pre_update();
    game.on_pre_update();
}

void Engine::update(float delta_time)
{
    world.update(delta_time);
    timer_manager.on_update(delta_time);
    game.on_update(delta_time);
}

void Engine::post_update()
{
    world.post_update();
    game.on_post_update();
}

void Engine::render()
{
    renderer.clear();
    world.render(renderer);
    game.on_render();
    renderer.present();
}

void Engine::process_commands()
{
    scene_manager.process_commands();
}

void Engine::process_lifecycle()
{
    world.process_lifecycle();
    event_bus.remove_deleted_events();
    game.process_lifecycle();
}

void Engine::end_frame()
{
    game.on_end_frame();
}

void Engine::main_loop()
{
    const float FIXED_DELTA_TIME = time.get_fixed_delta_time();
    std::chrono::duration<float> target_frame_time = time.get_target_frame_time();

    while (running)
    {
        auto frame_start = std::chrono::steady_clock::now();
        time.tick();

        begin_frame();

        int fixed_steps = time.consume_fixed_steps();
        for (int i = 0; i < fixed_steps; i++)
        {
            physics_step(FIXED_DELTA_TIME);
        }

        pre_update();
        update(time.get_delta_time());
        post_update();
        process_commands();
        process_lifecycle();
        render();

        end_frame();

        auto frame_time = std::chrono::steady_clock::now() - frame_start;

        if (frame_time < target_frame_time)
        {
            std::this_thread::sleep_for(target_frame_time - frame_time);
        }
    }

    shutdown();
}

void Engine::shutdown()
{
    game.on_shutdown();
    Logger::get().shutdown();
}
