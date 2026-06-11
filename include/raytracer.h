#pragma once
// std includes
#include <vector>
#include <variant>
#include <numbers>
#include <cstdint>
#include <cstring>
#include <optional>

// raytracer includes
#include "material.h"
#include "primitive.h"
#include "texture.h"
#include "utils/type_config.h"
#include "light.h"
#include "image.h"

// class that represents the Scene, owns all the primitives and lights
class Scene {
public:
    std::vector<Primitive> primitives;
    std::vector<Light> lights;
    // TODO: add functionality for background to be a texture not just a plain color
    Vec3d background;

    Scene(std::vector<Primitive> prims, std::vector<Light> lights, Vec3d bg);
    Scene(std::vector<Primitive> prims, std::vector<Light> lights);
    Scene(std::vector<Primitive> prims);
    ~Scene();

    std::optional<Hit> intersect(Ray& ray);
};

struct CameraParams {
    scalar aspect = 1;
    scalar f = 1;
    scalar vfov = std::numbers::pi / 2;         // 90 degrees

    Vec3d eye = Vec3d(0, 0, 0);
    Vec3d right = Vec3d(1, 0, 0);
    Vec3d target = Vec3d(0, 0, -1);
    Vec3d up = Vec3d(0, 1, 0);
};

class Camera {
public:
    Vec3d eye;
    Vec3d right;
    Vec3d up;
    Vec3d forward;
    scalar vfov;
    scalar aspect;
    scalar f;

    scalar half_height, half_width;

    Camera(CameraParams params);
    ~Camera();

    // generates a ray that passes through the image plane where (0, 0) is top left and (1, 1) is bottom right
    // clamps the values in those bounds if need be
    Ray generate_ray(scalar x, scalar y);
};


struct RayTracerParams {
    uint32_t width;
    uint32_t height;
    uint8_t max_depth = 4;
    scalar min_k_m = 0.00000001;
    uint8_t num_channels = 4;
    std::vector<Primitive> prims;
    std::vector<Light> lights = std::vector<Light>({AmbientLight(Vec3d(1, 1, 1))});
    CameraParams cam_params = {};
};

// class that represents the actual raytracer itself
// owns the camera, generates the rays, and owns the frame buffers
class RayTracer {
public:
    Camera camera;
    Scene scene;
    ImageWriter img_wr;
    uint32_t width, height;
    uint8_t max_depth;
    scalar min_k_m;
    uint8_t *pixels;


    RayTracer(RayTracerParams params);
    ~RayTracer();

    void add_light(Light light);
    Vec3d shade(Ray &ray, Hit& hit, unsigned int depth);
    Vec3d shade(Ray& ray, Hit& hit);
    void render();
    void write_image(std::string fname);
    void clear_buffer();
};