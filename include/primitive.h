#pragma once
// std includes
#include <variant>

#include "utils/vec3.h"
#include "utils/type_config.h"
#include "material.h"
#include "ray.h"

// interface for all things that can be intersected with by the ray tracer
class IPrimitive {
public:
    virtual ~IPrimitive() = default;
    virtual Hit intersect(Ray ray) = 0;
};



// sphere primitive
class Sphere : IPrimitive {
public:
    Vec3d center;
    scalar radius;
    Material material;
    Sphere(Vec3d c, scalar r, Material m);
    ~Sphere();
    // constructor for a default material
    Sphere(Vec3d c, scalar r);
    Hit intersect(Ray ray);
private:
};



// so it turns out that you cant make vectors of the type of an abstract class
// so instead we're going to make an alias for a variant type for each primitive we make
using Primitive = Sphere;