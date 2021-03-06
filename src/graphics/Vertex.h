#pragma once
#include <maths/Maths.h>

#include "Color.h"

namespace tk {

struct Vertex
{
  public:
    Vertex();
    Vertex(const Vector3f& position);
    Vertex(const Vector3f& position, const Vector2f& texture);
    Vertex(const Vector3f& position, const Color& color);
    Vertex(const Vector3f& position, const Color& color, const Vector2f& texture);

  public:
    Vector3f position;
    Color color;
    Vector2f texture;
};
}  // namespace tk