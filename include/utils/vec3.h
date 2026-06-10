#pragma once

#include <cmath>
#include <concepts>

template<typename T>
concept Vectorizable = requires(T a, T b) {
    // ops between same types
    { a + b } -> std::convertible_to<T>;
    { a - b } -> std::convertible_to<T>;
    { a * b } -> std::convertible_to<T>;
    { a / b } -> std::convertible_to<T>;

    // scalar ops
    { a * 1.0f } -> std::convertible_to<T>;
    { a / 1.0f } -> std::convertible_to<T>;
};

template<Vectorizable T>
class Vec3 {
    public:
        T x;
        T y;
        T z;
    

        Vec3(T x, T y, T z) : x(x), y(y), z(z) {};
        Vec3(T *arr) : x(arr[0]), y(arr[1]), z(arr[2]) {};
        Vec3() : x(), y(), z() {};
        ~Vec3() {};

        // compute the dot product between two vectors
        T dot(const Vec3<T>& other) const {
            return x * other.x + y * other.y + z * other.z;
        }

        // compute the norm of a vector
        T norm() const {
            return std::sqrt(dot(*this));
        }

        // normalize this vector in place
        void normalize() {
            *this /= norm();
        }

        // get a new vector that is the normalized version
        Vec3<T> normalized() {
            return *this / norm();
        }

        // compute the cross product
        Vec3<T> cross(Vec3<T>& other) {
            return {
                y * other.z - z * other.y,
                x * other.z - z * other.x,
                x * other.y - y * other.x
            };
        }



        // operator overloads
        // add two vectors
        friend Vec3<T> operator+(const Vec3<T>& lhs, const Vec3<T>& rhs) {
            return Vec3<T>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
        }

        // subtract a vector from another
        friend Vec3<T> operator-(const Vec3<T>& lhs, const Vec3<T>& rhs) {
            return Vec3<T>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
        }
        // unary negate a vector
        Vec3<T> operator-() const {
            return Vec3<T>(-x, -y, -z);
        }

        // component wise multiply two vectors
        friend Vec3<T> operator*(const Vec3<T>& lhs, const Vec3<T>& rhs) {
            return Vec3<T>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
        }

        // scalar multiply
        // vec * scalar
        template<typename S> requires std::is_arithmetic_v<S>
        friend Vec3<T> operator*(const Vec3<T>& vec, S scalar) {
            return {vec.x * scalar, vec.y * scalar, vec.z * scalar};
        }
        // scalar * vec
        template<typename S> requires std::is_arithmetic_v<S>
        friend Vec3<T> operator*(S scalar, const Vec3<T>& vec) {
            return {vec.x * scalar, vec.y * scalar, vec.z * scalar};
        }

        // divide by scalar
        // vec / scalar
        template<typename S> requires std::is_arithmetic_v<S>
        friend Vec3<T> operator/(const Vec3<T>& vec, S scalar) {
            return {vec.x / scalar, vec.y / scalar, vec.z / scalar};
        }

        // compound assignment
        Vec3<T>& operator+=(const Vec3<T>& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
        Vec3<T>& operator-=(const Vec3<T>& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
        Vec3<T>& operator*=(const Vec3<T>& rhs) { x *= rhs.x; y *= rhs.y; z *= rhs.z; return *this; }
        template<typename S> requires std::is_arithmetic_v<S>
        Vec3<T>& operator*=(S s) { x *= s; y *= s; z *= s; return *this; }
        template<typename S> requires std::is_arithmetic_v<S>
        Vec3<T>& operator/=(S s) { x /= s; y /= s; z /= s; return *this; }

};

