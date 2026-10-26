#pragma once
#include <string_view>

template <typename T>
constexpr std::string_view get_type_name()
{
#if defined(__clang__) || defined(__GNUC__)
    std::string_view name = __PRETTY_FUNCTION__;

    constexpr std::string_view PREFIX = "T = ";
    constexpr std::string_view SUFFIX = "]";

    const auto START = name.find(PREFIX) + PREFIX.size();
    const auto END = name.find(SUFFIX, START);

    return name.substr(START, END - START);

#elif defined(_MSC_VER)
    std::string_view name = __FUNCSIG__;

    constexpr std::string_view PREFIX = "getTypeName<";
    constexpr std::string_view SUFFIX = ">(void)";

    const auto START = name.find(PREFIX) + PREFIX.size();
    const auto END = name.find(SUFFIX, START);

    return name.substr(START, END - START);
#endif
}
