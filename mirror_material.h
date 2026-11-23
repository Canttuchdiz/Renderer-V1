#ifndef MIRROR_MAT_H
#define MIRROR_MAT_H

#include <any>

#include "material.h"
#include "ray.h"

class MirrorMaterial : public Material {
public:

    explicit MirrorMaterial(const Vector3& reflectance) : Material(reflectance) {}

    Color texture(const std::any& position_package) const override { return reflectance_; }

    ReflectionSample sample_reflection(const Hit& hit, const Ray& incoming) const override {
        Vector3 incoming_direction = incoming.direction().normalize();
        Vector3 hit_normal = hit.normal.normalize();

        Vector3 perpendicular_vector = -hit_normal * incoming_direction.dot(hit_normal);
        Vector3 parallel_vector = incoming_direction + perpendicular_vector;
        Vector3 resultant_vector = (perpendicular_vector + parallel_vector).normalize();

        return ReflectionSample {resultant_vector, reflectance_};
    }
};

#endif