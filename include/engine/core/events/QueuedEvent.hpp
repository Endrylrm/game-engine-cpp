#pragma once
#include <memory>

#include "engine/core/events/Event.hpp"
#include "engine/core/events/EventRegistry.hpp"

struct QueuedEvent
{
    EventTypeId type;
    std::unique_ptr<Event> event;
};