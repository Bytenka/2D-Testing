#pragma once

#include <maths/Maths.h>

namespace tk {
struct Transform
{
  public:
    Transform();
    Transform(const Vector3f& position);
    Transform(const Vector3f& position, const Vector3f& rotation);
    Transform(const Vector3f& position, const Vector3f rotation, const Vector3f& scale);
    virtual ~Transform();

    inline void setCenter(const Vector3f& localCenter) noexcept { m_center = localCenter * scale; }
    inline const Vector3f& getCenter() const noexcept { return m_center; }

  public:
    Vector3f position;
    Vector3f rotation;
    Vector3f scale;

  private:
    Vector3f m_center;
};
}  // namespace tk