#pragma once

#include <string>
#include <ostream>
#include <math.h>

namespace tk
{
template <typename T>
struct Vector3
{
    T x, y, z;

    Vector3(T x, T y, T z) : x(x), y(y), z(z) {}
    Vector3(T scalar) : Vector3((T)scalar, (T)scalar, (T)scalar) {}
    Vector3() : Vector3((T)0.0) {}

    inline Vector3<T> &add(const Vector3<T> &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    inline Vector3<T> &subtract(const Vector3<T> &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    inline Vector3<T> &multiply(const Vector3<T> &other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }

    inline Vector3<T> &divide(const Vector3<T> &other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
    }

    inline Vector3<T> &add(T value)
    {
        x += value;
        y += value;
        z += value;
        return *this;
    }

    inline Vector3<T> &subtract(T value)
    {
        x -= value;
        y -= value;
        z -= value;
        return *this;
    }

    inline Vector3<T> &multiply(T value)
    {
        x *= value;
        y *= value;
        z *= value;
        return *this;
    }

    inline Vector3<T> &divide(T value)
    {
        x /= value;
        y /= value;
        z /= value;
        return *this;
    }

    inline bool equals(const Vector3<T> &other) { return x == other.x && y == other.y && z == other.z; }

    friend Vector3<T> operator+(Vector3<T> left, const Vector3<T> &right) { return left.add(right); }
    friend Vector3<T> operator-(Vector3<T> left, const Vector3<T> &right) { return left.subtract(right); }
    friend Vector3<T> operator*(Vector3<T> left, const Vector3<T> &right) { return left.multiply(right); }
    friend Vector3<T> operator/(Vector3<T> left, const Vector3<T> &right) { return left.divide(right); }

    friend Vector3<T> operator+(Vector3<T> left, T value) { return left.add(value); }
    friend Vector3<T> operator-(Vector3<T> left, T value) { return left.subtract(value); }
    friend Vector3<T> operator*(Vector3<T> left, T value) { return left.multiply(value); }
    friend Vector3<T> operator/(Vector3<T> left, T value) { return left.divide(value); }

    bool operator==(const Vector3<T> &other) const { return equals(other); }
    bool operator!=(const Vector3<T> &other) const { return !equals(other); }

    Vector3<T> &operator+=(const Vector3<T> &other) { return add(other); }
    Vector3<T> &operator-=(const Vector3<T> &other) { return subtract(other); }
    Vector3<T> &operator*=(const Vector3<T> &other) { return multiply(other); }
    Vector3<T> &operator/=(const Vector3<T> &other) { return divide(other); }

    Vector3<T> &operator+=(double value) { return add(value); }
    Vector3<T> &operator-=(double value) { return subtract(value); }
    Vector3<T> &operator*=(double value) { return multiply(value); }
    Vector3<T> &operator/=(double value) { return divide(value); }

    inline double magnitude2() const noexcept { return x * x + y * y + z * z; }
    inline double magnitude() const noexcept { return sqrt(magnitude2()); }
    inline Vector3<T> normalised() const noexcept { return *this / magnitude(); }
    //double dot(const Vector3 &other) const noexcept;

    inline std::string toString() const noexcept { return std::string("(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")"); }

    friend std::ostream &operator<<(std::ostream &stream, const Vector3<T> &vec)
    {
        stream << vec.toString();
        return stream;
    }
};
} // namespace tk