cmake_minimum_required(VERSION 3.16)

project(RayTracer LANGUAGES CXX)

add_executable(raytracer main.cc cam.cc sphere.cc renderer.cc)

set_target_properties(raytracer PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_compile_options(raytracer PRIVATE -Wall -Wextra)