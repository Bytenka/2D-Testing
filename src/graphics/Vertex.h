#pragma once
#include <maths/Maths.h>

#include "Color.h"

namespace tk {

struct Vertex
{
  public:
    Vertex();
    Vertex(const Vector3f& position);
    Vertex(const Vector3f& position, const Vector2f& textureCoords);
    Vertex(const Vector3f& position, const Color& color);
    Vertex(const Vector3f& position, const Color& color, const Vector2f& textureCoords);

    Vector3f position;
    Color color;
    Vector2f textureCoords;
};
}  // namespace tk