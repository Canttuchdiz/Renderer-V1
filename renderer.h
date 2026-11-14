#ifndef RENDERER_H
#define RENDERER_H

#include "cam.h"
#include "scene.h"

class Renderer {
private:
    int image_width_;
    int image_height_;
    Camera camera_;

public:

    Renderer(int image_width, int image_height, Camera& camera);

    void render(std::ostream& out, const Scene& scene) const;

};

#endif