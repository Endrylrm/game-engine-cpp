#pragma once
#include <functional>

#include "Handle.hpp"

template <typename Tag>
struct TypedHandle : public Handle
{
    constexpr TypedHandle() = default;
    constexpr TypedHandle(Handle handle) : Handle(handle) {}
    constexpr TypedHandle(uint32_t id, uint32_t generation) : Handle{id, generation} {}
};

template <typename Tag>
struct std::hash<TypedHandle<Tag>>
{
    size_t operator()(const TypedHandle<Tag> &handle) const noexcept
    {
        return std::hash<Handle>{}(handle);
    }
};
