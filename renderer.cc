#include <iostream>
#include <chrono>
#include "renderer.h"
#include "color.h"
#include "sphere.h"
#include "mirror_material.h"

Renderer::Renderer(int image_width, int image_height, Camera &camera, const LightSource &source, int ray_count) : image_width_{image_width}, image_height_{image_height}, camera_{camera}, source_{source}, ray_count_{ray_count} {}

std::optional<Hit> Renderer::ray_intersect(Ray ray, const Scene &scene) const
{
    std::optional<Hit> last_hit;

    for (const auto &object : scene.objects())
    {
        std::optional<Hit> hit = object->intersect(ray);

        if (hit && (!last_hit || hit->t < last_hit->t))
        {
            last_hit = std::move(hit);
        }
    }
    return last_hit;
}

Vector3 Renderer::trace_ray(Ray ray, const Scene &scene, int bounces) const
{
    if (bounces <= 0)
        return Color(0, 0, 0);

    Radiance radiance = Vector3::zero();
    std::optional<Hit> last_hit = ray_intersect(ray, scene);

    if (last_hit)
    {

        Matrix3 local_to_world_matrix = Vector3::local_to_world_matrix(source_.direction().normalize());
        Vector3 local_random_vector = Vector3::random_angular_direction(source_.angular_radius());
        Vector3 random_angular_direction = (local_to_world_matrix * local_random_vector).normalize();

        ReflectionSample reflection_sample = last_hit->material->sample_reflection(*last_hit, ray);

        Color hit_reflectance = last_hit->material->texture(last_hit->position);

        const bool is_mirror = dynamic_cast<const MirrorMaterial *>(last_hit->material) != nullptr;

        if (!is_mirror)
        {
            Ray sun_ray = Ray(last_hit->position + (last_hit->normal * 0.0001), random_angular_direction);
            if (!(ray_intersect(sun_ray, scene)))
            {
                radiance += 2 * hit_reflectance * source_.radiance() * (1 - std::cos(source_.angular_radius())) * std::max(0.0, last_hit->normal.normalize().dot(sun_ray.direction()));
            }
        }
        else
        {
            Vector3 bounce_direction = reflection_sample.direction;
            if (bounce_direction.dot(source_.direction()) >= std::cos(source_.angular_radius()) && !ray_intersect(Ray(last_hit->position + (last_hit->normal * 0.0001), bounce_direction), scene))
                radiance += reflection_sample.weight * source_.radiance();
        }

        // Indirect lighting
        radiance += reflection_sample.weight * trace_ray(Ray(last_hit->position + (last_hit->normal * 0.0001), reflection_sample.direction), scene, bounces - 1);
    }
    else if (ray.direction().dot(Vector3::up()) > 0) {
        double distance_scalar = ray.direction().dot(Vector3::up());
        Color far_blue = Color(260.0, 440.0, 570.0);
        Color close_blue = Vector3(10.0, 100.0, 570.0);
        Color interpolator = close_blue - far_blue;

        radiance += far_blue + interpolator * distance_scalar;
    }

    return radiance;
}

// Rewrite to use image buffer
void Renderer::render(std::ostream &out, const Scene &scene) const
{

    const auto start_time = std::chrono::steady_clock::now();

    out << "P3\n"
        << image_width_ << ' ' << image_height_ << "\n255\n";

    int last_percent = 0;
    const auto total_pixels = 1LL * image_width_ * image_height_;

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

                Color pixel_color = trace_ray(ray, scene, MAX_BOUNCES);
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

            const auto pixels_done = 1LL * j * image_width_ + i + 1;
            const int percent = static_cast<int>(100.0 * pixels_done / total_pixels);

            if (percent > last_percent)
            {
                last_percent = percent;

                const double elapsed = std::chrono::duration<double>(
                                           std::chrono::steady_clock::now() - start_time)
                                           .count();

                const auto elapsed_seconds = static_cast<long long>(elapsed);
                const auto remaining_seconds = static_cast<long long>(
                    (elapsed / pixels_done) * (total_pixels - pixels_done));

                std::clog << "\rRendering: " << percent << "%"
                          << " | Elapsed: " << elapsed_seconds / 60 << ':'
                          << (elapsed_seconds % 60 < 10 ? "0" : "") << elapsed_seconds % 60
                          << " | Remaining: " << remaining_seconds / 60 << ':'
                          << (remaining_seconds % 60 < 10 ? "0" : "") << remaining_seconds % 60
                          << "    " << std::flush;
            }
        }
    }

    std::clog << "\n";
}