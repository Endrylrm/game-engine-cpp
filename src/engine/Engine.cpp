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
    SDLWindow *windowPtr = static_cast<SDLWindow *>(window.get());
    if (!windowPtr->onInit())
    {
        return;
    }

#ifdef RENDERER_SDL
    render_device = std::make_unique<SDLDevice>(windowPtr->getWindowHandle());
    SDLDevice *devicePtr = static_cast<SDLDevice *>(render_device.get());
#elif defined(RENDERER_OPENGL)
    render_device = std::make_unique<OpenGLDevice>(windowPtr->getWindowHandle());
    OpenGLDevice *devicePtr = static_cast<OpenGLDevice *>(render_device.get());
#endif

    if (!renderer.init(devicePtr))
    {
        return;
    }

    input_manager = std::make_unique<SDLInputManager>(&running);
    asset_db.registerAssetType<Texture>([this](const std::string &path)
                                        { return renderer.loadTexture(path); });

    InputAPI::setManager(input_manager.get());
    WindowAPI::setManager(window.get());
    ScenesAPI::setManager(&scene_manager);
    EntityAPI::setManager(&scene_manager);
    AssetsAPI::setManager(&asset_db);
    TimerAPI::setManager(&timer_manager);
    TimeAPI::setManager(&time);
    EventsAPI::setManager(&event_bus);
    WorldAPI::setManager(&world);

    world.init();
    game.onInit();
}

void Engine::begin_frame()
{
    input_manager->beginFrame();
    input_manager->processEvent();
    event_bus.processEvents();
    game.onBeginFrame();
}

void Engine::physics_step(float fixedDeltaTime)
{
    world.physics(fixedDeltaTime);
    game.onPhysics(fixedDeltaTime);
}

void Engine::pre_update()
{
    world.preUpdate();
    game.onPreUpdate();
}

void Engine::update(float deltaTime)
{
    world.update(deltaTime);
    timer_manager.onUpdate(deltaTime);
    game.onUpdate(deltaTime);
}

void Engine::post_update()
{
    world.postUpdate();
    game.onPostUpdate();
}

void Engine::render()
{
    renderer.clear();
    world.render(renderer);
    game.onRender();
    renderer.present();
}

void Engine::process_commands()
{
    scene_manager.processCommands();
}

void Engine::process_lifecycle()
{
    world.processLifecycle();
    event_bus.removeDeletedEvents();
    game.processLifecycle();
}

void Engine::end_frame()
{
    game.onEndFrame();
}

void Engine::main_loop()
{
    const float fixed_delta_time = time.getFixedDeltaTime();
    std::chrono::duration<float> target_frame_time = time.getTargetFrameTime();

    while (running)
    {
        auto frame_start = std::chrono::steady_clock::now();
        time.tick();

        begin_frame();

        int fixed_steps = time.consumeFixedSteps();
        for (int i = 0; i < fixed_steps; i++)
        {
            physics_step(fixed_delta_time);
        }

        pre_update();
        update(time.getDeltaTime());
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
    game.onShutdown();
    Logger::get().shutdown();
}
