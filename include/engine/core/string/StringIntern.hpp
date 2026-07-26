#pragma once
#include <cstdint>
#include <string_view>

struct StringIntern
{
    std::string_view text;
    uint64_t hash;
};
