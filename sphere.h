#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include <optional>

struct Hit {
    Point3 position;
    Vector3 normal;
    double t;
};

class Sphere {
private:
    Point3 center_;
    double radius_;

    double min_root(double a, double b, double c) const;

public:

    Sphere();
    Sphere(Point3 center, double radius);

    Point3 center() const;
    double radius() const;
    
    std::optional<Hit> hits_sphere(const Point3& origin, const Vector3& direction) const;

};

#endif