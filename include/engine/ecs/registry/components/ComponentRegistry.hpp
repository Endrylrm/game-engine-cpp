#pragma once
#include <cstdint>

using ComponentId = uint32_t;

class ComponentRegistry
{
public:
    template <typename T>
    static ComponentId get_type_id()
    {
        static const ComponentId id = next_id++;
        return id;
    }

private:
    inline static ComponentId next_id{};
};
