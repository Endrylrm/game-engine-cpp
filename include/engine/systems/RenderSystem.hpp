#pragma once
#include <vector>
#include "engine/core/graphics/Renderer.hpp"
#include "engine/core/events/EventBus.hpp"
#include "engine/core/events/Connections.hpp"
#include "engine/entities/components/SpriteRenderer.hpp"
#include "engine/entities/components/events/ComponentEvents.hpp"

class RenderSystem
{
public:
    void onInit();
    void onUnload();
    void onRender(Renderer &renderer);

    void setEventBus(EventBus* SceneEventBus) {
        eventBus = SceneEventBus;
    }

private:
    EventConnection spriteAdded;
    EventConnection spriteRemoved;

    std::vector<SpriteRenderer *> sprites{};
    EventBus* eventBus{};
};
