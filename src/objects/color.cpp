#include <cmath>

#include <objects/interval.hpp>
#include <objects/color.hpp>
#include <objects/vec3.hpp>

// color utility function definitions
double linear_to_gamma(double linear) {
  if(linear > 0) {
    return std::sqrt(linear);
  }
  return 0;
}

color get_color_byte(color c) {
    // Apply gamma correction (gamma=2.0 → sqrt)
    return color(
        static_cast<int>(256 * interval(0.0, 0.999).clamp(linear_to_gamma(c.x()))),
        static_cast<int>(256 * interval(0.0, 0.999).clamp(linear_to_gamma(c.y()))),
        static_cast<int>(256 * interval(0.0, 0.999).clamp(linear_to_gamma(c.z())))
    );
}
