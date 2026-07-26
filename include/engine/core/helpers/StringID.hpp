#pragma once
#include <cstdint>
#include "engine/core/helpers/Hash.hpp"

struct String32ID
{
    std::uint32_t value{};

    constexpr String32ID() = default;

    constexpr explicit String32ID(std::string_view str) noexcept
        : value(fnv1a_32(str))
    {
    }

    constexpr explicit String32ID(std::uint32_t hash) noexcept
        : value(hash)
    {
    }

    constexpr auto operator<=>(const String32ID&) const = default;
};

struct String64ID
{
    std::uint64_t value{};

    constexpr String64ID() = default;

    constexpr explicit String64ID(std::string_view str) noexcept
        : value(fnv1a_64(str))
    {
    }

    constexpr explicit String64ID(std::uint64_t hash) noexcept
        : value(hash)
    {
    }

    constexpr auto operator<=>(const String64ID&) const = default;
};