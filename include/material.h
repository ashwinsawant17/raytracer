#pragma once
#include "utils/type_config.h"
#include "utils/vec3.h"

struct Material {
    Vec3d k_d = Vec3d(0.2, 0.2, 0.2);;
    scalar k_s = 0.3;
    scalar p = 90;
    scalar k_m = 0.4;
    Vec3d k_a = Vec3d(0.2, 0.2, 0.2);
    // TODO: add textures for materials
};