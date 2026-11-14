#include <iostream>
#include <fstream>
#include "vec3.h"
#include "color.h"
#include "cam.h"
#include "sphere.h"
#include "renderer.h"

int main() {

    int image_width = 800;
    int image_height = 450;
    double fov = 90;

    std::ofstream output("image.ppm");

    Camera camera = Camera(image_width, double(image_width)/image_height, fov, Vector3::zero());

    Scene scene = Scene();

    Sphere sphere(Vector3(-15, 5, 40), 5);
    Sphere sphere2(Vector3(15, -5, 40), 10);

    scene.add_sphere(sphere);
    scene.add_sphere(sphere2);

    Renderer renderer = Renderer(image_width, image_height, camera);

    renderer.render(output, scene);
}