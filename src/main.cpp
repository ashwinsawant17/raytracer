#include "image.h"
#include <iostream>
#include "primitive.h"
#include "ray.h"
#include "raytracer.h"

#define WIN_H 600
#define WIN_W 800
#define BUFF_H 600
#define BUFF_W 800


int main(void) {

    Vec3d center = Vec3d(0, 5, -15);
    Sphere s = Sphere(center, 5);
    std::vector<Primitive> prims({s});

    uint32_t w = 2000, h = 500;

    RayTracerParams rt_config {
        .width = w,
        .height = h,
        .prims = prims,
        .lights = std::vector<Light>(),
        .cam_params = {
            .aspect = (scalar) w / h,
            .up = Vec3d(-0.2, 1, 0)
        }
    };

    RayTracer rt(rt_config);

    rt.add_light(PointLight(Vec3d(12, 10, -5), 300));

    rt.render();
    rt.write_image("renders/test4.png");
    return 0;
} 