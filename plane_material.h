#ifndef PLANE_MAT_H
#define PLANE_MAT_H

#include <any>

#include "matte_material.h"

class PlaneMaterial : public MatteMaterial {
public:

    explicit PlaneMaterial(const Vector3& reflectance) : MatteMaterial(reflectance) {}

    Color texture(const std::any& position_package) const override {
        int square_length = 20;
        const Point3& position = std::any_cast<const Point3>(position_package);

        double x = position.x();
        double z = position.z();

        int a = std::abs(int(x/square_length));
        int b = std::abs(int(z/square_length));

        if (x < 0) a++;
        if (z < 0) b++;
        if (a % 2 == b % 2) return reflectance_ * 0.5;

        return reflectance_;
    }
};

#endif