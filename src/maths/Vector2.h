#pragma once

#include <string>
#include <ostream>
#include <math.h>

namespace tk
{
template <typename T>
struct Vector2
{
    T x, y;

    Vector2(T x, T y) : x(x), y(y) {}
    Vector2(T scalar) : Vector2((T)scalar, (T)scalar) {}
    Vector2() : Vector2((T)0.0) {}

    inline Vector2<T> &add(const Vector2<T> &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    inline Vector2<T> &subtract(const Vector2<T> &other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    inline Vector2<T> &multiply(const Vector2<T> &other)
    {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    inline Vector2<T> &divide(const Vector2<T> &other)
    {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    inline Vector2<T> &add(T value)
    {
        x += value;
        y += value;
        return *this;
    }

    inline Vector2<T> &subtract(T value)
    {
        x -= value;
        y -= value;
        return *this;
    }

    inline Vector2<T> &multiply(T value)
    {
        x *= value;
        y *= value;
        return *this;
    }

    inline Vector2<T> &divide(T value)
    {
        x /= value;
        y /= value;
        return *this;
    }

    inline bool equals(const Vector2<T> &other) { return x == other.x && y == other.y; }

    friend Vector2<T> operator+(Vector2<T> left, const Vector2<T> &right) { return left.add(right); }
    friend Vector2<T> operator-(Vector2<T> left, const Vector2<T> &right) { return left.subtract(right); }
    friend Vector2<T> operator*(Vector2<T> left, const Vector2<T> &right) { return left.multiply(right); }
    friend Vector2<T> operator/(Vector2<T> left, const Vector2<T> &right) { return left.divide(right); }

    friend Vector2<T> operator+(Vector2<T> left, T value) { return left.add(value); }
    friend Vector2<T> operator-(Vector2<T> left, T value) { return left.subtract(value); }
    friend Vector2<T> operator*(Vector2<T> left, T value) { return left.multiply(value); }
    friend Vector2<T> operator/(Vector2<T> left, T value) { return left.divide(value); }

    bool operator==(const Vector2<T> &other) const { return equals(other); }
    bool operator!=(const Vector2<T> &other) const { return !equals(other); }

    Vector2<T> &operator+=(const Vector2<T> &other) { return add(other); }
    Vector2<T> &operator-=(const Vector2<T> &other) { return subtract(other); }
    Vector2<T> &operator*=(const Vector2<T> &other) { return multiply(other); }
    Vector2<T> &operator/=(const Vector2<T> &other) { return divide(other); }

    Vector2<T> &operator+=(double value) { return add(value); }
    Vector2<T> &operator-=(double value) { return subtract(value); }
    Vector2<T> &operator*=(double value) { return multiply(value); }
    Vector2<T> &operator/=(double value) { return divide(value); }

    inline double magnitude2() const noexcept { return x * x + y * y; }
    inline double magnitude() const noexcept { return sqrt(magnitude2()); }
    inline Vector2<T> normalised() const noexcept { return *this / magnitude(); }
    //double dot(const Vector2 &other) const noexcept;

    inline std::string toString() const noexcept { return std::string("(" + std::to_string(x) + ", " + std::to_string(y) + ")"); }

    friend std::ostream &operator<<(std::ostream &stream, const Vector2<T> &vec)
    {
        stream << vec.toString();
        return stream;
    }
};
} // namespace tk