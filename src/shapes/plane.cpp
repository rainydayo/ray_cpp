// Simple infinite plane: y = k
#include <cmath>
#include <memory>

#include <objects/hittable.hpp>
#include <objects/hit_record.hpp>
#include <objects/interval.hpp>
#include <objects/ray.hpp>
#include <objects/vec3.hpp>

class plane : public hittable {
public:
    double y;                                  // plane height (y = k)
    std::shared_ptr<material> mat;

    plane(double k, std::shared_ptr<material> m) : y(k), mat(std::move(m)) {}

    bool hit(const ray& r, interval ray_interval, hit_record& rec) const override {
        // If ray is parallel to plane, no hit
        double denom = r.direction().y();
        if (std::fabs(denom) < 1e-8) return false;

        // Solve A.y + t * b.y = y
        double t = (y - r.origin().y()) / denom;
        if (!ray_interval.surrounds(t)) return false;

        rec.t = t;
        rec.p = r.at(t);
        vec3 outward_normal(0, 1, 0);               // Upward normal
        rec.set_face_normal(r, outward_normal);     // Orient properly w.r.t. the ray
        rec.mat = mat;
        return true;
    }
};
