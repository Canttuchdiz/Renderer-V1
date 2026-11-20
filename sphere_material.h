#ifndef SPHERE_MAT_H
#define SPHERE_MAT_H

#include <any>
#include "material.h"

class SphereMaterial : public Material {
public:
    explicit SphereMaterial(const Vector3& reflectance) : Material(reflectance) {}

    Color texture(const std::any& position_package) const override { return reflectance_; }
};

#endif