#pragma once
#include <cstdint>

using EventTypeId = uint32_t;

class EventRegistry
{
public:
    template <typename T>
    static EventTypeId getTypeId()
    {
        static const EventTypeId id = nextId++;
        return id;
    }

private:
    inline static EventTypeId nextId{};
};
