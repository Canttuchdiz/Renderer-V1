#ifndef MATTE_MAT_H
#define MATTE_MAT_H

#include <any>
#include "material.h"

class MatteMaterial : public Material {
public:
    explicit MatteMaterial(const Vector3& reflectance) : Material(reflectance) {}

    Color texture(const std::any& position_package) const override { return reflectance_; }

    ReflectionSample sample_reflection(const Hit& hit, const Ray& incoming) const override {
        Color hit_reflectance = texture(hit.position);

        Vector3 random_direction = Vector3::random_hemisphere_direction();
        Vector3 outgoing_direction = (Vector3::local_to_world_matrix(hit.normal) * random_direction).normalize();

        Vector3 weight = 2 * hit_reflectance * std::max(0.0, outgoing_direction.dot(hit.normal));

        return ReflectionSample {outgoing_direction, weight};

    }
};

#endif