#include "image.h"
#include <iostream>
#include "light.h"
#include "primitive.h"
#include "ray.h"
#include "raytracer.h"
#include <random>
#include "utils/type_config.h"

#define WIN_H 600
#define WIN_W 800
#define BUFF_H 600
#define BUFF_W 800
#define NUM_SPHERES 50
#define MAX_R 2
#define MIN_R 0.1

int main(void) {

    // initialize random numbers
    std::random_device dev;
    std::mt19937_64 engine(dev());
    std::uniform_real_distribution<scalar> r_dist(MIN_R, MAX_R);
    std::uniform_real_distribution<scalar> d_dist(-100, -10);
    std::uniform_real_distribution<scalar> x_dist(-24, 24);
    std::uniform_real_distribution<scalar> c_dist(0, 1);
    

    // initialize a bunch of random spheres
    std::vector<Primitive> prims{};

    for (int i = 0; i < NUM_SPHERES; i++) {
        Vec3d color(c_dist(engine), c_dist(engine), c_dist(engine));
        Material m = {
            .k_d = color,
            .k_a = color
        };

        scalar r = r_dist(engine);
        Vec3d pos(x_dist(engine), x_dist(engine), d_dist(engine));

        Sphere s(pos, r, m);
        prims.push_back(s);

    }

    /*
    Vec3d center = Vec3d(0, 5, -15);
    Sphere s = Sphere(center, 5);
    std::vector<Primitive> prims({s});
    */
    uint32_t w = 800, h = 600;

    RayTracerParams rt_config {
        .width = w,
        .height = h,
        .prims = prims,
        .lights = std::vector<Light>(),
        .cam_params = {
            .aspect = (scalar) w / h,
            .vfov = std::numbers::pi / 4
        }
    };

    RayTracer rt(rt_config);

    rt.add_light(PointLight(Vec3d(12, 10, -5), 300));
    rt.add_light(PointLight(Vec3d(-20, 13, -5), 200));
    rt.add_light(AmbientLight(0.3));

    rt.render();
    rt.write_image("renders/test4.png");
    return 0;
} 