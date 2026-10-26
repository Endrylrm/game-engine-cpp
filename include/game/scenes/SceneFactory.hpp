#pragma once
#include "engine/scenes/Scene.hpp"

class SceneFactory
{
public:
    static void create_menu_scene(Scene &scene);
    static void create_gameplay_scene(Scene &scene);
    static void create_player_scene(Scene &scene);
};
