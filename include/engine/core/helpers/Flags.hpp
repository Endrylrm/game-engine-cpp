#pragma once

template <typename Enum>
class Flags
{
    static_assert(std::is_enum_v<Enum>);

public:
    using Underlying = std::underlying_type_t<Enum>;

    constexpr Flags() = default;
    constexpr explicit Flags(Enum value) : value(value) {}

    constexpr void add(Enum flags)
    {
        value = static_cast<Enum>(
            static_cast<Underlying>(value) |
            static_cast<Underlying>(flags));
    }

    constexpr void remove(Enum flags)
    {
        value = static_cast<Enum>(
            static_cast<Underlying>(value) &
            ~static_cast<Underlying>(flags));
    }

    constexpr bool has(Enum flags) const
    {
        return (static_cast<Underlying>(value) &
                static_cast<Underlying>(flags)) == static_cast<Underlying>(flags);
    }

    constexpr bool hasAny(Enum flags) const
    {
        return (static_cast<Underlying>(value) &
                static_cast<Underlying>(flags)) != 0;
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

    constexpr operator Enum() const
    {
        return value;
    }

    constexpr Flags &operator=(Enum value)
    {
        this->value = value;
        return *this;
    }

private:
    Enum value{};
};
