#include "engine/Engine.hpp"

#include <chrono>
#include <string>
#include <thread>

#include <engine/api/AssetsAPI.hpp>
#include <engine/api/EntityAPI.hpp>
#include <engine/api/EventsAPI.hpp>
#include <engine/api/InputAPI.hpp>
#include <engine/api/ScenesAPI.hpp>
#include <engine/api/TimeAPI.hpp>
#include <engine/api/TimerAPI.hpp>
#include <engine/api/WindowAPI.hpp>
#include <engine/api/WorldAPI.hpp>
#ifdef RENDERER_OPENGL
#include <engine/backend/OpenGL/graphics/OpenGLRenderer.hpp>
#elif defined(RENDERER_SDL)
#include <engine/backend/SDL/graphics/SDLRenderer.hpp>
#endif
#include <engine/backend/SDL/input/SDLInputManager.hpp>
#include <engine/backend/SDL/window/SDLWindow.hpp>
#include <engine/core/graphics/Texture.hpp>
#include <engine/core/log/Logger.hpp>

void Engine::initialize(const char *title, int width, int height)
{
    running = true;

    Logger::get().init();

    currentWindow = std::make_unique<SDLWindow>(title, width, height);
    SDLWindow *windowPtr = static_cast<SDLWindow *>(currentWindow.get());
    if (!windowPtr->onInit())
    {
        return;
    }

#ifdef RENDERER_SDL
    currentRenderer = std::make_unique<SDLRenderer>(windowPtr->getWindowHandle());
    SDLRenderer *rendererPtr = static_cast<SDLRenderer *>(currentRenderer.get());
    if (!rendererPtr->onInit())
    {
        return;
    }
#elif defined(RENDERER_OPENGL)
    currentRenderer = std::make_unique<OpenGLRenderer>(windowPtr->getWindowHandle());
    OpenGLRenderer *rendererPtr = static_cast<OpenGLRenderer *>(currentRenderer.get());
    if (!rendererPtr->onInit())
    {
        return;
    }
#endif

    currentInputManager = std::make_unique<SDLInputManager>(&running);
    currentAssetDB.registerManager<Texture>([this](const std::string &path)
                                            { return currentRenderer->loadTexture(path); });

    InputAPI::setManager(currentInputManager.get());
    WindowAPI::setManager(currentWindow.get());
    ScenesAPI::setManager(&currentSceneManager);
    EntityAPI::setManager(&currentSceneManager);
    AssetsAPI::setManager(&currentAssetDB);
    TimerAPI::setManager(&currentTimerManager);
    TimeAPI::setManager(&currentTime);
    EventsAPI::setManager(&eventBus);
    WorldAPI::setManager(&currentWorld);

    currentWorld.init();
    game.onInit();
}

void Engine::beginFrame()
{
    currentInputManager->beginFrame();
    currentInputManager->processEvent();
    eventBus.processEvents();
    game.onBeginFrame();
}

void Engine::physicsStep(float fixedDeltaTime)
{
    currentWorld.physics(fixedDeltaTime);
    game.onPhysics(fixedDeltaTime);
}

void Engine::preUpdate()
{
    currentWorld.preUpdate();
    game.onPreUpdate();
}

void Engine::update(float deltaTime)
{
    currentWorld.update(deltaTime);
    currentTimerManager.onUpdate(deltaTime);
    game.onUpdate(deltaTime);
}

void Engine::postUpdate()
{
    currentWorld.postUpdate();
    game.onPostUpdate();
}

void Engine::render()
{
    currentRenderer->clear();
    currentWorld.render(*currentRenderer);
    game.onRender();
    currentRenderer->present();
}

void Engine::processCommands()
{
    currentSceneManager.processCommands();
}

void Engine::processLifeCycle()
{
    currentWorld.processLifecycle();
    eventBus.removeDeletedEvents();
    game.processLifecycle();
}

void Engine::endFrame()
{
    game.onEndFrame();
}

void Engine::mainLoop()
{
    const float fixedDeltaTime = currentTime.getFixedDeltaTime();
    std::chrono::duration<float> targetFrameTime = currentTime.getTargetFrameTime();

    while (running)
    {
        auto frameStart = std::chrono::steady_clock::now();
        currentTime.tick();

        beginFrame();

        int fixedSteps = currentTime.consumeFixedSteps();
        for (int i = 0; i < fixedSteps; i++)
        {
            physicsStep(fixedDeltaTime);
        }

        preUpdate();
        update(currentTime.getDeltaTime());
        postUpdate();
        processCommands();
        processLifeCycle();
        render();

        endFrame();

        auto frameTime = std::chrono::steady_clock::now() - frameStart;

        if (frameTime < targetFrameTime)
        {
            std::this_thread::sleep_for(targetFrameTime - frameTime);
        }
    }

    shutdown();
}

void Engine::shutdown()
{
    game.onShutdown();
    Logger::get().shutdown();
}
