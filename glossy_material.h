#ifndef GLOSSY_MAT_H
#define GLOSSY_MAT_H

#include <any>

#include "material.h"
#include "ray.h"

class GlossyMaterial : public Material {
public:

    explicit GlossyMaterial(const Vector3& reflectance) : Material(reflectance) {}

    Color texture(const std::any& position_package) const override { return reflectance_; }

    ReflectionSample sample_reflection(const Hit& hit, const Ray& incoming) const override {
        const double alpha = pi / 6.0;

        Vector3 incoming_direction = incoming.direction().normalize();
        Vector3 hit_normal = hit.normal.normalize();

        Vector3 perpendicular_vector = -hit_normal * incoming_direction.dot(hit_normal);
        Vector3 parallel_vector = incoming_direction + perpendicular_vector;
        Vector3 resultant_vector = (perpendicular_vector + parallel_vector).normalize();

        Vector3 random_angular_direction = Vector3::random_angular_direction(alpha);
        Matrix3 local_to_world_matrix = Vector3::local_to_world_matrix(resultant_vector);

        Vector3 outgoing_direction = (local_to_world_matrix * random_angular_direction).normalize();

        Vector3 weight = 8 * reflectance_ * (1 - std::cos(alpha)) * std::max(0.0, outgoing_direction.dot(hit_normal));

        return ReflectionSample {outgoing_direction, weight};
    }
};

#endif