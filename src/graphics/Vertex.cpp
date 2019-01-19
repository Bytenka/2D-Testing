#include "pch.h"
#include "Vertex.h"

namespace tk {

Vertex::Vertex(const Vector3f& position, const Color& color, const Vector2f& texture)
    : position(position), color(color), texture(texture) {}

Vertex::Vertex(const Vector3f& position, const Color& color)
    : Vertex(position, color, 0.0f) {}

Vertex::Vertex(const Vector3f& position, const Vector2f& texture)
    : Vertex(position, Color(255), texture) {}

Vertex::Vertex(const Vector3f& position)
    : Vertex(position, Color(255), 0.0f) {}

Vertex::Vertex()
    : Vertex(0.0f, Color(255), 0.0f) {}

}  // namespace tk