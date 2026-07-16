#pragma once
#include <functional>
#include "engine/core/events/ConnectionSlot.hpp"

struct Event
{
    virtual ~Event() = default;
};
