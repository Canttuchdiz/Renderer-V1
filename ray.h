#ifndef RAY_H
#define RAY_H

#include "vec3.h"
#include "material.h"

struct Hit {
    Point3 position;
    Vector3 normal;
    double t;
    const Material* material;
};

class Ray {
private:
    Point3 origin_;
    Vector3 direction_;

public:
    Ray() : origin_{Vector3::zero()}, direction_{Vector3::zero()} {}
    Ray(const Point3& origin, const Vector3& direction) : origin_{origin}, direction_{direction} {}

    const Point3& origin() const { return origin_; }
    const Vector3& direction() const { return direction_; }

    Point3 at(double t) const { return origin_ + (t * direction_); }
};

#endif