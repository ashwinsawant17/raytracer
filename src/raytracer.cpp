#include "raytracer.h"
#include <algorithm>
#include <vector>
#include <cmath>
#include <iostream>
#include <optional>


Scene::Scene(std::vector<Primitive> prims, std::vector<Light> lights, Vec3d bg) 
: primitives(prims), lights(lights), background(bg) {}

Scene::Scene(std::vector<Primitive> prims, std::vector<Light> lights) :
    primitives(prims),
    lights(lights),
    background(Vec3d(0, 0, 0)) {}

Scene::Scene(std::vector<Primitive> prims) : 
    primitives(prims),
    lights(std::vector<Light>({AmbientLight(Vec3d(1, 1, 1))})), 
    background(Vec3d(0.2, 0.3, 0.5)) {}

Scene::~Scene() {}

std::optional<Hit> Scene::intersect(Ray& ray) {

    //std::cout << "Performing intersect on scene" << std::endl;
    std::optional<Hit> hit_data;
    //std::cout << "Beginning loop" << std::endl;
    for (Primitive& p : primitives) {
        std::optional<Hit> new_hit = p.intersect(ray);
        // only update the hit data if
        // our current hit is a no hit
        // or the new hit is a hit and it's closer to the ray origin than the old
        if (!hit_data || (new_hit && new_hit->t < hit_data->t)) {
            hit_data = new_hit;
        }
    }
    //std::cout << "Returning Hit data: " << (hit_data.hit? "valid hit" : "no hit") << std::endl;
    return hit_data;
}




Camera::Camera(CameraParams params) {

    aspect = params.aspect;
    f = params.aspect;
    vfov = params.vfov;
    half_height = std::tan(vfov / 2) * f;
    half_width = half_height * aspect;
    std::cout << "Aspect: " << aspect << std::endl;
    std::cout << "Half height: " << half_height << ", Half width: " << half_width << std::endl;
    // TODO: add a slight ofset to normalization so that we don't get div by 0 errors

    // the center of the camera
    eye = params.eye;

    // where the camera is pointing
    forward = params.target - eye;
    forward.normalize();

    // the right of the camera
    up = params.up.normalized();
    right = forward.cross(up);
    right.normalize();

    // the properly computed up vector
    up = (-forward).cross(right);
    up.normalize();

}

Camera::~Camera() {}

Ray Camera::generate_ray(scalar x, scalar y) {
    if (x < 0) x = 0;
    if (x > 1) x = 1;
    if (y < 0) y = 0;
    if (y > 1) y = 1;

    x = (2 * x - 1) * half_width;
    y = (1 - 2 * y) * half_height;
    scalar z = f;

    Vec3d dir_ray = Vec3d(x, y, z);
    Vec3d dir_world = (x * right) + (y * up) + (z * forward);
    dir_world.normalize();
    return Ray({.origin = eye, .direction = dir_world});
}

RayTracer::RayTracer(RayTracerParams params) :
    camera(params.cam_params),
    scene(params.prims, params.lights),
    img_wr(params.num_channels),
    max_depth(params.max_depth), min_k_m(params.min_k_m),
    width(params.width), height(params.height)
{
    pixels = static_cast<uint8_t *>(calloc(params.height * params.width * params.num_channels, 1));
    if (pixels == NULL) {
        std::cout << "Error allocating pixel buffer" << std::endl;
        exit(-1);
    }
}

RayTracer::~RayTracer() {
    free(pixels);
}

void RayTracer::add_light(Light light) {
    scene.lights.push_back(light);
}

void RayTracer::write_image(std::string fname) {
    std::cout << "Writing image" << std::endl;
    img_wr.write_image(fname, 
        width, height, 
        static_cast<void *>(pixels)
    );
}

void RayTracer::clear_buffer() {
    memset(pixels, 0, width * height * img_wr.w_channels);
}

Vec3d RayTracer::shade(Ray& ray, Hit& hit, unsigned int depth) {
    // TODO: add option for texture sampling for background
    
    // starting color output is black due to no light
    Vec3d output = Vec3d(0, 0, 0);
    
    // iterate over all the lights and compute their contribution
    for (const Light light : scene.lights) {

        output += std::visit([&](const auto& l) -> Vec3d{
            return l.illuminate(ray, hit, scene.primitives);
        }, light);
    }

    // TODO: add capability for mirror reflectiosn
    if (depth < max_depth && hit.material.k_m > min_k_m) {
        Vec3d v = (ray.origin - hit.point).normalized();

        // add a slight offset to avoid self intersection
        Ray new_ray = {
            .origin=hit.point,
            .direction=2 * hit.normal.dot(v) * hit.normal - v,
            .start=EPSILON
        };

        std::optional<Hit> new_hit = scene.intersect(new_ray);
        
        // TODO: again, add capability for sampling a background texture
        Vec3d reflected;
        if (new_hit) {
            reflected = shade(new_ray, *new_hit, depth + 1);
        } else {
            reflected = scene.background;
        }

        output += hit.material.k_m * reflected;
    }

    // TODO: use the base color from the texture

    // return the computed color
    return output;

}

Vec3d RayTracer::shade(Ray& ray, Hit& hit) {
    // if we don't want mirror reflection, just pass in the max depth automatically
    return shade(ray, hit, max_depth);
}

void RayTracer::render() {
    //std::cout << "Rendering" << std::endl;

    auto mid_x = width / 2;
    auto mid_y = height / 2;
    for (auto i = 0; i < width; i++) {
        for (auto j = 0; j < height; j++) {

            // compute the color for this pixel
            //std::cout << "Generating Ray" << std::endl;
            Ray ray = camera.generate_ray(((scalar) i + 0.5) / width, ((scalar) j + 0.5) / height);
            //std::cout << "Computing intersect" << std::endl;
            std::optional<Hit> hit = scene.intersect(ray);
            //std::cout << "Computing color" << std::endl;
            if (i == 900 && j == 400) {
                if (hit) std::cout << "Hit Material: " << hit->material.k_d << std::endl;
                if (!hit) std::cout << "No Hit" << std::endl;
            }
            
            Vec3d color;

            if (!hit) {
                color = scene.background;
            } else {
                color = shade(ray, *hit, 0);
            }

            if (i == 900 && j == 400) {
                std::cout << "Color: " << color << std::endl;
            }
            
            // tone mapping, maybe disable?
            // color = color / (color + Vec3d(1.0, 1.0, 1.0));

            // now that we have the color, assign it to our pixels buffer
            // TODO: FOR RIGHT NOW ASSUMES 4 CHANNELS
            auto pixel_ind = (j * width + i) * img_wr.w_channels;
            //std::cout << "i: " << i << ", j: " << j << ", ind: " << pixel_ind << std::endl;
            // red
            pixels[pixel_ind] = static_cast<uint8_t>(std::clamp(color.x, 0.0, 1.0) * 255);
            // blue
            pixels[pixel_ind + 1] = static_cast<uint8_t>(std::clamp(color.y, 0.0, 1.0) * 255);
            // green
            pixels[pixel_ind + 2] = static_cast<uint8_t>(std::clamp(color.z, 0.0, 1.0) * 255);
            pixels[pixel_ind + 3] = 255;
        }
    }
}