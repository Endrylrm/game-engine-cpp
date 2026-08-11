#pragma once
#include <engine/core/graphics/Renderer.hpp>
#include <engine/ecs/registry/Registry.hpp>

#include "System.hpp"

class RenderSystem : public System
{
public:
    explicit RenderSystem(Registry &registry) : registry(registry) {}
    void onRender(Renderer &renderer) override;

private:
    Registry &registry;
};
