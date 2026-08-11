#pragma once

template <typename Enum>
class Flags
{
    static_assert(std::is_enum_v<Enum>);

public:
    using Underlying = std::underlying_type_t<Enum>;

    constexpr Flags() = default;
    constexpr Flags(Enum value) : value(value) {}

    constexpr void add(Enum flags)
    {
        value = static_cast<Enum>(static_cast<Underlying>(value) | static_cast<Underlying>(flags));
    }

    constexpr void remove(Enum flags)
    {
        value = static_cast<Enum>(static_cast<Underlying>(value) & ~static_cast<Underlying>(flags));
    }

    constexpr bool has(Enum flags) const
    {
        return (static_cast<Underlying>(value) & static_cast<Underlying>(flags)) ==
               static_cast<Underlying>(flags);
    }

    constexpr bool hasAny(Enum flags) const
    {
        return (static_cast<Underlying>(value) & static_cast<Underlying>(flags)) != 0;
    }

    constexpr void assign(Enum newValue)
    {
        value = newValue;
    }

    constexpr void set(Enum flags, bool enabled)
    {
        if (enabled)
            add(flags);
        else
            remove(flags);
    }

    constexpr void replace(Enum removeFlags, Enum addFlags)
    {
        remove(removeFlags);
        add(addFlags);
    }

    constexpr void clear()
    {
        value = static_cast<Enum>(0);
    }

    constexpr Enum get() const
    {
        return value;
    }

    constexpr explicit operator Enum() const
    {
        return value;
    }

    constexpr explicit operator bool() const
    {
        return static_cast<Underlying>(value) != 0;
    }

    constexpr Flags &operator=(Enum value)
    {
        this->value = value;
        return *this;
    }

    constexpr Flags &operator|=(Enum flags)
    {
        add(flags);
        return *this;
    }

    constexpr Flags &operator&=(Enum flags)
    {
        value = static_cast<Enum>(static_cast<Underlying>(value) & static_cast<Underlying>(flags));

        return *this;
    }

    constexpr Flags &operator^=(Enum flags)
    {
        value = static_cast<Enum>(static_cast<Underlying>(value) ^ static_cast<Underlying>(flags));

        return *this;
    }

private:
    Enum value{};
};

template <typename Enum>
constexpr Flags<Enum> operator|(Enum lhs, Enum rhs)
{
    static_assert(std::is_enum_v<Enum>);

    Flags<Enum> result{lhs};
    result.add(rhs);
    return result;
}

template <typename Enum>
constexpr Flags<Enum> operator|(Flags<Enum> lhs, Enum rhs)
{
    lhs.add(rhs);
    return lhs;
}

template <typename Enum>
constexpr Flags<Enum> operator|(Enum lhs, Flags<Enum> rhs)
{
    rhs.add(lhs);
    return rhs;
}

template <typename Enum>
constexpr Flags<Enum> operator&(Enum lhs, Enum rhs)
{
    using Underlying = std::underlying_type_t<Enum>;

    return Flags<Enum>(
        static_cast<Enum>(static_cast<Underlying>(lhs) & static_cast<Underlying>(rhs))
    );
}

template <typename Enum>
constexpr Flags<Enum> operator&(Flags<Enum> lhs, Enum rhs)
{
    lhs &= rhs;
    return lhs;
}

template <typename Enum>
constexpr Flags<Enum> operator&(Enum lhs, Flags<Enum> rhs)
{
    rhs &= lhs;
    return rhs;
}

template <typename Enum>
constexpr Flags<Enum> operator^(Enum lhs, Enum rhs)
{
    using Underlying = std::underlying_type_t<Enum>;

    return Flags<Enum>(
        static_cast<Enum>(static_cast<Underlying>(lhs) ^ static_cast<Underlying>(rhs))
    );
}

template <typename Enum>
constexpr Flags<Enum> operator^(Flags<Enum> lhs, Enum rhs)
{
    lhs ^= rhs;
    return lhs;
}

template <typename Enum>
constexpr Flags<Enum> operator^(Enum lhs, Flags<Enum> rhs)
{
    rhs ^= lhs;
    return rhs;
}
