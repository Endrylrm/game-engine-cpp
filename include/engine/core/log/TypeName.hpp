#pragma once

template <typename T>
constexpr std::string_view getTypeName()
{
#if defined(__clang__) || defined(__GNUC__)
    std::string_view name = __PRETTY_FUNCTION__;

    constexpr std::string_view prefix = "T = ";
    constexpr std::string_view suffix = "]";

    const auto start = name.find(prefix) + prefix.size();
    const auto end = name.find(suffix, start);

    return name.substr(start, end - start);

#elif defined(_MSC_VER)
    std::string_view name = __FUNCSIG__;

    constexpr std::string_view prefix = "getTypeName<";
    constexpr std::string_view suffix = ">(void)";

    const auto start = name.find(prefix) + prefix.size();
    const auto end = name.find(suffix, start);

    return name.substr(start, end - start);
#endif
}
