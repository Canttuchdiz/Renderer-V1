#include "lightSource.h"
#include "constants.h"

Vector3 LightSource::direction() const { return direction_.normalize(); }
double LightSource::angular_radius() const { return angular_radius_; }

Radiance LightSource::radiance() const {
    return irradiance_ / (pi * (std::sin(angular_radius_)) * std::sin(angular_radius_));
}