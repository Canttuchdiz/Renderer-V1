#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <random>
#include <stdexcept>
#include <cmath>
#include <ostream>
#include "constants.h"

inline std::random_device rd;
inline std::mt19937 gen(rd());
inline std::uniform_real_distribution<double> dis(0.0, 1.0);

class Vector3;

inline std::ostream &operator<<(std::ostream &out, const Vector3 &v);

struct Matrix3
{
    double matrix[3][3];

    Vector3 operator*(const Vector3 &v) const;

    Matrix3 transpose() const { return Matrix3{{
        {matrix[0][0], matrix[1][0], matrix[2][0]},
        {matrix[0][1], matrix[1][1], matrix[2][1]},
        {matrix[0][2], matrix[1][2], matrix[2][2]},
    }}; }
};

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

    Vector3 operator-() const
    {
        return Vector3(-x_, -y_, -z_);
    }

    Vector3 operator+(const Vector3 &other) const
    {
        return Vector3(x_ + other.x_, y_ + other.y_, z_ + other.z_);
    }

    Vector3 operator-(const Vector3 &other) const
    {
        return *this + (-other);
    }

    Vector3 &operator+=(const Vector3 &other)
    {
        x_ += other.x_;
        y_ += other.y_;
        z_ += other.z_;
        return *this;
    }

    Vector3 &operator-=(const Vector3 &other)
    {
        x_ -= other.x_;
        y_ -= other.y_;
        z_ -= other.z_;
        return *this;
    }

    Vector3 operator*(const Vector3 &other) const
    {
        return Vector3(x_ * other.x_, y_ * other.y_, z_ * other.z_);
    }

    Vector3 operator/(const Vector3 &other) const
    {
        return Vector3(x_ / other.x_, y_ / other.y_, z_ / other.z_);
    }

    Vector3 operator*(double other) const
    {
        return Vector3(x_ * other, y_ * other, z_ * other);
    }

    Vector3 operator/(double other) const
    {
        return Vector3(x_ / other, y_ / other, z_ / other);
    }

    Vector3 &operator*=(const Vector3 &other)
    {
        x_ *= other.x_;
        y_ *= other.y_;
        z_ *= other.z_;
        return *this;
    }

    Vector3 &operator/=(const Vector3 &other)
    {
        x_ /= other.x_;
        y_ /= other.y_;
        z_ /= other.z_;
        return *this;
    }

    Vector3 &operator*=(double other)
    {
        x_ *= other;
        y_ *= other;
        z_ *= other;
        return *this;
    }

    Vector3 &operator/=(double other)
    {
        x_ /= other;
        y_ /= other;
        z_ /= other;
        return *this;
    }

    double dot(const Vector3 &other) const
    {
        return x_ * other.x_ + y_ * other.y_ + z_ * other.z_;
    }

    Vector3 cross(const Vector3 &other) const
    {
        return Vector3(
            (y_ * other.z_) - (z_ * other.y_),
            (z_ * other.x_) - (x_ * other.z_),
            (x_ * other.y_) - (y_ * other.x_));
    }

    double length_squared() const
    {
        return (x_ * x_ + y_ * y_ + z_ * z_);
    }

    double length() const { return std::sqrt(length_squared()); }

    Vector3 normalize() const
    {
        double vector_length = length();
        if (vector_length > 0)
        {
            return *this / vector_length;
        }
        return *this;
    }

    bool is_normalized() const { return std::abs(length() - 1.0) <= epsilon; }

    static Vector3 zero() { return Vector3(0, 0, 0); }

    static Vector3 one() { return Vector3(1, 1, 1); }

    static Vector3 forward() { return Vector3(0, 0, 1); }

    static Vector3 up() { return Vector3(0, 1, 0); }

    static Vector3 right() { return Vector3(1, 0, 0); }

    static Matrix3 world_to_local_matrix(const Vector3 &normal)
    {

        if (!normal.is_normalized())
            throw std::invalid_argument("Normal must be normalized");

        double x = normal.x();
        double y = normal.y();
        double z = normal.z();
        double s = std::sqrt((x * x) + (z * z));

        if (x == 0.0 && z == 0.0)
            return Matrix3{{{y, 0, 0},
                            {0, y, 0},
                            {0, 0, 1}}};

        return Matrix3{{{(-x * y) / s, s, (-y * z) / s},
                        {x, y, z},
                        {z / s, 0, -x / s}}};
    }

    static Matrix3 local_to_world_matrix(const Vector3 &normal)
    {
        return world_to_local_matrix(normal).transpose();
    }

    static Matrix3 rotation_x_matrix(double theta) {
        return Matrix3{{
            {1, 0, 0},
            {0, std::cos(theta), std::sin(theta)},
            {0, -std::sin(theta), std::cos(theta)}
        }};
    }

    static Matrix3 rotation_y_matrix(double theta)
    {
        return Matrix3{{{std::cos(theta), 0, -std::sin(theta)},
                        {0, 1, 0},
                        {std::sin(theta), 0, std::cos(theta)}}};
    }

    static Matrix3 rotation_z_matrix(double theta) {
        return Matrix3{{
            {std::cos(theta), std::sin(theta), 0},
            {-std::sin(theta), std::cos(theta), 0},
            {0, 0, 1}
        }};
    }

    // From center direction
    static Vector3 random_angular_direction(double theta) {
        double y = 1 - (dis(gen) * (1 - std::cos(theta)));
        double z = std::sqrt(1 - (y * y));

        Vector3 initial_vector = Vector3(0, y, z);
        Matrix3 rotation_matrix = rotation_y_matrix(dis(gen) * 2 * pi);
        Vector3 rotated_vector = rotation_matrix * initial_vector;
        return rotated_vector;
    }

    static Vector3 random_hemisphere_direction()
    {
        double y = dis(gen);
        Vector3 initial_vector = Vector3(std::sqrt(1 - (y * y)), y, 0);
        Vector3 random_vector = rotation_y_matrix(2 * pi * dis(gen)) * initial_vector;
        return random_vector;
    }
};

inline Vector3 Matrix3::operator*(const Vector3 &v) const
{
    double x = v.x();
    double y = v.y();
    double z = v.z();

    double a = x * matrix[0][0] + y * matrix[0][1] + z * matrix[0][2];
    double b = x * matrix[1][0] + y * matrix[1][1] + z * matrix[1][2];
    double c = x * matrix[2][0] + y * matrix[2][1] + z * matrix[2][2];

    return Vector3(a, b, c);
}

using Point3 = Vector3;
using Color = Vector3;

using Irradiance = Vector3;
using Radiance = Vector3;


inline Vector3 operator*(double scalar, const Vector3 &v)
{
    return v * scalar;
}

inline std::ostream &operator<<(std::ostream &out, const Vector3 &v)
{
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

#endif