#pragma once
#include <cstdint>
#include <iostream>
#include <string>
#include <string_view>

#include "engine/core/string/StringIntern.hpp"
#include "engine/core/string/StringTable.hpp"

class StringHandle
{
public:
    StringHandle() = default;
    explicit StringHandle(std::string_view str) : string(StringTable::intern(str)) {}

    const std::string_view &text() const
    {
        return string->text;
    }

    uint64_t hash() const
    {
        return string->hash;
    }

    StringHandle &operator=(std::string_view str)
    {
        string = StringTable::intern(str);
        return *this;
    }

    bool operator==(const StringHandle &) const = default;

    explicit operator bool() const
    {
        return string != nullptr;
    }

    operator std::string_view() const
    {
        return text();
    }

    friend std::ostream &operator<<(std::ostream &os, const StringHandle &handle)
    {
        os << handle.text();
        return os;
    }

private:
    const StringIntern *string{};
};

// for use in maps as keys
struct StringHandleHash
{
    uint64_t operator()(const StringHandle &handle) const
    {
        return handle.hash();
    }
};
