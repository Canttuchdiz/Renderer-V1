#ifndef SQUARE_H
#define SQUARE_H

#include <vector>
#include <optional>
#include "object.h"

struct Edge {
    Point3 position;
    Vector3 normal;
    Vector3 up;
};

std::ostream& operator<<(std::ostream& os, const Edge& hit) {
    os << "Position: " << hit.position
       << ", Normal: " << hit.normal;

    return os;
}

class Cube : public Object {
private:
    Point3 center_;
    double length_;
    std::vector<Edge> edges_;

public:

    Cube(Point3 center, double length, std::shared_ptr<const Material> material) : center_{center}, length_{length}, Object(std::move(material)) {
        for (int i = 0; i < 2; i++) {
            int j = i == 0 ? 1 : -1;
            edges_.push_back(Edge {center_ + (Vector3::forward() * (length_/2.0) * j), Vector3::forward() * j, Vector3::up()});
            edges_.push_back(Edge {center_ + (Vector3::right() * (length_/2.0) * j), Vector3::right() * j, Vector3::up()});
            edges_.push_back(Edge {center_ + (Vector3::up() * (length_/2.0) * j), Vector3::up() * j, -Vector3::forward()});
        }
    }

    std::optional<Hit> intersect(const Ray& ray) const {
        std::optional<Edge> last_edge;
        Vector3 hit_vector;

        double last_t = -1;
        Vector3 ray_origin = ray.origin();
        Vector3 ray_direction = ray.direction();

        for (const auto& edge : edges_) {
            double t = edge.normal.dot(edge.position - ray_origin)/edge.normal.dot(ray_direction);
            double half_length = length_/2.0;

            Vector3 intersect_vector = ray_origin + (ray_direction * t);
            Vector3 plane_vector = intersect_vector - edge.position;
            Vector3 right_vector = edge.up.cross(edge.normal).normalize();

            Vector3 horizontal_vector = right_vector * (right_vector.dot(plane_vector));
            Vector3 vertical_vector = plane_vector - horizontal_vector;
            if (t >= 0 && horizontal_vector.length() <= half_length && vertical_vector.length() <= half_length && (last_t < 0 || t < last_t)) {
                last_edge = edge;
                last_t = t;
                hit_vector = intersect_vector;
            };
        }

        if (last_edge) return Hit {hit_vector, last_edge->normal.normalize(), last_t, material_.get()};
        
        return std::nullopt;

    }
};

#endif