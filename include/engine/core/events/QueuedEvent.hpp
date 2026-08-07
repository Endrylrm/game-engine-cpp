#pragma once
#include <memory>

#include "Event.hpp"
#include "EventRegistry.hpp"

struct QueuedEvent
{
    EventTypeId type;
    std::unique_ptr<Event> event;
};