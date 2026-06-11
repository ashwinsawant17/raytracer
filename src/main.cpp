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

Scene random_spheres() {
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
            .k_a = color,
        };

        scalar r = r_dist(engine);
        Vec3d pos(x_dist(engine), x_dist(engine), d_dist(engine));

        Sphere s(pos, r, m);
        prims.push_back(s);

    }

    std::vector<Light> lights = {
        PointLight(Vec3d(12, 10, -5), 300),
        PointLight(Vec3d(-20, 13, -5), 200),
        AmbientLight(0.3)
    };

    Scene s(prims, lights);

    return s;
}

int main(void) {

    

    Material tan = {
        .k_d=Vec3d(0.4, 0.4, 0.2),
        .k_s = 0.3,
        .p = 90,
        .k_m=0.3
    };

    Material blue = {
        .k_d = Vec3d(0.2, 0.2, 0.4),
        .k_m = 0.5
    };

    Material gray = {
        .k_d = Vec3d(0.2, 0.2, 0.2),
        .k_m = 0.5
    };

    std::vector<Primitive> prims = {
        Sphere(Vec3d(-0.7, 0, 0), 0.5, tan),
        Sphere(Vec3d(0.7, 0, 0), 0.5, blue),
        Sphere(Vec3d(0, -40, 0), 39.5, gray)
    };

    std::vector<Light> lights = {
        PointLight(Vec3d(12, 10,5), 300),
        AmbientLight(.2)
    };
    

    uint32_t w = 1920, h = 1080;

    RayTracerParams rt_config {
        .width = w,
        .height = h,
        .max_depth = 4,
        .min_k_m = 0.00000001,
        .prims = prims,
        .lights = lights,
        .cam_params = {
            .aspect = (scalar) w / h,
            .vfov = std::numbers::pi / 4,
            .eye = Vec3d(3, 1.2, 5),
            .target = Vec3d(0, -0.4, 0)
        }
    };

    RayTracer rt(rt_config);
    rt.scene.background = Vec3d(0.2, 0.3, 0.5);
    rt.render();
    rt.write_image("renders/test5.png");
    return 0;
} 