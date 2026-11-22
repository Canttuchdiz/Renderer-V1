#include <iostream>
#include "renderer.h"
#include "color.h"
#include "sphere.h"

Renderer::Renderer(int image_width, int image_height, Camera &camera, const LightSource& source, int ray_count) : image_width_{image_width}, image_height_{image_height}, camera_{camera}, source_{source}, ray_count_{ray_count} {}

std::optional<Hit> Renderer::ray_intersect(Ray ray, const Scene& scene) const {
    std::optional<Hit> last_hit;

    for (const auto& object : scene.objects())
    {
        std::optional<Hit> hit = object->intersect(ray);

        if (hit && (!last_hit || hit->t < last_hit->t)) {
            last_hit = std::move(hit);
        }
    }
    return last_hit;
}

Vector3 Renderer::trace_ray(Ray ray, const Scene& scene, int bounces) const
{
    if (bounces <= 0) return Color(0, 0, 0);

    Radiance radiance = Vector3::zero();
    std::optional<Hit> last_hit = ray_intersect(ray, scene);

    if (last_hit) {
        Vector3 ray_position = ray.origin() + (ray.direction() * last_hit->t);

        Vector3 random_direction = Vector3::random_hemisphere_direction();
        Vector3 world_random_direction = (Vector3::local_to_world_matrix(last_hit->normal) * random_direction).normalize();

        Matrix3 local_to_world_matrix = Vector3::local_to_world_matrix(source_.direction().normalize());
        Vector3 local_random_vector = Vector3::random_angular_direction(source_.angular_radius());
        Vector3 random_angular_direction = (local_to_world_matrix * local_random_vector).normalize();

        Color hit_reflectance = last_hit->material->texture(last_hit->position);

        Ray sun_ray = Ray(last_hit->position + (last_hit->normal * 0.0001), random_angular_direction);
        if(!(ray_intersect(sun_ray, scene))) {
            // Direct lighting
            radiance += 2 * hit_reflectance * source_.radiance() * (1 - std::cos(source_.angular_radius())) * std::max(0.0, last_hit->normal.normalize().dot(sun_ray.direction()));
            
        
        }

        // Indirect lighting
        radiance += 2 * hit_reflectance * trace_ray(Ray(ray_position + (last_hit->normal * 0.0001), world_random_direction), scene, bounces - 1) * std::max(0.0, world_random_direction.dot(last_hit->normal));

        return radiance;
    }

    return Vector3::zero();
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

            Color pixel_average = pixel_sum / hit_colors.size();
            Color exposed = pixel_average * .0028;
            Color mapped_pixel_average = Vector3(exposed.x() / (exposed.x() + 1), exposed.y() / (exposed.y() + 1), exposed.z() / (exposed.z() + 1));
            Color pixel_root_average = Color(std::sqrt(mapped_pixel_average.x()), std::sqrt(mapped_pixel_average.y()), std::sqrt(mapped_pixel_average.z()));
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