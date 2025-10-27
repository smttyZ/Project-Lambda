#pragma once
#include "core/LDColor.hpp"

namespace lambda::core {

    inline RGBAColor ToRGB(const RGBColor& rgb) noexcept {
        return RGBAColor{rgb.r, rgb.g, rgb.b, 1.0f};
    }

    inline RGBAColor ToRGB(const RGBAColor& rgba) noexcept {
        return RGBAColor{rgba.r, rgba.g, rgba.b};
    }

    inline RGBAColor ToRGB(const CMYKColor& cmyk) noexcept {
        float r = (1.0f - cmyk.c) * (1.0f - cmyk.k);
        float g = (1.0f - cmyk.m) * (1.0f - cmyk.k);
        float b = (1.0f - cmyk.y) * (1.0f - cmyk.k);
        return {r, g, b, 1.0f};
    }

    inline RGBAColor ToRGB(LDColor color) noexcept {
    switch (color) {
        case LDColor::Red:   return {1, 0, 0, 1};
        case LDColor::Green: return {0, 1, 0, 1};
        case LDColor::Blue:  return {0, 0, 1, 1};
        case LDColor::Gray:  return {0.3f, 0.3f, 0.3f, 1};
        case LDColor::White: return {1, 1, 1, 1};
        case LDColor::Black: return {0, 0, 0, 1};
        case LDColor::Transparent: return {0, 0, 0, 0};
        case LDColor::DEBUG_COLOR: return {1, 0, 1, 1};
        default: return {0, 0, 0, 1};
    }
}

}