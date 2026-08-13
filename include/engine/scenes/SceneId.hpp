#pragma once
#include <functional>

struct SceneId
{
    uint32_t value{};

    constexpr bool operator==(const SceneId &) const = default;
};

struct SceneIdHash
{
    size_t operator()(SceneId id) const noexcept
    {
        return std::hash<uint32_t>{}(id.value);
    }
};
