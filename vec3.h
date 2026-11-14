#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <ostream>

class Vector3
{
private:
    double x_, y_, z_;

public:
    Vector3() : x_{0}, y_{0}, z_{0} {}

    Vector3(double x, double y, double z) : x_{x}, y_{y}, z_{z} {}

    double x() const { return x_; }
    double y() const { return y_; }
    double z() const { return z_; }

    Vector3 operator-() const {
        return Vector3(-x_, -y_, -z_);
    }

    Vector3 operator+(const Vector3& other) const {
        return Vector3(x_ + other.x_, y_ + other.y_, z_ + other.z_);
    }

    Vector3 operator-(const Vector3& other) const {
        return *this + (-other);
    }

    Vector3& operator+=(const Vector3& other) {
        x_ += other.x_;
        y_ += other.y_;
        z_ += other.z_;
        return *this;
    }

    Vector3& operator-=(const Vector3& other) {
        x_ -= other.x_;
        y_ -= other.y_;
        z_ -= other.z_;
        return *this;
    }

    Vector3 operator*(const Vector3& other) const {
        return Vector3(x_ * other.x_, y_ * other.y_, z_ * other.z_);
    }

    Vector3 operator/(const Vector3& other) const {
        return Vector3(x_ / other.x_, y_ / other.y_, z_ / other.z_);
    }

     Vector3 operator*(double other) const {
        return Vector3(x_ * other, y_ * other, z_ * other);
    }

    Vector3 operator/(double other) const {
        return Vector3(x_ / other, y_ / other, z_ / other);
    }

    Vector3& operator*=(const Vector3& other) {
        x_ *= other.x_;
        y_ *= other.y_;
        z_ *= other.z_;
        return *this;
    }

    Vector3& operator/=(const Vector3& other) {
        x_ /= other.x_;
        y_ /= other.y_;
        z_ /= other.z_;
        return *this;
    }

    Vector3& operator*=(double other) {
        x_ *= other;
        y_ *= other;
        z_ *= other;
        return *this;
    }

    Vector3& operator/=(double other) {
        x_ /= other;
        y_ /= other;
        z_ /= other;
        return *this;
    }

    double dot(const Vector3& other) const {
        return x_ * other.x_ + y_ * other.y_ + z_ * other.z_;
    }

    Vector3 cross(const Vector3& other) const {
        return Vector3(
            (y_ * other.z_) - (z_ * other.y_),
            (z_ * other.x_) - (x_ * other.z_),
            (x_ * other.y_) - (y_ * other.x_)
        );
    }

    double length_squared() const {
        return (x_*x_ + y_*y_ + z_*z_);
    }

    double length() const { return std::sqrt(length_squared()); }

    Vector3 normalized() const {
        double vector_length = length();
        if (vector_length > 0) { return *this / vector_length; }
        return *this;
    }

    static Vector3 zero() { return Vector3(0, 0, 0); }
};

using Point3 = Vector3;
using Color = Vector3;

inline Vector3 operator*(double scalar, const Vector3& v) {
    return v * scalar;
}

inline std::ostream& operator<<(std::ostream& out, const Vector3& v) {
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

#endif