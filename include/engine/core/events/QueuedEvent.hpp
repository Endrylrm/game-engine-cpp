#pragma once
#include <typeindex>
#include <memory>
#include "engine/core/events/Event.hpp"

struct QueuedEvent
{
    std::type_index type;
    std::unique_ptr<Event> event;
};