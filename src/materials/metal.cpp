#include <materials/metal.hpp>

vec3 reflect(const vec3& v, const vec3& n) {
  // TODO: Write the reflect function that computes the reflection of vector v around normal n
  return vec3(0, 0, 0);
}

bool metal::scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
  vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
  reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
  scattered = ray(rec.p, reflected);
  attenuation = albedo;
  return dot(scattered.direction(), rec.normal) > 0;
}