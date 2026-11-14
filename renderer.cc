#include <iostream>
#include "renderer.h"
#include "color.h"
#include "sphere.h"

Renderer::Renderer(int image_width, int image_height, double fov, Camera &camera) : image_width_{image_width},
                                                                                    image_height_{image_height},
                                                                                    fov_{fov},
                                                                                    camera_{camera} {}

void Renderer::render(std::ostream& out, const Scene& scene) const {

    out << "P3\n" << image_width_ << ' ' << image_height_ << "\n255\n";

    for (int j = 0; j < image_height_; j++) {
        for (int i = 0; i < image_width_; i++) {

            double r = 0, g = 0, b = 0;
            
            Point3 pixel_position = camera_.pixel_position(i, j);
            Vector3 ray_direction = (pixel_position - camera_.position()).normalized();
            double last_depth = -1;

            for (const Sphere& sphere : scene.spheres()) {
                std::optional<Hit> hit = sphere.hits_sphere(camera_.position(), ray_direction);

                if (hit && (hit->t < last_depth || last_depth == -1)) {

                    // Pixel color calculation
                    r = (hit->normal.x() + 1)/2;
                    g = (hit->normal.y() + 1)/2;
                    b = (hit->normal.z() + 1)/2;

                    last_depth = hit->t;
                }
            }

            Color pixel_color = Color(r, g, b);

            write_color(out, pixel_color);
        }
    }

}