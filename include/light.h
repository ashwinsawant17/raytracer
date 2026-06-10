#pragma once
#include "primitive.h"
#include "utils/type_config.h"
#include <vector>


class PointLight {
public:
    Vec3d position;
    Vec3d intensity;

    PointLight(Vec3d position, Vec3d intensity);
    PointLight(Vec3d position, scalar intensity);
    ~PointLight();

    Vec3d illuminate(Ray& ray, Hit& hit, std::vector<Primitive>& prims) const;

};


class AmbientLight {
public:
    Vec3d intensity;
    
    AmbientLight(Vec3d intensity);
    AmbientLight(scalar intensity);
    ~AmbientLight();


    Vec3d illuminate(Ray& ray, Hit& hit, std::vector<Primitive>& prims) const;
};


using Light = std::variant<AmbientLight, PointLight>;