#ifndef MATERIAL_H
#define MATERIAL_H

#include "vec3.h"

class Material {
private:
    Vector3 reflectance_;

public:
    Material(const Vector3& reflectance): reflectance_{reflectance} {}

    Vector3 brdf() const { return reflectance_ / pi; }
};

#endif