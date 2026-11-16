#include <iostream>
#include "renderer.h"
#include "color.h"
#include "sphere.h"

Renderer::Renderer(int image_width, int image_height, Camera &camera, int ray_count) : image_width_{image_width}, image_height_{image_height}, camera_{camera}, ray_count_{ray_count} {}

Color Renderer::trace_ray(Ray ray, const Scene &scene, int bounces) const
{
    std::optional<Hit> last_hit;

    if (bounces <= 0) return Color(0, 0, 0);

    Color hit_color;

    for (const auto& object : scene.objects())
    {
        std::optional<Hit> hit = object->intersect(ray);

        if (hit && (!last_hit || hit->t < last_hit->t)) {
            last_hit = hit;
            hit_color = object->color();
        }
    }

    if (last_hit) {
        Vector3 ray_position = ray.origin() + (ray.direction() * last_hit->t);
        Vector3 random_direction = Vector3::random_hemisphere_direction();
        Vector3 world_random_direction = Vector3::local_to_world_matrix(last_hit->normal) * random_direction;

        return hit_color * trace_ray(Ray(ray_position + (world_random_direction * 0.0001), world_random_direction), scene, bounces - 1) * 0.8;
    }

    return Color(1.0, 1.0, 1.0);
}

void Renderer::render(std::ostream &out, const Scene &scene) const
{

    out << "P3\n"
        << image_width_ << ' ' << image_height_ << "\n255\n";

    int last_percent = 0;

    for (int j = 0; j < image_height_; j++)
    {
        for (int i = 0; i < image_width_; i++)
        {
            std::vector<Color> hit_colors;
            for (int k = 0; k < ray_count_; k++)
            {

                Point3 pixel_position = camera_.pixel_random(i, j);
                Vector3 ray_direction = (pixel_position - camera_.position()).normalize();

                Ray ray = Ray(camera_.position(), ray_direction);
                
                Color pixel_color = trace_ray(ray, scene, 5);
                hit_colors.push_back(pixel_color);
            }

            Color pixel_sum = Vector3::zero();
            for (const Color &pixel_color : hit_colors)
                pixel_sum += pixel_color;

            Color pixel_average = pixel_sum / hit_colors.size() * 0.7;
            Color pixel_root_average = Color(std::sqrt(pixel_average.x()), std::sqrt(pixel_average.y()), std::sqrt(pixel_average.z()));
            write_color(out, pixel_root_average);

            int percent = int((double(i + 1 + (j * image_width_))/(image_width_ * image_height_)) * 100);

            if (percent > last_percent) {
                last_percent = percent;
                std::clog << "\rRendering: " << percent << "%" << std::flush;
            }
        }
    }

    std::clog << "\n";
}