#pragma once

#include <maths/Maths.h>

typedef unsigned char ColorValue;

namespace tk {
struct Color
{
  public:
    Color();
    Color(ColorValue gray);
    Color(ColorValue gray, ColorValue alpha);
    Color(ColorValue red, ColorValue green, ColorValue blue);
    Color(ColorValue red, ColorValue green, ColorValue blue, ColorValue alpha);

    union {
        Vector4<ColorValue> asVector4;
        ColorValue red;
        ColorValue green;
        ColorValue blue;
        ColorValue alpha;
    };
};
}  // namespace tk