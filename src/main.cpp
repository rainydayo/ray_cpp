#include <iostream>
#include <memory>

#include <objects/camera.hpp>
#include <objects/color.hpp>
#include <objects/hittable.hpp>

#include <shapes/sphere.hpp>

#include <materials/lambertian.hpp>
#include <materials/metal.hpp>
#include "materials/dielectric.cpp"
#include "shapes/plane.cpp"

int main() {
    hittable_list world;

    auto material_ground = std::make_shared<lambertian>(color(0.11, 0.14, 0.22));
    auto material_center = std::make_shared<lambertian>(color(0.9, 0.1, 0.1));
    auto material_side = std::make_shared<metal>(color(1.0, 1.0, 1.0), 0.0);

    // Materials
    auto mat_brown = std::make_shared<lambertian>(color(0.65, 0.33, 0.22)); // brown diffuse
    auto mat_white = std::make_shared<lambertian>(color(0.9, 0.9, 0.9));    // white diffuse
    auto mat_metal = std::make_shared<metal>(color(0.8, 0.8, 0.8), 0.1);    // slightly fuzzy metal
    auto mat_ground = std::make_shared<lambertian>(color(0.11, 0.14, 0.22));
    auto glass = std::make_shared<dielectric>(2.4);

    // Head
    world.add(std::make_shared<sphere>(point3(0, 0, -1), 0.6, glass));

    // Body
    world.add(std::make_shared<sphere>(point3(0, -0.9, -1), 0.9, mat_brown));

    // Ears
    world.add(std::make_shared<sphere>(point3(-0.6, 0.6, -1), 0.25, mat_metal));
    world.add(std::make_shared<sphere>(point3(0.6, 0.6, -1), 0.25, mat_metal));

    // Arms
    world.add(std::make_shared<sphere>(point3(-1.0, -0.2, -1), 0.35, mat_white));
    world.add(std::make_shared<sphere>(point3(1.0, -0.2, -1), 0.35, mat_white));

    // Ground
    //world.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100, glass));
    world.add(std::make_shared<plane>(-0.5, mat_ground));

    camera cam("./images/out.ppm");

    // Camera setup
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 800;        // smaller test render
    cam.samples_per_pixel = 50;   // anti-aliasing
    cam.max_depth = 5;

    cam.look_from = point3(0, 0, 1);
    cam.look_at = point3(0, 0, -1);
    cam.v_up = vec3(0, 1, 0);

    cam.render(world);

    std::cout << "\nImage rendered to ./images/out.ppm" << std::endl;
    return 0;
}
