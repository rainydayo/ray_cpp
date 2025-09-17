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
  // TODO: Convert the color from linear space to gamma space
  
  return color(0, 0, 0);
}