#include <memory>

#include <objects/hittable.hpp>
#include <objects/hit_record.hpp>

// hittable_list method definitions
hittable_list::hittable_list(std::shared_ptr<hittable> object) {
  add(object);
}

void hittable_list::clear() {
  objects.clear();
}

void hittable_list::add(std::shared_ptr<hittable> object) {
  objects.emplace_back(object);
}

bool hittable_list::hit(const ray& r, interval ray_interval, hit_record& rec) const {
  hit_record temp_record;
  bool hit_something = false;
  double closest_position = ray_interval.max;

  for (const auto& object : objects) {
    // TODO: Check if the ray hits the object, and update the hit record accordingly
    
  }

  return hit_something;
}