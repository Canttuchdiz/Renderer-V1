#ifndef OBJECT_H
#define OBJECT_H

#include <optional>
#include "ray.h"

class Object {
public:
    virtual std::optional<Hit> intersect(const Ray& ray) const = 0;
    virtual ~Object() = default;
    virtual Color color() const = 0;
};

#endif