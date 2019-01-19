#pragma once

#include <string>
#include <ostream>
#include <math.h>

namespace tk {
template<typename T>
struct Vector4
{
    T x, y, z, w;

    Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
    Vector4(T scalar) : Vector4((T)scalar, (T)scalar, (T)scalar, (T)scalar) {}
    Vector4() : Vector4((T)0.0) {}

    inline Vector4<T>& add(const Vector4<T>& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }

    inline Vector4<T>& subtract(const Vector4<T>& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
    }

    inline Vector4<T>& multiply(const Vector4<T>& other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        w *= other.w;
        return *this;
    }

    inline Vector4<T>& divide(const Vector4<T>& other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        w /= other.w;
        return *this;
    }

    inline Vector4<T>& add(T value)
    {
        x += value;
        y += value;
        z += value;
        w += value;
        return *this;
    }

    inline Vector4<T>& subtract(T value)
    {
        x -= value;
        y -= value;
        z -= value;
        w -= value;
        return *this;
    }

    inline Vector4<T>& multiply(T value)
    {
        x *= value;
        y *= value;
        z *= value;
        w *= value;
        return *this;
    }

    inline Vector4<T>& divide(T value)
    {
        x /= value;
        y /= value;
        z /= value;
        w /= value;
        return *this;
    }

    inline bool equals(const Vector4<T>& other) { return x == other.x && y == other.y && z == other.z && w == other.w; }

    friend Vector4<T> operator+(Vector4<T> left, const Vector4<T>& right) { return left.add(right); }
    friend Vector4<T> operator-(Vector4<T> left, const Vector4<T>& right) { return left.subtract(right); }
    friend Vector4<T> operator*(Vector4<T> left, const Vector4<T>& right) { return left.multiply(right); }
    friend Vector4<T> operator/(Vector4<T> left, const Vector4<T>& right) { return left.divide(right); }

    friend Vector4<T> operator+(Vector4<T> left, T value) { return left.add(value); }
    friend Vector4<T> operator-(Vector4<T> left, T value) { return left.subtract(value); }
    friend Vector4<T> operator*(Vector4<T> left, T value) { return left.multiply(value); }
    friend Vector4<T> operator/(Vector4<T> left, T value) { return left.divide(value); }

    bool operator==(const Vector4<T>& other) const { return equals(other); }
    bool operator!=(const Vector4<T>& other) const { return !equals(other); }

    Vector4<T>& operator+=(const Vector4<T>& other) { return add(other); }
    Vector4<T>& operator-=(const Vector4<T>& other) { return subtract(other); }
    Vector4<T>& operator*=(const Vector4<T>& other) { return multiply(other); }
    Vector4<T>& operator/=(const Vector4<T>& other) { return divide(other); }

    Vector4<T>& operator+=(double value) { return add(value); }
    Vector4<T>& operator-=(double value) { return subtract(value); }
    Vector4<T>& operator*=(double value) { return multiply(value); }
    Vector4<T>& operator/=(double value) { return divide(value); }

    inline double magnitude2() const noexcept { return x * x + y * y + z * z + w * w; }
    inline double magnitude() const noexcept { return sqrt(magnitude2()); }
    inline Vector4<T> normalised() const noexcept { return *this / magnitude(); }
    //double dot(const Vector4 &other) const noexcept;

    inline std::string toString() const noexcept { return std::string("(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w) + ")"); }

    friend std::ostream& operator<<(std::ostream& stream, const Vector4<T>& vec)
    {
        stream << vec.toString();
        return stream;
    }
};
}  // namespace tk