#ifndef PLANE_H
#define PLANE_H

#include "ray.h"
#include "object.h"
#include <optional>

class Plane : public Object {
private:
    double level_;
    Color color_;

public:

    Plane(double level, Color color) : level_{level}, color_{color} {}

    double level() const { return level_; }

    std::optional<Hit> intersect(const Ray& ray) const override {

        Point3 position = ray.origin();
        Vector3 direction = ray.direction();

        if (std::abs(direction.y()) <= epsilon) return std::nullopt;

        double t = (level_ - position.y())/direction.y();

        if (t > 0) {
            Point3 hit_position = position + (direction * t);
            Vector3 hit_normal = Vector3(0, 1, 0);
            return Hit {hit_position, hit_normal, t};
        }
        return std::nullopt;
    }

    Color color() const override { return color_; }
};

#endif