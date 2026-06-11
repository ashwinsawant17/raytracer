#pragma once
#include "utils/type_config.h"
#include "utils/vec3.h"

struct Material {
    Vec3d k_d = Vec3d(1, 0.2, 0.2);;
    scalar k_s = 0;
    scalar p = 20;
    scalar k_m = 0;
    Vec3d k_a = k_d;
    // TODO: add textures for materials
};