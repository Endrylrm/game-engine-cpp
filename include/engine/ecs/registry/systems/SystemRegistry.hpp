#pragma once
#include <cstdint>

using SystemTypeId = uint32_t;

class SystemRegistry
{
public:
    template <typename T>
    static SystemTypeId get_type_id()
    {
        static const SystemTypeId ID = next_id++;
        return ID;
    }

private:
    inline static SystemTypeId next_id{};
};
