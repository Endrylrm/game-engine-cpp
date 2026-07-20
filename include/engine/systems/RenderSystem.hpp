#pragma once
#include "engine/core/graphics/Renderer.hpp"
#include "engine/entities/EntityManager.hpp"

class RenderSystem
{
public:
    void render(EntityManager &entityManager, Renderer &renderer);
};
