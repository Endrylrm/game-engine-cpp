#pragma once
#include <cstdint>

// RGBA4444 - 4 bits per channel - packed unsigned integer
// Layout - RRRR GGGG BBBB AAAA
struct RGBA16
{
    uint16_t value;
};

// RGBA8888 - 8 bits per channel - unsigned integer
struct RGBA32
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

// RGBA16161616 - 16 bits per channel - unsigned integer
struct RGBA64
{
    uint16_t r;
    uint16_t g;
    uint16_t b;
    uint16_t a;
};

// RGBA32323232 - 32 bits per channel - unsigned integer
struct RGBA128UI
{
    uint32_t r;
    uint32_t g;
    uint32_t b;
    uint32_t a;
};

struct HSL
{
    float h;
    float s;
    float l;
    float a;
};

struct HSV
{
    float h;
    float s;
    float v;
    float a;
};

struct Color
{
    Color();
    Color(float r, float g, float b, float a = 1.0f);

    static Color white();
    static Color black();
    static Color red();
    static Color green();
    static Color blue();
    static Color yellow();
    static Color cyan();
    static Color magenta();
    static Color transparent();

    // Converts a Hexadecimal 0xRRGGBBAA to a Color.
    static Color from_hex(uint32_t hex_code);
    uint32_t to_hex() const;

    // Converts a RGBA4444 to a Color.
    static Color from_rgba_16(const RGBA16 &color);
    RGBA16 to_rgba_16() const;

    // Converts a RGBA8888 to a Color.
    static Color from_rgba_32(const RGBA32 &color);
    RGBA32 to_rgba_32() const;

    // Converts a RGBA16161616 to a Color.
    static Color from_rgba_64(const RGBA64 &color);
    RGBA64 to_rgba_64() const;

    // Converts a unsigned integer RGBA32323232 to a Color.
    static Color from_rgba_128_ui(const RGBA128UI &color);
    RGBA128UI to_rgba_128_ui() const;

    static Color from_hsl(const HSL &hsl);
    HSL to_hsl() const;

    static Color from_hsv(const HSV &hsv);
    HSV to_hsv() const;

    Color clamped() const;
    static Color lerp(const Color &a, const Color &b, float t);

    Color operator+(const Color &other) const;
    Color &operator+=(const Color &other);

    Color operator-(const Color &other) const;
    Color &operator-=(const Color &other);

    Color operator*(float scalar) const;
    Color &operator*=(float scalar);

    Color operator*(const Color &other) const;
    Color &operator*=(const Color &other);

    Color operator/(float scalar) const;
    Color &operator/=(float scalar);

    bool operator==(const Color &other) const;
    bool operator!=(const Color &other) const;

    float r;
    float g;
    float b;
    float a;
};
