#pragma once
#include "engine/ecs/world/World.hpp"
#include "engine/renderer/Renderer.hpp"

#include "System.hpp"

class RenderSystem final : public System
{
public:
    void on_render(World &world, Renderer &renderer) override;
};
