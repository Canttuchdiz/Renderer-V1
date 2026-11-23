#ifndef LIGHT_SOURCE_H
#define LIGHT_SOURCE_H

#include "vec3.h"

class LightSource
{

private:
    Vector3 direction_;
    double angular_radius_;
    Irradiance irradiance_;

public:
    LightSource(const Vector3 &direction, double angular_radius, const Irradiance &irradiance) : direction_{direction},
                                                                                             angular_radius_{angular_radius},
                                                                                             irradiance_{irradiance} {}

    Vector3 direction() const;
    double angular_radius() const;
    Radiance radiance() const;
};

#endif