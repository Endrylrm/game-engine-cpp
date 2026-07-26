#pragma once
#include <string_view>
#include <cstdint>

[[nodiscard]]
constexpr uint32_t fnv1a_32(std::string_view str) noexcept
{
    uint32_t hash = 2166136261U;

    for (char c : str) 
    {
        hash ^= static_cast<uint8_t>(c);
        hash *= 16777619U;
    }

    return hash;
}

[[nodiscard]]
constexpr uint64_t fnv1a_64(std::string_view str) noexcept
{
    uint64_t hash = 14695981039346656037ULL;

    for (char c : str) 
    {
        hash ^= static_cast<uint8_t>(c);
        hash *= 1099511628211ULL;
    }

    return hash;
}

constexpr uint32_t operator"" _fnv32(const char* str, std::size_t len) noexcept {
    return fnv1a_32(std::string_view(str, len));
}

constexpr uint64_t operator"" _fnv64(const char* str, std::size_t len) noexcept {
    return fnv1a_64(std::string_view(str, len));
}