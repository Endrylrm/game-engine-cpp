#pragma once
#include <cstdint>
#include <functional>
#include <limits>

template <typename Tag, typename T = uint32_t, T InvalidValue = T{0}>
struct TypedIdentifier
{
    T index = InvalidValue;

    constexpr bool is_valid() const
    {
        return index != InvalidValue;
    }

    constexpr void reset()
    {
        index = InvalidValue;
    }

    constexpr bool operator==(const TypedIdentifier &other) const
    {
        return index == other.index;
    }

    constexpr bool operator!=(const TypedIdentifier &other) const
    {
        return !(*this == other);
    }

    constexpr operator T() const
    {
        return index;
    }
};

template <typename Tag, typename T, T InvalidValue>
struct std::hash<TypedIdentifier<Tag, T, InvalidValue>>
{
    size_t operator()(const TypedIdentifier<Tag, T, InvalidValue> &identifier) const noexcept
    {
        return std::hash<T>{}(identifier.index);
    }
};
