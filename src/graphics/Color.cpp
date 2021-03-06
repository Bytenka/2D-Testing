#include "pch.h"
#include "Color.h"

namespace tk {

Color::Color(ColorValue red, ColorValue green, ColorValue blue, ColorValue alpha)
    : red(red), green(green), blue(blue), alpha(alpha) {}

Color::Color(ColorValue gray, ColorValue alpha)
    : Color(gray, gray, gray, alpha) {}

Color::Color() : Color(127, 127, 0) {}

}  // namespace tk