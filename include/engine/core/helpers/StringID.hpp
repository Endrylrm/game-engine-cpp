#pragma once
#include <cstdint>
#include "engine/core/helpers/Hash.hpp"

struct StringID
{
    std::uint64_t value{};

    constexpr StringID() = default;

    constexpr explicit StringID(std::string_view str) noexcept
        : value(fnv1a_64(str))
    {
    }

    constexpr explicit StringID(std::uint64_t hash) noexcept
        : value(hash)
    {
    }

    constexpr auto operator<=>(const StringID&) const = default;
};