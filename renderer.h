#ifndef RENDERER_H
#define RENDERER_H

#include "cam.h"
#include "scene.h"
#include "ray.h"

class Renderer {
private:
    int image_width_;
    int image_height_;
    Camera camera_;
    int ray_count_;

public:

    Renderer(int image_width, int image_height, Camera& camera, int ray_count);

    Color trace_ray(Ray ray, const Scene& scene, int bounces) const;

    void render(std::ostream& out, const Scene& scene) const;

};

#endif