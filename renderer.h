#ifndef RENDERER_H
#define RENDERER_H

#include "cam.h"
#include "scene.h"
#include "ray.h"
#include "lightSource.h"

class Renderer {
private:
    int image_width_;
    int image_height_;
    Camera camera_;
    LightSource source_;
    int ray_count_;

    static constexpr int MAX_BOUNCES = 10;

public:

    Renderer(int image_width, int image_height, Camera& camera, const LightSource& source, int ray_count);

    std::optional<Hit> ray_intersect(Ray ray, const Scene& scene) const;

    Vector3 trace_ray(Ray ray, const Scene& scene, int bounces) const;

    void render(std::ostream& out, const Scene& scene) const;

};

#endif