#pragma once
#include <cstdint>

using AssetManagerId = uint32_t;

class AssetManagerRegistry
{
public:
    template <typename T>
    static AssetManagerId get_type_id()
    {
        static const AssetManagerId id = next_id++;
        return id;
    }

private:
    inline static AssetManagerId next_id{};
};
