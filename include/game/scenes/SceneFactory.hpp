#pragma once
#include "engine/scenes/Scene.hpp"

class SceneFactory
{
public:
    static void createMenuScene(Scene &scene);
    static void createGameplayScene(Scene &scene);
};
