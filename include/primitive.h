#include "vec3.h"
#include "type_config.h"


// interface for all things that can be intersected with by the ray tracer
class Primitive {
public:
    virtual ~Primitive() = default;
    virtual Vec3d intersect(Vec3d) = 0;
};

// sphere primitive
class Sphere : Primitive {
public:
    Vec3d center;
    scalar radius;


private:


};