#pragma once

#include "utils/type_config.h"
#include "material.h"


// struct containing intersection info from a ray and a primitive
// note that by default, it constructs a representation that means there was NO intersection
struct Hit {
    // whether or not it's an actual hit
    bool hit = false;
    // distance along ray at which the hit ocurred
    scalar t = 0;
    // point at which the hit ocurred
    Vec3d point = Vec3d();
    // surface normal of the primitive at the hit point
    Vec3d normal = Vec3d();
    // material of the primitive where it was hit
    Material material = {};
    // texture coords
    scalar u = 0, v = 0;
};


// struct containing a Ray's configuration
// by default start is 0 and there is no end
struct Ray {
    // origin of ray
    Vec3d origin;
    // direction of ray
    Vec3d direction;
    // at what point along the ray to begin detecting hits
    scalar start = 0;
    // whether or not we will cut off the ray at some point
    bool has_end = false;
    // at what point along the ray to stop detecting hits (if has_end is false, this value should not be used)
    scalar end = 0;
};


