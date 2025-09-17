#include <algorithm>
#include <fstream>

#include <objects/camera.hpp>
#include <objects/color.hpp>
#include <objects/hittable.hpp>

#include <materials/base.hpp>

#include <constants.hpp>
#include <randomizer.hpp>

// camera method definitions
void camera::render(const hittable& world) {
  initialize();

  std::ofstream file_out;
  file_out.open(file_path);

  file_out << "P3\n";
  file_out << image_width << " " << image_height << "\n" << 255 << "\n";
  for(int i=0; i<image_height; ++i) {
    for(int j=0; j<image_width; ++j) {
      color pixel_color(0, 0, 0);
      for(int sample=0; sample<samples_per_pixel; ++sample) {
        ray r = get_ray(i, j);
        pixel_color += get_ray_color(r, max_depth, world);
      }

      pixel_color = get_color_byte(pixel_samples_scale * pixel_color);
      file_out << pixel_color.x() << " " << pixel_color.y() << " " << pixel_color.z() << "\n";
    }
  }
}

void camera::initialize() {
  image_height = std::max(1, static_cast<int> (image_width / aspect_ratio));
  pixel_samples_scale = 1.0 / samples_per_pixel;
  camera_position = point3(0, 0, 0);

  double focal_length = 1.0;
  double viewport_height = 2.0;
  double viewport_width = aspect_ratio * viewport_height;

  vec3 view_u = vec3(viewport_width, 0, 0);
  vec3 view_v = vec3(0, -viewport_height, 0);

  pixel_delta_u = view_u / image_width;
  pixel_delta_v = view_v / image_height;

  vec3 view_upper_left_corner = camera_position - vec3(0, 0, focal_length) - view_u / 2 - view_v / 2;
  upper_left_corner_pixel = view_upper_left_corner + 0.5 * (pixel_delta_u + pixel_delta_v);
}

ray camera::get_ray(int i, int j) const {
  vec3 offset = sample_square();
  vec3 pixel_sample = upper_left_corner_pixel + ((offset.x() + j) * pixel_delta_u) + ((offset.y() + i) * pixel_delta_v);

  vec3 ray_origin = camera_position;
  vec3 ray_direction = pixel_sample - ray_origin;

  return ray(ray_origin, ray_direction);
}

vec3 camera::sample_square() const {
  return vec3(random_double() - 0.5, random_double() - 0.5, 0);
}

color camera::get_ray_color(const ray& r, int depth, const hittable& world) const {
  // TODO: Write the ray color function with recursion for ray bouncing

  return color(0, 0, 0);
}