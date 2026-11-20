#include <algorithm>
#include "sphere.h"

Sphere::Sphere(Point3 center, double radius, std::shared_ptr<const Material> material) : center_{center}, radius_{radius}, Object(std::move(material)) {}

Point3 Sphere::center() const { return center_; }
double Sphere::radius() const { return radius_; }

double Sphere::min_root(double a, double b, double c) const {
    double det = (b * b) - (4 * a * c);

    if (det < 0) return -1;

    double det_root = std::sqrt(det);
    double r1 = (-b + det_root)/(2 * a);
    double r2 = (-b - det_root)/(2 * a);

    double min = std::min(r1, r2);
    double max = std::max(r1, r2);
    if (min < 0 && max < 0) return -1;
    if (min < 0) return max;
    return min;
}

std::optional<Hit> Sphere::intersect(const Ray& ray) const {
    Point3 origin = ray.origin();
    Vector3 direction = ray.direction();

    double a = 1;
    double b = 2 * direction.dot(origin - center_);
    double c = origin.length_squared() + center_.length_squared() - (radius_ * radius_) - (2 * (origin.dot(center_)));

    double t = min_root(a, b, c);

    if (t >= 0) {
        Point3 hit_position = origin + (direction * t);
        Vector3 hit_normal = (hit_position - center_).normalize();
        return Hit {hit_position, hit_normal, t, material_.get()};
    }
    return std::nullopt;
}

