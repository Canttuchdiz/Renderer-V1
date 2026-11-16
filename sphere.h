#ifndef SPHERE_H
#define SPHERE_H

#include <optional>
#include "vec3.h"
#include "ray.h"
#include "object.h"

class Sphere : public Object {
private:
    Point3 center_;
    double radius_;
    Color color_;

    double min_root(double a, double b, double c) const;

public:

    Sphere();
    Sphere(Point3 center, double radius, Color color);

    Point3 center() const;
    double radius() const;
    
    std::optional<Hit> intersect(const Ray& ray) const override;

    Color color() const override { return color_; }

};

#endif