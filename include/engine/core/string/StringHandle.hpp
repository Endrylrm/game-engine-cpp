#pragma once
#include <cstdint>
#include <string>
#include <string_view>
#include "engine/core/string/StringTable.hpp"
#include "engine/core/string/StringIntern.hpp"

class StringHandle
{
public:
    StringHandle() = default;
    explicit StringHandle(std::string_view str) : string(StringTable::Intern(str)) {}

    const std::string_view& text() const
    {
        return string->text;
    }

    uint64_t hash() const
    {
        return string->hash;
    }

    StringHandle& operator=(std::string_view str)
    {
        string = StringTable::Intern(str);
        return *this;
    }

    bool operator==(const StringHandle&) const = default;

    explicit operator bool() const
    {
        return string != nullptr;
    }

private:
    const StringIntern* string{};
};
