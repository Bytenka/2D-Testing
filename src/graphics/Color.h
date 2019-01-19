#pragma once

#include <maths/Maths.h>

typedef unsigned char ColorValue;

namespace tk {
struct Color
{
  public:
    Color();
    explicit Color(ColorValue gray, ColorValue alpha = 255);
    Color(ColorValue red, ColorValue green, ColorValue blue, ColorValue alpha = 255);

    Vector4f normalized() const noexcept { return {red / 255.0f, green / 255.0f, blue / 255.0f, alpha / 255.0f}; }
    Vector4<ColorValue> asVector4() const noexcept { return {red, green, blue, alpha}; }

    ColorValue red;
    ColorValue green;
    ColorValue blue;
    ColorValue alpha;
};
}  // namespace tk