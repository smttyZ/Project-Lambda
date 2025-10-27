#pragma once

namespace lambda::core {

struct RGBColor {
    float r, g, b;
};

struct RGBAColor {
    float r, g, b, a{1.0f};
};

struct CMYKColor {
    float c, m, y, k;
};

enum class LDColor {
    Red,
    Green,
    Blue,
    White,
    Black,
    Yellow,
    Cyan,
    Magenta,
    Transparent,
    Gray,
    DEBUG_COLOR, // A bright purple color reserved for debugging purposes
    None        // if ever a color isn't needed, but the screen must still be cleared.
};
}