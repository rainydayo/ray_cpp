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
  image_height = std::max(1, static_cast<int>(image_width / aspect_ratio));
  pixel_samples_scale = 1.0 / samples_per_pixel;

  // TODO: Initialize the camera parameters
  double theta = 0.0;
  double h = 0.0;
  double viewport_height = 0.0;
  double viewport_width = 0.0;

  vec3 w = unit_vector(look_from - look_at);
  vec3 u = unit_vector(cross(v_up, w));
  vec3 v = cross(w, u);

  camera_position = look_from;
  vec3 horizontal = viewport_width * u;
  vec3 vertical = viewport_height * v;
  upper_left_corner_pixel = camera_position - w - horizontal / 2 + vertical / 2;
  pixel_delta_u = horizontal / image_width;
  pixel_delta_v = -vertical / image_height;
  upper_left_corner_pixel += 0.5 * (pixel_delta_u + pixel_delta_v);
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