#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "sphere.h"

class Scene {
private:
    std::vector<Sphere> spheres_;

public:
    void add_sphere(const Sphere& sphere) {
        spheres_.push_back(sphere);
    }

    const std::vector<Sphere>& spheres() const { return spheres_; }
};

#endif