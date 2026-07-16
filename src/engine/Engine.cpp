#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include "engine/Engine.hpp"
#include "engine/backend/SDL/window/SDLWindowManager.hpp"
#include "engine/backend/SDL/graphics/SDLRenderer.hpp"
#include "engine/backend/SDL/input/SDLInputManager.hpp"
#include "engine/core/graphics/Texture.hpp"
#include "engine/api/InputAPI.hpp"
#include "engine/api/WindowAPI.hpp"
#include "engine/api/ScenesAPI.hpp"
#include "engine/api/EntityAPI.hpp"
#include "engine/api/AssetsAPI.hpp"
#include "engine/api/TimerAPI.hpp"
#include "engine/api/TimeAPI.hpp"

void Engine::initialize(const char *title, int width, int height)
{
	running = true;
	currentWindowManager = std::make_unique<SDLWindowManager>(title, width, height);
	currentRenderer = std::make_unique<SDLRenderer>();
	currentInputManager = std::make_unique<SDLInputManager>(&running);

	if (!currentWindowManager->onInit())
	{
		return;
	}

	if (!currentRenderer->onInit(currentWindowManager->getWindowHandle()))
	{
		return;
	}

	currentAssetDB.registerManager<Texture>(
		[this](const std::string &path)
		{ return currentRenderer->loadTexture(path); });

	InputAPI::setManager(currentInputManager.get());
	WindowAPI::setManager(currentWindowManager.get());
	ScenesAPI::setManager(&currentSceneManager);
	EntityAPI::setManager(&currentSceneManager);
	AssetsAPI::setManager(&currentAssetDB);
	TimerAPI::setManager(&currentTimerManager);
	TimeAPI::setManager(&currentTime);

	game.onInit();
}

void Engine::beginFrame()
{
	currentInputManager->beginFrame();
	currentInputManager->processEvent();
	game.onBeginFrame();
}

void Engine::physicsStep(float fixedDeltaTime)
{
	currentSceneManager.onPhysics(fixedDeltaTime);
	game.onPhysics(fixedDeltaTime);
}

void Engine::preUpdate()
{
	currentSceneManager.onPreUpdate();
	game.onPreUpdate();
}

void Engine::update(float deltaTime)
{
	currentSceneManager.onUpdate(deltaTime);
	currentTimerManager.onUpdate(deltaTime);
	game.onUpdate(deltaTime);
}

void Engine::postUpdate()
{
	currentSceneManager.onPostUpdate();
	game.onPostUpdate();
}

void Engine::render()
{
	currentRenderer->clear();
	currentSceneManager.onRender(*currentRenderer);
	game.onRender();
	currentRenderer->present();
}

void Engine::processLifeCycle()
{
	currentSceneManager.processLifecycle();
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
		processLifeCycle();
		render();
		endFrame();

		auto frameTime = std::chrono::steady_clock::now() - frameStart;

		if (frameTime < targetFrameTime)
		{
			std::this_thread::sleep_for(targetFrameTime - frameTime);
		}
	}
}

void Engine::shutdown()
{
	game.onShutdown();
}
