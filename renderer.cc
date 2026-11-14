#include <iostream>
#include "renderer.h"
#include "color.h"
#include "sphere.h"

constexpr int ray_count = 64;

Renderer::Renderer(int image_width, int image_height, Camera &camera) : image_width_{image_width}, image_height_{image_height}, camera_{camera} {}

void Renderer::render(std::ostream &out, const Scene &scene) const
{

    out << "P3\n"
        << image_width_ << ' ' << image_height_ << "\n255\n";

    for (int j = 0; j < image_height_; j++)
    {
        for (int i = 0; i < image_width_; i++)
        {
            std::vector<Color> hit_colors;
            for (int k = 0; k < ray_count; k++)
            {

                double r = 0, g = 0, b = 0;

                Point3 pixel_position = camera_.pixel_random(i, j);
                Vector3 ray_direction = (pixel_position - camera_.position()).normalized();
                double last_depth = -1;

                for (const Sphere &sphere : scene.spheres())
                {
                    std::optional<Hit> hit = sphere.hits_sphere(camera_.position(), ray_direction);

                    if (hit && (hit->t < last_depth || last_depth == -1))
                    {

                        // Pixel color calculation
                        r = (hit->normal.x() + 1) / 2;
                        g = (hit->normal.y() + 1) / 2;
                        b = (hit->normal.z() + 1) / 2;

                        last_depth = hit->t;
                    }
                }

                Color pixel_color = Color(r, g, b);
                hit_colors.push_back(pixel_color);
            }
            Color pixel_sum = Vector3::zero();
            for (const Color& pixel_color : hit_colors) pixel_sum += pixel_color;

            Color pixel_average = pixel_sum/hit_colors.size();
            write_color(out, pixel_average);
        }
    }
}