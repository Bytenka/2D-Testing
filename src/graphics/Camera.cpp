#include "pch.h"
#include "Camera.h"

namespace tk {
Camera::Camera(Vector3d position, Vector3d target)
    : m_position(position)
{
    // Gets the local right vector by using the direction vector and up vector,
    // and getting the "normal" vector of the plane created by these vectors (done with cross product)

    // Something is up here. initialDir.z and .x should be inverted,
    // and "-asin" is incorrect. It works, but something is wrong
    // Adding PI or other offset is expected in some cases
    Vector3d initialDir = (target - position).normalised();
    m_yaw = maths::toDegrees(atan2(initialDir.z, initialDir.x) + maths::PI);
    m_pitch = maths::toDegrees(-asin(initialDir.y));
    //rotate(0, 0);
}

void Camera::rotate(double pitch, double yaw)
{
    m_pitch += pitch;
    m_yaw += yaw;

    if (m_pitch < -89.99999)
        m_pitch = -89.99999;

    if (m_pitch > 89.99999)
        m_pitch = 89.99999;

    if (m_yaw > 180.0)
        m_yaw -= 360.0;

    if (m_yaw < -180.0)
        m_yaw += 360.0;

    Vector3d newRot;
    newRot.x = cos(maths::toRadians(m_pitch)) * cos(maths::toRadians(m_yaw));
    newRot.y = sin(maths::toRadians(m_pitch));
    newRot.z = cos(maths::toRadians(m_pitch)) * sin(maths::toRadians(m_yaw));

    m_direction = newRot.normalised();
    m_right = maths::vector::cross(Vector3d(0.0, 1.0, 0.0), m_direction).normalised();
    m_up = maths::vector::cross(m_direction, m_right).normalised();
    m_forward = maths::vector::cross(Vector3d(0.0, 1.0, 0.0), m_right).normalised();

    //LOG_TRACE("dir: {}, {}, {}", m_direction.x, m_direction.y, m_direction.z);
    //LOG_TRACE("rig: {}, {}, {}", m_right.x, m_right.y, m_right.z);
    //LOG_TRACE("up : {}, {}, {}", m_up.x, m_up.y, m_up.z);
    //LOG_TRACE("for: {}, {}, {}\n\n", m_forward.x, m_forward.y, m_forward.z);
}
}  // namespace tk