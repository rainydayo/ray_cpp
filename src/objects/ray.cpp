#include <objects/ray.hpp>

// ray method definitions
const point3& ray::origin() const {
  return orig;
}

const vec3& ray::direction() const {
  return dir;
}

point3 ray::at(double t) const {
  // TODO: Write the at function that computes the point along the ray at parameter t
  return point3(0, 0, 0);
}