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

Color Color::from_hex(uint32_t hex_code)
{
    uint8_t red = (hex_code >> 24) & 0xFF;
    uint8_t green = (hex_code >> 16) & 0xFF;
    uint8_t blue = (hex_code >> 8) & 0xFF;
    uint8_t alpha = hex_code & 0xFF;

    return Color{
        static_cast<float>(red / Math::MAX_UINT8),
        static_cast<float>(green / Math::MAX_UINT8),
        static_cast<float>(blue / Math::MAX_UINT8),
        static_cast<float>(alpha / Math::MAX_UINT8)
    };
}

uint32_t Color::to_hex() const
{
    const Color COLOR = clamped();

    const uint32_t RED = static_cast<uint32_t>(COLOR.r * Math::MAX_UINT8 + 0.5f);
    const uint32_t GREEN = static_cast<uint32_t>(COLOR.g * Math::MAX_UINT8 + 0.5f);
    const uint32_t BLUE = static_cast<uint32_t>(COLOR.b * Math::MAX_UINT8 + 0.5f);
    const uint32_t ALPHA = static_cast<uint32_t>(COLOR.a * Math::MAX_UINT8 + 0.5f);

    uint32_t hex_code = (RED << 24) | (GREEN << 16) | (BLUE << 8) | ALPHA;

    return hex_code;
}

Color Color::from_rgba_16(const RGBA16 &color)
{
    uint8_t red = (color.value >> 12) & 0xF;
    uint8_t green = (color.value >> 8) & 0xF;
    uint8_t blue = (color.value >> 4) & 0xF;
    uint8_t alpha = color.value & 0xF;

    return Color{
        static_cast<float>(red / Math::MAX_UINT4),
        static_cast<float>(green / Math::MAX_UINT4),
        static_cast<float>(blue / Math::MAX_UINT4),
        static_cast<float>(alpha / Math::MAX_UINT4)
    };
}

RGBA16 Color::to_rgba_16() const
{
    const Color COLOR = clamped();

    const uint8_t RED = static_cast<uint8_t>(COLOR.r * Math::MAX_UINT4 + 0.5f);
    const uint8_t GREEN = static_cast<uint8_t>(COLOR.g * Math::MAX_UINT4 + 0.5f);
    const uint8_t BLUE = static_cast<uint8_t>(COLOR.b * Math::MAX_UINT4 + 0.5f);
    const uint8_t ALPHA = static_cast<uint8_t>(COLOR.a * Math::MAX_UINT4 + 0.5f);

    uint16_t packed = static_cast<uint16_t>((RED << 12) | (GREEN << 8) | (BLUE << 4) | ALPHA);

    return RGBA16{packed};
}

Color Color::from_rgba_32(const RGBA32 &color)
{
    return Color{
        static_cast<float>(color.r / Math::MAX_UINT8),
        static_cast<float>(color.g / Math::MAX_UINT8),
        static_cast<float>(color.b / Math::MAX_UINT8),
        static_cast<float>(color.a / Math::MAX_UINT8)
    };
}

RGBA32 Color::to_rgba_32() const
{
    const Color COLOR = clamped();

    const uint8_t RED = static_cast<uint8_t>(COLOR.r * Math::MAX_UINT8 + 0.5f);
    const uint8_t GREEN = static_cast<uint8_t>(COLOR.g * Math::MAX_UINT8 + 0.5f);
    const uint8_t BLUE = static_cast<uint8_t>(COLOR.b * Math::MAX_UINT8 + 0.5f);
    const uint8_t ALPHA = static_cast<uint8_t>(COLOR.a * Math::MAX_UINT8 + 0.5f);

    return RGBA32{RED, GREEN, BLUE, ALPHA};
}

Color Color::from_rgba_64(const RGBA64 &color)
{
    return Color{
        static_cast<float>(color.r / Math::MAX_UINT16),
        static_cast<float>(color.g / Math::MAX_UINT16),
        static_cast<float>(color.b / Math::MAX_UINT16),
        static_cast<float>(color.a / Math::MAX_UINT16)
    };
}

RGBA64 Color::to_rgba_64() const
{
    const Color COLOR = clamped();

    const uint16_t RED = static_cast<uint16_t>(COLOR.r * Math::MAX_UINT16 + 0.5f);
    const uint16_t GREEN = static_cast<uint16_t>(COLOR.g * Math::MAX_UINT16 + 0.5f);
    const uint16_t BLUE = static_cast<uint16_t>(COLOR.b * Math::MAX_UINT16 + 0.5f);
    const uint16_t ALPHA = static_cast<uint16_t>(COLOR.a * Math::MAX_UINT16 + 0.5f);

    return RGBA64{RED, GREEN, BLUE, ALPHA};
}

Color Color::from_rgba_128_ui(const RGBA128UI &color)
{
    return Color{
        static_cast<float>(color.r / Math::MAX_UINT32),
        static_cast<float>(color.g / Math::MAX_UINT32),
        static_cast<float>(color.b / Math::MAX_UINT32),
        static_cast<float>(color.a / Math::MAX_UINT32)
    };
}

RGBA128UI Color::to_rgba_128_ui() const
{
    const Color COLOR = clamped();

    return RGBA128UI{
        static_cast<uint32_t>(COLOR.r * Math::MAX_UINT32 + 0.5f),
        static_cast<uint32_t>(COLOR.g * Math::MAX_UINT32 + 0.5f),
        static_cast<uint32_t>(COLOR.b * Math::MAX_UINT32 + 0.5f),
        static_cast<uint32_t>(COLOR.a * Math::MAX_UINT32 + 0.5f)
    };
}

Color Color::from_hsl(const HSL &hsl)
{
    float h = std::fmod(hsl.h, 360.0f);

    if (h < 0.0f)
        h += 360.0f;

    const float S = Math::clamp(hsl.s, 0.0f, 1.0f);
    const float L = Math::clamp(hsl.l, 0.0f, 1.0f);
    const float A = Math::clamp(hsl.a, 0.0f, 1.0f);

    const float C = (1.0f - std::abs(2.0f * L - 1.0f)) * S;

    const float H_PRIME = h / 60.0f;
    const float X = C * (1.0f - std::abs(std::fmod(H_PRIME, 2.0f) - 1.0f));

    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;

    if (H_PRIME >= 0.0f && H_PRIME < 1.0f)
    {
        r = C;
        g = X;
    }
    else if (H_PRIME < 2.0f)
    {
        r = X;
        g = C;
    }
    else if (H_PRIME < 3.0f)
    {
        g = C;
        b = X;
    }
    else if (H_PRIME < 4.0f)
    {
        g = X;
        b = C;
    }
    else if (H_PRIME < 5.0f)
    {
        r = X;
        b = C;
    }
    else if (H_PRIME < 6.0f)
    {
        r = C;
        b = X;
    }

    const float M = L - C * 0.5f;

    return Color{r + M, g + M, b + M, hsl.a};
}

HSL Color::to_hsl() const
{
    const float MAX = std::max({r, g, b});
    const float MIN = std::min({r, g, b});

    const float DELTA = MAX - MIN;

    HSL hsl{};
    hsl.a = a;

    // Achromatic
    if (Math::approximately_equal(DELTA, 0.0f))
    {
        hsl.h = 0.0f;
        hsl.s = 0.0f;
        hsl.l = (MAX + MIN) * 0.5f;

        return hsl;
    }

    hsl.l = (MAX + MIN) * 0.5f;

    // Saturation
    if (hsl.l <= 0.5f)
        hsl.s = DELTA / (MAX + MIN);
    else
        hsl.s = DELTA / (2.0f - MAX - MIN);

    // Hue
    if (Math::approximately_equal(MAX, r))
    {
        hsl.h = 60.0f * ((g - b) / DELTA);

        if (hsl.h < 0.0f)
            hsl.h += 360.0f;
    }
    else if (Math::approximately_equal(MAX, g))
    {
        hsl.h = 60.0f * (((b - r) / DELTA) + 2.0f);
    }
    else
    {
        hsl.h = 60.0f * (((r - g) / DELTA) + 4.0f);
    }

    return hsl;
}

Color Color::from_hsv(const HSV &hsv)
{
    float h = std::fmod(hsv.h, 360.0f);

    if (h < 0.0f)
        h += 360.0f;

    const float S = Math::clamp(hsv.s, 0.0f, 1.0f);
    const float V = Math::clamp(hsv.v, 0.0f, 1.0f);
    const float A = Math::clamp(hsv.a, 0.0f, 1.0f);

    const float C = V * S;

    const float H_PRIME = h / 60.0f;

    const float X = C * (1.0f - std::abs(std::fmod(H_PRIME, 2.0f) - 1.0f));

    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;

    if (H_PRIME < 1.0f)
    {
        r = C;
        g = X;
    }
    else if (H_PRIME < 2.0f)
    {
        r = X;
        g = C;
    }
    else if (H_PRIME < 3.0f)
    {
        g = C;
        b = X;
    }
    else if (H_PRIME < 4.0f)
    {
        g = X;
        b = C;
    }
    else if (H_PRIME < 5.0f)
    {
        r = X;
        b = C;
    }
    else
    {
        r = C;
        b = X;
    }

    const float M = V - C;

    return Color{r + M, g + M, b + M, A};
}

HSV Color::to_hsv() const
{
    const float MAX = std::max({r, g, b});
    const float MIN = std::min({r, g, b});
    const float DELTA = MAX - MIN;

    HSV hsv{};
    hsv.v = MAX;
    hsv.a = a;

    // Achromatic
    if (Math::approximately_equal(DELTA, 0.0f))
    {
        hsv.h = 0.0f;
        hsv.s = 0.0f;

        return hsv;
    }

    // Saturation
    hsv.s = DELTA / MAX;

    // Hue
    if (Math::approximately_equal(MAX, r))
    {
        hsv.h = 60.0f * ((g - b) / DELTA);

        if (hsv.h < 0.0f)
            hsv.h += 360.0f;
    }
    else if (Math::approximately_equal(MAX, g))
    {
        hsv.h = 60.0f * (((b - r) / DELTA) + 2.0f);
    }
    else
    {
        hsv.h = 60.0f * (((r - g) / DELTA) + 4.0f);
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
    return Math::approximately_equal(r, other.r) && Math::approximately_equal(g, other.g) &&
           Math::approximately_equal(b, other.b) && Math::approximately_equal(a, other.a);
}

bool Color::operator!=(const Color &other) const
{
    return !(*this == other);
}
