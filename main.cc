#include <iostream>
#include <fstream>
#include "vec3.h"
#include "color.h"
#include "cam.h"
#include "sphere.h"
#include "renderer.h"
#include "plane.h"
#include "lightSource.h"
#include "plane_material.h"
#include "sphere_material.h"

int main() {
    // 1280 720 | 850 478
    int image_width = 1280;
    int image_height = 720;
    double fov = 100;

    std::ofstream output("image.ppm");

    Camera camera = Camera(image_width, double(image_width)/image_height, fov, Vector3(0, 10, 0));

    Vector3 light_direction = Vector3(-.5, 1, 0);
    LightSource source = LightSource(light_direction, 15 * (pi/180), Irradiance(1361, 1361, 1361));

    Scene scene = Scene();

    Sphere sphere(Vector3(-20, 8, 55), 8, std::make_shared<SphereMaterial>(Color(0.3, 0.1, 0.7)));
    Sphere sphere2(Vector3(13, 13, 40), 13, std::make_shared<SphereMaterial>(Color(0.9, 0.1, 0.1)));

    scene.add_object(std::make_unique<Sphere>(sphere));
    scene.add_object(std::make_unique<Sphere>(sphere2));
    scene.add_object(std::make_unique<Plane>(0, std::make_shared<PlaneMaterial>(Color(0.3, 0.3, 0.3))));

    Renderer renderer = Renderer(image_width, image_height, camera, source, 2048); // 64 | 2048

    renderer.render(output, scene);
}