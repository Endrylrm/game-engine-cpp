#pragma once
#include "engine/scenes/Scene.hpp"
#include "engine/core/graphics/Renderer.hpp"
#include "game/managers/GameManager.hpp"

class GameplayScene : public Scene
{
public:
    ~GameplayScene() override = default;

protected:
    void onInit() override;
    void onPreUpdate() override;
    void onUpdate(float deltaTime) override;
    void onPostUpdate() override;
    void onPhysics(float fixedDeltaTime) override;
    void onRender(Renderer &renderer) override;

private:
    GameManager gameManager{};
};
