#include "pch.h"
#include "Color.h"

namespace tk {

Color::Color(ColorValue red, ColorValue green, ColorValue blue, ColorValue alpha)
    : asVector4(red, green, blue, alpha) {}

Color::Color(ColorValue red, ColorValue green, ColorValue blue)
    : asVector4(red, green, blue, 255) {}

Color::Color(ColorValue gray, ColorValue alpha)
    : Color(gray, gray, gray, alpha) {}

Color::Color(ColorValue gray)
    : Color(gray, 255) {}

Color::Color() : Color(127, 127, 0) {}

}  // namespace tk