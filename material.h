#ifndef MATERIAL_H
#define MATERIAL_H

#include <any>
#include "vec3.h"

class Material {
protected:
    Vector3 reflectance_;

public:
    explicit Material(const Vector3& reflectance): reflectance_{reflectance} {}

    virtual ~Material() = default;

    const Vector3& reflectance() const { return reflectance_; }

    virtual Color texture(const std::any& data) const = 0;

};

#endif