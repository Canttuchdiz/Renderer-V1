#ifndef MATERIAL_H
#define MATERIAL_H

#include <any>
#include "vec3.h"

struct Hit;
class Ray;

struct ReflectionSample {
    Vector3 direction;
    Vector3 weight;
};

class Material {
protected:
    Vector3 reflectance_;

public:
    explicit Material(const Vector3& reflectance): reflectance_{reflectance} {}

    virtual ~Material() = default;

    const Vector3& reflectance() const { return reflectance_; }

    virtual Color texture(const std::any& data) const = 0;

    virtual ReflectionSample sample_reflection(const Hit& hit, const Ray& incoming) const = 0;

};

#endif