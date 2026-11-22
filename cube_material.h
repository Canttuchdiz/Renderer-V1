#ifndef CUBE_MAT_H
#define CUBE_MAT_H

#include <any>
#include "material.h"

class CubeMaterial : public Material {
public:
    explicit CubeMaterial(const Vector3& reflectance) : Material(reflectance) {}

    Color texture(const std::any& position_package) const override { return reflectance_; }
};

#endif