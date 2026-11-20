#ifndef PLANE_H
#define PLANE_H

#include <optional>
#include <memory>
#include "ray.h"
#include "object.h"

class Plane : public Object {
private:
    double level_;
    Color color_;

public:

    Plane(double level, std::shared_ptr<const Material> material) : level_{level}, Object(std::move(material)) {}

    double level() const { return level_; }

    std::optional<Hit> intersect(const Ray& ray) const override {

        Point3 position = ray.origin();
        Vector3 direction = ray.direction();

        if (std::abs(direction.y()) <= epsilon) return std::nullopt;

        double t = (level_ - position.y())/direction.y();

        if (t > 0) {
            Point3 hit_position = position + (direction * t);
            Vector3 hit_normal = Vector3(0, 1, 0);
            return Hit {hit_position, hit_normal, t, material_.get()};
        }
        return std::nullopt;
    }

    Color color(const std::any& position_package) const override {
        int square_length = 20;
        const Point3& position = std::any_cast<const Point3>(position_package);

        double x = position.x();
        double z = position.z();

        int a = std::abs(int(x/square_length));
        int b = std::abs(int(z/square_length));

        if (x < 0) a++;
        if (z < 0) b++;
        if (a % 2 == b % 2) return color_ * 0.5;

        return color_;
    }
};

#endif