#include <iostream>
#include <memory>

#include <objects/camera.hpp>
#include <objects/color.hpp>
#include <objects/hittable.hpp>

#include <shapes/sphere.hpp>

#include <materials/lambertian.hpp>
#include <materials/metal.hpp>

int main() {
    hittable_list world;

    auto material_ground = std::make_shared<lambertian>(color(0.11, 0.14, 0.22));
    auto material_center = std::make_shared<lambertian>(color(0.9, 0.1, 0.1));
    auto material_side = std::make_shared<metal>(color(1.0, 1.0, 1.0), 0.0);

    world.add(std::make_shared<sphere>(point3(0, 0, -1), 0.5, material_center));
    world.add(std::make_shared<sphere>(point3(1, 0, -1), 0.5, material_side));
    world.add(std::make_shared<sphere>(point3(-1, 0, -1), 0.5, material_side));
    world.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100, material_ground));

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
