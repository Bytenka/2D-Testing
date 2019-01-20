#pragma once

#include "Color.h"

#include <maths/Maths.h>

#include <vector>

namespace tk {
struct Vertex;

class Mesh
{
  public:
    Mesh();
    ~Mesh();

    void addVertex(const Vertex& vertex) noexcept;
    inline void clear() noexcept { m_vertices.clear(); }

    inline const std::vector<float>& getData() const noexcept { return m_vertices; };
    inline unsigned getVerticesCount() const noexcept { return (unsigned)(m_vertices.size() / 3); }

    // These functions will build a new vector containing only the requested data
    // Copies are made, so calling them is slow
    std::vector<Vector3f> getVertices() const noexcept;
    std::vector<Color> getColors() const noexcept;
    std::vector<Vector2f> getTextures() const noexcept;

  private:
    void addPosition(const Vector3f& pos) noexcept;
    void addColor(const Color& col) noexcept;
    void addTexture(const Vector2f& tex) noexcept;

  private:
    std::vector<float> m_vertices;
};
}  // namespace tk