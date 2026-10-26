#pragma once
#include <cstdint>

using ComponentId = uint32_t;

class ComponentRegistry
{
public:
    template <typename T>
    static ComponentId get_type_id()
    {
        static const ComponentId ID = next_id++;
        return ID;
    }

private:
    inline static ComponentId next_id{};
};
