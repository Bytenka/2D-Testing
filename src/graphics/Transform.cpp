#include "pch.h"
#include "Transform.h"

namespace tk {

Transform::Transform(const Vector3f& position, const Vector3f rotation, const Vector3f& scale)
    : position(position), rotation(rotation), scale(scale) {}

Transform::Transform(const Vector3f& position, const Vector3f& rotation)
    : Transform(position, rotation, Vector3f(1.0f)) {}

Transform::Transform(const Vector3f& position)
    : Transform(position, Vector3f(0.0f), Vector3f(1.0f)) {}

Transform::Transform()
    : Transform(Vector3f(0.0f), Vector3f(0.0f), Vector3f(1.0f)) {}


Transform::~Transform()
{
}
}  // namespace tk