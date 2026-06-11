#include "primitive.h"
#include "material.h"
#include <cmath>
#include <numbers>
#include <iostream>
#include <optional>


Sphere::Sphere(Vec3d c, scalar r, Material m) : 
center(c), radius(r), material(m) {}

Sphere::Sphere(Vec3d c, scalar r) : 
    center(c), radius(r), material(Material{
    .k_d = Vec3d(0.2, 0.2, 0.2),
    .k_s = 0.3,
    .p = 90,
    .k_m = 0.4,
    .k_a = Vec3d(0.2, 0.2, 0.2)
}) {}


std::optional<Hit> Sphere::intersect(Ray& ray) {
    //std::cout << "Computing intersect for sphere" << std::endl;
    Vec3d diff {ray.origin - center};

    scalar a = ray.direction.dot(ray.direction);
    scalar b = 2 * (diff).dot(ray.direction);
    scalar c = (diff).dot(diff) - radius * radius;

    scalar disc = b * b - 4 * a * c;

    // return a "no hit"
    if (disc < 0) {
        return {};
    } else {
        scalar root = std::sqrt(disc);

        scalar t1 = (-b + root) / (2 * a);
        scalar t2 = (-b - root) / (2 * a);

        bool valid_t1 = t1 > ray.start && (!ray.has_end || t1 < ray.end);
        bool valid_t2 = t2 > ray.start && (!ray.has_end || t2 < ray.end);

        scalar t_out;
        if (!valid_t1 && !valid_t2) {
            return {};
        } else if (valid_t1 && valid_t2) {
            t_out = (t1 < t2)? t1 : t2;
        } else if (valid_t1) {
            t_out = t1;
        } else {
            t_out = t2;
        }

        Vec3d intersect_point = ray.origin + ray.direction * t_out;
        Vec3d unit_normal = (intersect_point - center).normalized();

        scalar theta = std::atan2(unit_normal.z, unit_normal.x);
        scalar phi = std::acos(unit_normal.y);
        scalar u = (theta + std::numbers::pi) / (2 * std::numbers::pi);
        scalar v = phi / std::numbers::pi;

        return Hit{
            .hit = true,
            .t = t_out,
            .point = intersect_point,
            .normal = unit_normal,
            .material = this->material,
            .u = u,
            .v = v
        };
    }
}