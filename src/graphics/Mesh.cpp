#include "pch.h"
#include "Mesh.h"

#include "Vertex.h"
#include "Color.h"

#include <array>

#include <system/Log.h>

namespace tk {
Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

// public:

void Mesh::addVertex(const Vertex& vertex) noexcept
{
    addPosition(vertex.position);
    addColor(vertex.color);
    addTexture(vertex.texture);
}

std::vector<Vector3f> Mesh::getVertices() const noexcept
{
    std::vector<Vector3f> toReturn;
    toReturn.reserve(m_vertices.size() * 3);  // Reserve exact size, to prevent the reallocation of memory

    for (unsigned i = 0 + 0; i < m_vertices.size(); i += (3 + 4 + 2)) {
        Vector3f v = {
            m_vertices[i + 0],
            m_vertices[i + 1],
            m_vertices[i + 2]};

        toReturn.push_back(v);
    }

    return toReturn;
}

std::vector<Color> Mesh::getColors() const noexcept
{
    std::vector<Color> toReturn;
    toReturn.reserve(m_vertices.size() * 3);  // Reserve exact size, to prevent the reallocation of memory

    for (unsigned i = 0 + 3; i < m_vertices.size(); i += (3 + 4 + 2)) {
        Color v(
            (ColorValue)(m_vertices[i + 0] * 255),
            (ColorValue)(m_vertices[i + 1] * 255),
            (ColorValue)(m_vertices[i + 2] * 255),
            (ColorValue)(m_vertices[i + 3] * 255));

        toReturn.push_back(v);
    }

    return toReturn;
}

std::vector<Vector2f> Mesh::getTextures() const noexcept
{
    std::vector<Vector2f> toReturn;
    toReturn.reserve(m_vertices.size() * 3);  // Reserve exact size, to prevent the reallocation of memory

    for (unsigned i = 3 + 4; i < m_vertices.size(); i += (3 + 4 + 2)) {
        Vector2f v = {
            m_vertices[i + 0],
            m_vertices[i + 1]};

        toReturn.push_back(v);
    }

    return toReturn;
}
// private:

void Mesh::addPosition(const Vector3f& pos) noexcept
{
    m_vertices.push_back(pos.x);
    m_vertices.push_back(pos.y);
    m_vertices.push_back(pos.z);
}

void Mesh::addColor(const Color& col) noexcept
{
    auto v = col.normalized();

    m_vertices.push_back(v.x);
    m_vertices.push_back(v.y);
    m_vertices.push_back(v.z);
    m_vertices.push_back(v.w);
}

void Mesh::addTexture(const Vector2f& tex) noexcept
{
    m_vertices.push_back(tex.x);
    m_vertices.push_back(tex.y);
}
}  // namespace tk