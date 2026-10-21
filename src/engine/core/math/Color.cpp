#include "engine/core/math/Color.hpp"

#include "engine/core/math/Math.hpp"

Color::Color() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}

Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

Color Color::white()
{
    return Color{1.0f, 1.0f, 1.0f, 1.0f};
}

Color Color::black()
{
    return Color{0.0f, 0.0f, 0.0f, 1.0f};
}

Color Color::red()
{
    return Color{1.0f, 0.0f, 0.0f, 1.0f};
}

Color Color::green()
{
    return Color{0.0f, 1.0f, 0.0f, 1.0f};
}

Color Color::blue()
{
    return Color{0.0f, 0.0f, 1.0f, 1.0f};
}

Color Color::yellow()
{
    return Color{1.0f, 1.0f, 0.0f, 1.0f};
}

Color Color::cyan()
{
    return Color{0.0f, 1.0f, 1.0f, 1.0f};
}

Color Color::magenta()
{
    return Color{1.0f, 0.0f, 1.0f, 1.0f};
}

Color Color::transparent()
{
    return Color{0.0f, 0.0f, 0.0f, 0.0f};
}

Color Color::fromHex(uint32_t hexCode)
{
    uint8_t red = (hexCode >> 24) & 0xFF;
    uint8_t green = (hexCode >> 16) & 0xFF;
    uint8_t blue = (hexCode >> 8) & 0xFF;
    uint8_t alpha = hexCode & 0xFF;

    return Color{
        static_cast<float>(red) / Math::MAX_UINT8,
        static_cast<float>(green) / Math::MAX_UINT8,
        static_cast<float>(blue) / Math::MAX_UINT8,
        static_cast<float>(alpha) / Math::MAX_UINT8
    };
}

uint32_t Color::toHex() const
{
    const Color color = clamped();

    const uint32_t red = static_cast<uint32_t>(color.r * Math::MAX_UINT8 + 0.5f);
    const uint32_t green = static_cast<uint32_t>(color.g * Math::MAX_UINT8 + 0.5f);
    const uint32_t blue = static_cast<uint32_t>(color.b * Math::MAX_UINT8 + 0.5f);
    const uint32_t alpha = static_cast<uint32_t>(color.a * Math::MAX_UINT8 + 0.5f);

    uint32_t hexCode = (red << 24) | (green << 16) | (blue << 8) | alpha;

    return hexCode;
}

Color Color::fromRGBA16(const RGBA16 &color)
{
    uint8_t red = (color.value >> 12) & 0xF;
    uint8_t green = (color.value >> 8) & 0xF;
    uint8_t blue = (color.value >> 4) & 0xF;
    uint8_t alpha = color.value & 0xF;

    return Color{
        static_cast<float>(red) / Math::MAX_UINT4,
        static_cast<float>(green) / Math::MAX_UINT4,
        static_cast<float>(blue) / Math::MAX_UINT4,
        static_cast<float>(alpha) / Math::MAX_UINT4
    };
}

RGBA16 Color::toRGBA16() const
{
    const Color color = clamped();

    const uint8_t red = static_cast<uint8_t>(color.r * Math::MAX_UINT4 + 0.5f);
    const uint8_t green = static_cast<uint8_t>(color.g * Math::MAX_UINT4 + 0.5f);
    const uint8_t blue = static_cast<uint8_t>(color.b * Math::MAX_UINT4 + 0.5f);
    const uint8_t alpha = static_cast<uint8_t>(color.a * Math::MAX_UINT4 + 0.5f);

    uint16_t packed = static_cast<uint16_t>((red << 12) | (green << 8) | (blue << 4) | alpha);

    return RGBA16{packed};
}

Color Color::fromRGBA32(const RGBA32 &color)
{
    return Color{
        static_cast<float>(color.r) / Math::MAX_UINT8,
        static_cast<float>(color.g) / Math::MAX_UINT8,
        static_cast<float>(color.b) / Math::MAX_UINT8,
        static_cast<float>(color.a) / Math::MAX_UINT8
    };
}

RGBA32 Color::toRGBA32() const
{
    const Color color = clamped();

    const uint8_t red = static_cast<uint8_t>(color.r * Math::MAX_UINT8 + 0.5f);
    const uint8_t green = static_cast<uint8_t>(color.g * Math::MAX_UINT8 + 0.5f);
    const uint8_t blue = static_cast<uint8_t>(color.b * Math::MAX_UINT8 + 0.5f);
    const uint8_t alpha = static_cast<uint8_t>(color.a * Math::MAX_UINT8 + 0.5f);

    return RGBA32{red, green, blue, alpha};
}

Color Color::fromRGBA64(const RGBA64 &color)
{
    return Color{
        static_cast<float>(color.r) / Math::MAX_UINT16,
        static_cast<float>(color.g) / Math::MAX_UINT16,
        static_cast<float>(color.b) / Math::MAX_UINT16,
        static_cast<float>(color.a) / Math::MAX_UINT16
    };
}

RGBA64 Color::toRGBA64() const
{
    const Color color = clamped();

    const uint16_t red = static_cast<uint16_t>(color.r * Math::MAX_UINT16 + 0.5f);
    const uint16_t green = static_cast<uint16_t>(color.g * Math::MAX_UINT16 + 0.5f);
    const uint16_t blue = static_cast<uint16_t>(color.b * Math::MAX_UINT16 + 0.5f);
    const uint16_t alpha = static_cast<uint16_t>(color.a * Math::MAX_UINT16 + 0.5f);

    return RGBA64{red, green, blue, alpha};
}

Color Color::fromRGBA128UI(const RGBA128UI &color)
{
    return Color{
        static_cast<float>(color.r) / Math::MAX_UINT32,
        static_cast<float>(color.g) / Math::MAX_UINT32,
        static_cast<float>(color.b) / Math::MAX_UINT32,
        static_cast<float>(color.a) / Math::MAX_UINT32
    };
}

RGBA128UI Color::toRGBA128UI() const
{
    const Color color = clamped();

    return RGBA128UI{
        static_cast<uint32_t>(color.r * Math::MAX_UINT32 + 0.5f),
        static_cast<uint32_t>(color.g * Math::MAX_UINT32 + 0.5f),
        static_cast<uint32_t>(color.b * Math::MAX_UINT32 + 0.5f),
        static_cast<uint32_t>(color.a * Math::MAX_UINT32 + 0.5f)
    };
}

Color Color::fromHSL(const HSL &hsl)
{
    float h = std::fmod(hsl.h, 360.0f);

    if (h < 0.0f)
        h += 360.0f;

    const float s = Math::clamp(hsl.s, 0.0f, 1.0f);
    const float l = Math::clamp(hsl.l, 0.0f, 1.0f);
    const float a = Math::clamp(hsl.a, 0.0f, 1.0f);

    const float c = (1.0f - std::abs(2.0f * l - 1.0f)) * s;

    const float hPrime = h / 60.0f;
    const float x = c * (1.0f - std::abs(std::fmod(hPrime, 2.0f) - 1.0f));

    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;

    if (hPrime >= 0.0f && hPrime < 1.0f)
    {
        r = c;
        g = x;
    }
    else if (hPrime < 2.0f)
    {
        r = x;
        g = c;
    }
    else if (hPrime < 3.0f)
    {
        g = c;
        b = x;
    }
    else if (hPrime < 4.0f)
    {
        g = x;
        b = c;
    }
    else if (hPrime < 5.0f)
    {
        r = x;
        b = c;
    }
    else if (hPrime < 6.0f)
    {
        r = c;
        b = x;
    }

    const float m = l - c * 0.5f;

    return Color{r + m, g + m, b + m, hsl.a};
}

HSL Color::toHSL() const
{
    const float max = std::max({r, g, b});
    const float min = std::min({r, g, b});

    const float delta = max - min;

    HSL hsl{};
    hsl.a = a;

    // Achromatic
    if (Math::approximatelyEqual(delta, 0.0f))
    {
        hsl.h = 0.0f;
        hsl.s = 0.0f;
        hsl.l = (max + min) * 0.5f;

        return hsl;
    }

    hsl.l = (max + min) * 0.5f;

    // Saturation
    if (hsl.l <= 0.5f)
        hsl.s = delta / (max + min);
    else
        hsl.s = delta / (2.0f - max - min);

    // Hue
    if (Math::approximatelyEqual(max, r))
    {
        hsl.h = 60.0f * ((g - b) / delta);

        if (hsl.h < 0.0f)
            hsl.h += 360.0f;
    }
    else if (Math::approximatelyEqual(max, g))
    {
        hsl.h = 60.0f * (((b - r) / delta) + 2.0f);
    }
    else
    {
        hsl.h = 60.0f * (((r - g) / delta) + 4.0f);
    }

    return hsl;
}

Color Color::fromHSV(const HSV &hsv)
{
    float h = std::fmod(hsv.h, 360.0f);

    if (h < 0.0f)
        h += 360.0f;

    const float s = Math::clamp(hsv.s, 0.0f, 1.0f);
    const float v = Math::clamp(hsv.v, 0.0f, 1.0f);
    const float a = Math::clamp(hsv.a, 0.0f, 1.0f);

    const float c = v * s;

    const float hPrime = h / 60.0f;

    const float x = c * (1.0f - std::abs(std::fmod(hPrime, 2.0f) - 1.0f));

    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;

    if (hPrime < 1.0f)
    {
        r = c;
        g = x;
    }
    else if (hPrime < 2.0f)
    {
        r = x;
        g = c;
    }
    else if (hPrime < 3.0f)
    {
        g = c;
        b = x;
    }
    else if (hPrime < 4.0f)
    {
        g = x;
        b = c;
    }
    else if (hPrime < 5.0f)
    {
        r = x;
        b = c;
    }
    else
    {
        r = c;
        b = x;
    }

    const float m = v - c;

    return Color{r + m, g + m, b + m, a};
}

HSV Color::toHSV() const
{
    const float max = std::max({r, g, b});
    const float min = std::min({r, g, b});
    const float delta = max - min;

    HSV hsv{};
    hsv.v = max;
    hsv.a = a;

    // Achromatic
    if (Math::approximatelyEqual(delta, 0.0f))
    {
        hsv.h = 0.0f;
        hsv.s = 0.0f;

        return hsv;
    }

    // Saturation
    hsv.s = delta / max;

    // Hue
    if (Math::approximatelyEqual(max, r))
    {
        hsv.h = 60.0f * ((g - b) / delta);

        if (hsv.h < 0.0f)
            hsv.h += 360.0f;
    }
    else if (Math::approximatelyEqual(max, g))
    {
        hsv.h = 60.0f * (((b - r) / delta) + 2.0f);
    }
    else
    {
        hsv.h = 60.0f * (((r - g) / delta) + 4.0f);
    }

    return hsv;
}

Color Color::clamped() const
{
    return Color{
        Math::clamp(r, 0.0f, 1.0f),
        Math::clamp(g, 0.0f, 1.0f),
        Math::clamp(b, 0.0f, 1.0f),
        Math::clamp(a, 0.0f, 1.0f)
    };
}

Color Color::lerp(const Color &a, const Color &b, float t)
{
    return Color{
        Math::lerp(a.r, b.r, t),
        Math::lerp(a.g, b.g, t),
        Math::lerp(a.b, b.b, t),
        Math::lerp(a.a, b.a, t)
    };
}

Color Color::operator+(const Color &other) const
{
    return {r + other.r, g + other.g, b + other.b, a + other.a};
}

Color &Color::operator+=(const Color &other)
{
    *this = *this + other;
    return *this;
}

Color Color::operator-(const Color &other) const
{
    return {r - other.r, g - other.g, b - other.b, a - other.a};
}

Color &Color::operator-=(const Color &other)
{
    *this = *this - other;
    return *this;
}

Color Color::operator*(float scalar) const
{
    return {r * scalar, g * scalar, b * scalar, a * scalar};
}

Color &Color::operator*=(float scalar)
{
    *this = *this * scalar;
    return *this;
}

Color Color::operator*(const Color &other) const
{
    return Color{r * other.r, g * other.g, b * other.b, a * other.a};
}

Color &Color::operator*=(const Color &other)
{
    *this = *this * other;
    return *this;
}

Color Color::operator/(float scalar) const
{
    return {r / scalar, g / scalar, b / scalar, a / scalar};
}

Color &Color::operator/=(float scalar)
{
    *this = *this / scalar;
    return *this;
}

bool Color::operator==(const Color &other) const
{
    return Math::approximatelyEqual(r, other.r) && Math::approximatelyEqual(g, other.g) &&
           Math::approximatelyEqual(b, other.b) && Math::approximatelyEqual(a, other.a);
}

bool Color::operator!=(const Color &other) const
{
    return !(*this == other);
}
