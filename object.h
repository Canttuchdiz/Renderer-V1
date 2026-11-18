#ifndef OBJECT_H
#define OBJECT_H

#include <any>
#include <optional>
#include "ray.h"
#include "material.h"

class Object {
    Material material_;

public:
    explicit Object(const Material& material) : material_{material} {}

    virtual std::optional<Hit> intersect(const Ray& ray) const = 0;
    virtual ~Object() = default;
    virtual Color color(const std::any& data) const = 0;
    const Material& material() const { return material_; }
};

#endif