#include "primitive.h"
#include "utils/type_config.h"
#include "light.h"
#include <vector>
#include <iostream>


PointLight::PointLight(Vec3d position, Vec3d intensity) :
position(position), intensity(intensity) {}

PointLight::PointLight(Vec3d position, scalar intensity):
position(position), intensity(Vec3d(intensity, intensity, intensity)) {}

PointLight::~PointLight() {}

Vec3d PointLight::illuminate(Ray& ray, Hit& hit, std::vector<Primitive>& prims) const {
    // first test if hit point is even visible from our light source
    Vec3d direction = position - hit.point;
    scalar dist = direction.norm();
    direction /= dist;
    Ray temp_ray{.origin=hit.point, .direction=direction, .start = EPSILON};

    // iterate through the primitives given to see if we intersect with them before our hit
    bool in_shadow = false;
    for (Primitive& p : prims) {
        std::optional<Hit> temp_hit = p.intersect(temp_ray);

        // if this hit is closer to the point light than our actual hit, then it's in shadow
        if (temp_hit && dist > temp_hit->t + EPSILON) {
            in_shadow = true;
        }
    }
    in_shadow = false;
    // if the hit is in shadow, simply return a 0 vector
    if (in_shadow) {
        return Vec3d(0, 0, 0);
    
    // if it's not in shadow, compute the light calculations
    } else {
        //std::cout << "In Light" << std::endl;
        Vec3d& n = hit.normal;
        Vec3d& l = direction;
        Vec3d v = (ray.origin - hit.point).normalized();
        Vec3d h = (l + v).normalized();

        Material& m = hit.material;

        scalar& r = dist;

        Vec3d l_base = std::max((scalar) 0, n.dot(l)) * intensity / (r * r);
        scalar f_spec = m.k_s * std::pow(std::max((scalar) 0, n.dot(h)), m.p);
    
        Vec3d l_diffuse = m.k_d * l_base;
        Vec3d l_spec = f_spec * l_base;

        return l_diffuse + l_spec;
    }
}


AmbientLight::AmbientLight(Vec3d intensity) : intensity(intensity) {}
AmbientLight::AmbientLight(scalar intensity) : intensity(intensity, intensity, intensity) {}
AmbientLight::~AmbientLight() {}
Vec3d AmbientLight::illuminate(Ray& ray, Hit& hit, std::vector<Primitive>& prims) const {
    return intensity * hit.material.k_a;
}