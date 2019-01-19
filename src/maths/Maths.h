#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <math.h>

#include "Vector1.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

namespace tk {
#ifdef MATHS_USES_GLM
// Vectors //
typedef glm::dvec1 Vector1d;
typedef glm::dvec2 Vector2d;
typedef glm::dvec3 Vector3d;
typedef glm::dvec4 Vector4d;

typedef glm::fvec1 Vector1f;
typedef glm::fvec2 Vector2f;
typedef glm::fvec3 Vector3f;
typedef glm::fvec4 Vector4f;

typedef glm::uvec1 Vector1u;
typedef glm::uvec2 Vector2u;
typedef glm::uvec3 Vector3u;
typedef glm::uvec4 Vector4u;

typedef glm::ivec1 Vector1i;
typedef glm::ivec2 Vector2i;
typedef glm::ivec3 Vector3i;
typedef glm::ivec4 Vector4i;

typedef glm::bvec1 Vector1b;
typedef glm::bvec2 Vector2b;
typedef glm::bvec3 Vector3b;
typedef glm::bvec4 Vector4b;

#else
// Vectors //
typedef Vector1<double> Vector1d;
typedef Vector2<double> Vector2d;
typedef Vector3<double> Vector3d;
typedef Vector4<double> Vector4d;

typedef Vector1<float> Vector1f;
typedef Vector2<float> Vector2f;
typedef Vector3<float> Vector3f;
typedef Vector4<float> Vector4f;

typedef Vector1<unsigned int> Vector1u;
typedef Vector2<unsigned int> Vector2u;
typedef Vector3<unsigned int> Vector3u;
typedef Vector4<unsigned int> Vector4u;

typedef Vector1<int> Vector1i;
typedef Vector2<int> Vector2i;
typedef Vector3<int> Vector3i;
typedef Vector4<int> Vector4i;

typedef Vector1<bool> Vector1b;
typedef Vector2<bool> Vector2b;
typedef Vector3<bool> Vector3b;
typedef Vector4<bool> Vector4b;

#endif

// Matrices //
typedef glm::mat2 Matrix2f;
typedef glm::mat3 Matrix3f;
typedef glm::mat4 Matrix4f;

namespace maths {
    const double PI = 3.14159265359;
    const double HALF_PI = PI / 2;

    inline double toDegrees(double radians) noexcept { return (180 / PI * radians); }
    inline double toRadians(double degrees) noexcept { return (PI / 180 * degrees); }

    namespace vector {
        inline Vector3d cross(const Vector3d& x, const Vector3d& y) noexcept
        {
            glm::dvec3 r = glm::cross(glm::dvec3(x.x, x.y, x.z), glm::dvec3(y.x, y.y, y.z));
            return {r.x, r.y, r.z};
        }
    }  // namespace vector

    namespace matrix {
        inline const float* value_ptr(const Matrix4f& mat) noexcept { return glm::value_ptr(mat); }
        inline Matrix4f lookAt(const Vector3d& eye, const Vector3d& center, const Vector3d& up) noexcept { return glm::lookAt(glm::vec3(eye.x, eye.y, eye.z), glm::vec3(center.x, center.y, center.z), glm::vec3(up.x, up.y, up.z)); }
        inline Matrix4f ortho(float left, float right, float bottom, float top) noexcept { return glm::ortho(left, right, bottom, top); }
        inline Matrix4f translate(const Matrix4f& m, const Vector3f& v) noexcept { return glm::translate(m, {v.x, v.y, v.z}); }
        inline Matrix4f scale(const Matrix4f& m, const Vector3f& v) noexcept { return glm::scale(m, {v.x, v.y, v.z}); }
        inline Matrix4f rotate(const Matrix4f& m, float angleRad, const Vector3f& v) noexcept { return glm::rotate(m, angleRad, {v.x, v.y, v.z}); }
    }  // namespace matrix
}  // namespace maths
}  // namespace tk
