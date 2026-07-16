#pragma once
#include <memory>
#include "engine/Game.hpp"
#include "engine/core/window/WindowManager.hpp"
#include "engine/core/graphics/Renderer.hpp"
#include "engine/core/input/InputManager.hpp"
#include "engine/scenes/SceneManager.hpp"
#include "engine/time/Time.hpp"
#include "engine/time/TimerManager.hpp"
#include "engine/assets/AssetDatabase.hpp"

class Engine
{
public:
	Engine(Game &gameRef) : game(gameRef) {}
	void initialize(const char *title, int width, int height);
	void mainLoop();
	void shutdown();

private:
	void beginFrame();
	void physicsStep(float fixedDeltaTime);
	void preUpdate();
	void update(float deltaTime);
	void postUpdate();
	void render();
	void processLifeCycle();
	void endFrame();

	std::unique_ptr<WindowManager> currentWindowManager;
	std::unique_ptr<Renderer> currentRenderer;
	std::unique_ptr<InputManager> currentInputManager;
	std::unique_ptr<AssetDatabase> currentAssetDB;
	std::unique_ptr<SceneManager> currentSceneManager;
	std::unique_ptr<TimerManager> currentTimerManager;
	std::unique_ptr<Time> currentTime;
	Game &game;
	bool running = true;
};
