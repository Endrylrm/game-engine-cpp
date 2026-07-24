#pragma once
#include <vector>
#include "engine/core/graphics/Renderer.hpp"
#include "engine/entities/Entity.hpp"
#include "engine/core/events/Connections.hpp"
#include "engine/entities/components/SpriteRenderer.hpp"
#include "engine/entities/components/events/ComponentEvents.hpp"

class RenderSystem
{
public:
    void onInit();
    void onRender(Renderer &renderer);

private:
    EventConnection spriteAdded;
    EventConnection spriteRemoved;

    std::vector<Entity *> entities;
};
