#pragma once

#include <maths/Maths.h>

namespace tk {
class Camera
{
  public:
    Camera(
        Vector3d position = Vector3d(0.0, 0.0, 0.0),
        Vector3d target = Vector3d(0.0, 0.0, -1.0));
    ~Camera(){};

    void rotate(double pitch, double yaw) noexcept;
    inline void rotate(const Vector2d& by) noexcept { rotate(by.x, by.y); }
    inline void move(const Vector3d& direction) noexcept { m_position += direction; };
    inline void teleport(const Vector3d& toLocation) noexcept { m_position = toLocation; };

    inline Matrix4f getView() const { return maths::matrix::lookAt(m_position, m_position - m_direction, Vector3d(0.0, 1.0, 0.0)); }
    inline Vector3d getDirection() const noexcept { return m_direction; }
    inline Vector3d getForward() const noexcept { return m_forward; }
    inline Vector3d getPosition() const noexcept { return m_position; }
    inline Vector3d getRight() const noexcept { return m_right; }
    inline Vector3d getUp() const noexcept { return m_up; }

  private:
    Vector3d m_position;
    Vector3d m_direction;

    Vector3d m_forward;  // Like direction, but it's the way, not where the player looks
    Vector3d m_right;
    Vector3d m_up;

    double m_yaw = 0, m_pitch = 0;
};
}  // namespace tk
