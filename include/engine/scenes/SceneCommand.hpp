#pragma once
#include "engine/scenes/SceneRegistry.hpp"

enum class SceneCommandType
{
    Load,
    LoadAdditive,
    Unload
};

struct SceneCommand
{
    SceneCommandType type;
    SceneId id;
};
