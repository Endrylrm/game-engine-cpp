#pragma once
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include "engine/core/string/StringIntern.hpp"

class StringTable
{
public:
    static const StringIntern* intern(std::string_view str);

private:
    inline static std::unordered_map<std::string, std::unique_ptr<StringIntern>> strings;
};
