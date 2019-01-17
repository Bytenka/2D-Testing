#pragma once

#include <string>
#include <ostream>
#include <math.h>

namespace tk
{
template <typename T>
struct Vector1
{
    T x;

    Vector1(T x) : x(x) {}
    Vector1() : Vector1((T)0.0) {}

    inline Vector1<T> &add(const Vector1<T> &other)
    {
        x += other.x;
        return *this;
    }

    inline Vector1<T> &subtract(const Vector1<T> &other)
    {
        x -= other.x;
        return *this;
    }

    inline Vector1<T> &multiply(const Vector1<T> &other)
    {
        x *= other.x;
        return *this;
    }

    inline Vector1<T> &divide(const Vector1<T> &other)
    {
        x /= other.x;
        return *this;
    }

    inline Vector1<T> &add(T value)
    {
        x += value;
        return *this;
    }

    inline Vector1<T> &subtract(T value)
    {
        x -= value;
        return *this;
    }

    inline Vector1<T> &multiply(T value)
    {
        x *= value;
        return *this;
    }

    inline Vector1<T> &divide(T value)
    {
        x /= value;
        return *this;
    }

    inline bool equals(const Vector1<T> &other) { return x == other.x; }

    friend Vector1<T> operator+(Vector1<T> left, const Vector1<T> &right) { return left.add(right); }
    friend Vector1<T> operator-(Vector1<T> left, const Vector1<T> &right) { return left.subtract(right); }
    friend Vector1<T> operator*(Vector1<T> left, const Vector1<T> &right) { return left.multiply(right); }
    friend Vector1<T> operator/(Vector1<T> left, const Vector1<T> &right) { return left.divide(right); }

    friend Vector1<T> operator+(Vector1<T> left, T value) { return left.add(value); }
    friend Vector1<T> operator-(Vector1<T> left, T value) { return left.subtract(value); }
    friend Vector1<T> operator*(Vector1<T> left, T value) { return left.multiply(value); }
    friend Vector1<T> operator/(Vector1<T> left, T value) { return left.divide(value); }

    bool operator==(const Vector1<T> &other) const { return equals(other); }
    bool operator!=(const Vector1<T> &other) const { return !equals(other); }

    Vector1<T> &operator+=(const Vector1<T> &other) { return add(other); }
    Vector1<T> &operator-=(const Vector1<T> &other) { return subtract(other); }
    Vector1<T> &operator*=(const Vector1<T> &other) { return multiply(other); }
    Vector1<T> &operator/=(const Vector1<T> &other) { return divide(other); }

    Vector1<T> &operator+=(double value) { return add(value); }
    Vector1<T> &operator-=(double value) { return subtract(value); }
    Vector1<T> &operator*=(double value) { return multiply(value); }
    Vector1<T> &operator/=(double value) { return divide(value); }

    inline double magnitude2() const noexcept { return x * x; }
    inline double magnitude() const noexcept { return sqrt(magnitude2()); }
    inline Vector1<T> normalised() const noexcept { return *this / magnitude(); }
    //double dot(const Vector1 &other) const noexcept;

    inline std::string toString() const noexcept { return std::string("(" + std::to_string(x) + ")"); }

    friend std::ostream &operator<<(std::ostream &stream, const Vector1<T> &vec)
    {
        stream << vec.toString();
        return stream;
    }
};
} // namespace tk