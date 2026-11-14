#include "renderer.h"
#include "color.h"

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

            for (const Sphere& sphere : scene.spheres()) {
                
                if (sphere.hits_sphere(camera_.position(), ray_direction)) b = 1;
            }

            Color pixel_color = Color(r, g, b);

            write_color(out, pixel_color);
        }
    }

}