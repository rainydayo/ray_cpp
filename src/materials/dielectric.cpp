#include <cmath>
#include <memory>

#include <materials/base.hpp>
#include <objects/ray.hpp>
#include <objects/hit_record.hpp>
#include <objects/color.hpp>
#include <objects/vec3.hpp>
#include <randomizer.hpp>

// A glass-like material that refracts light
class dielectric : public material {
public:
    double ref_idx; // index of refraction (e.g., 1.5 for glass)

    dielectric(double ri) : ref_idx(ri) {}

    bool scatter(const ray& r_in, const hit_record& rec,
        color& attenuation, ray& scattered) const override {
        attenuation = color(1.0, 1.0, 1.0); // glass absorbs no color

        double refraction_ratio = rec.front_face ? (1.0 / ref_idx) : ref_idx;

        vec3 unit_dir = unit_vector(r_in.direction());
        double cos_theta = fmin(dot(-unit_dir, rec.normal), 1.0);
        double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

        bool cannot_refract = refraction_ratio * sin_theta > 1.0;
        vec3 direction;

        if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double()) {
            direction = reflect(unit_dir, rec.normal);
        }
        else {
            direction = refract(unit_dir, rec.normal, refraction_ratio);
        }

        scattered = ray(rec.p, direction);
        return true;
    }

private:
    static vec3 reflect(const vec3& v, const vec3& n) {
        return v - 2 * dot(v, n) * n;
    }

    static vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
        auto cos_theta = fmin(dot(-uv, n), 1.0);
        vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
        vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
        return r_out_perp + r_out_parallel;
    }

    static double reflectance(double cosine, double ref_idx) {
        // Schlick’s approximation
        auto r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }
};
