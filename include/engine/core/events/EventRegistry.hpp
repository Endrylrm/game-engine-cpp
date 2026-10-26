#pragma once
#include <cstdint>

using EventTypeId = uint32_t;

class EventRegistry
{
public:
    template <typename T>
    static EventTypeId get_type_id()
    {
        static const EventTypeId id = next_id++;
        return id;
    }

private:
    inline static EventTypeId next_id{};
};
