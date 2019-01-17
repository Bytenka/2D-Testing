#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Vector1.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

namespace tk
{
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

namespace maths
{
namespace matrix
{
inline const float *value_ptr(const Matrix2f &mat) { return glm::value_ptr(mat); }
} // namespace matrix
} // namespace maths
} // namespace tk
