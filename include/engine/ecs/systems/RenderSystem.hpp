#pragma once
#include <engine/core/graphics/Renderer.hpp>
#include <engine/ecs/world/World.hpp>

#include "System.hpp"

class RenderSystem : public System
{
public:
    void onRender(World &world, Renderer &renderer) override;
};
