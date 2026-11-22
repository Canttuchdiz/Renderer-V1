#ifndef OBJECT_H
#define OBJECT_H

#include <any>
#include <memory>
#include <optional>
#include "ray.h"
#include "material.h"

class Object {
protected:
    std::shared_ptr<const Material> material_;

public:
    explicit Object(std::shared_ptr<const Material> material) : material_{std::move(material)} {}

    virtual std::optional<Hit> intersect(const Ray& ray) const = 0;
    virtual ~Object() = default;
    const Material& material() const { return *material_; }
};

#endif