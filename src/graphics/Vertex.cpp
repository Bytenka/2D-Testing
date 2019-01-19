#include "pch.h"
#include "Vertex.h"

namespace tk {

Vertex::Vertex(const Vector3f& position, const Color& color, const Vector2f& textureCoords)
    : position(position), color(color), textureCoords(textureCoords) {}

Vertex::Vertex(const Vector3f& position, const Color& color)
    : Vertex(position, color, 0.0f) {}

Vertex::Vertex(const Vector3f& position, const Vector2f& textureCoords)
    : Vertex(position, 255, textureCoords) {}

Vertex::Vertex(const Vector3f& position)
    : Vertex(position, 255, 0.0f) {}

Vertex::Vertex()
    : Vertex(0.0f, 255, 0.0f) {}

}  // namespace tk