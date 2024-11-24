#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Material.hpp"
#include "Lights/point_light.h"
#include "Containers/Vector.hpp"


namespace ray_tracer {

class RayTracer
{
private:

public:
    RayTracer() = default;

    Color<float> compute_lightning(materials::BaseMaterial &material,
                                   lights::PointLight &light,
                                   Vector<float> &point,
                                   Vector<float> &eye_dir,
                                   Vector<float> &normal);


    ~RayTracer() = default;
};

} // namespace ray_tracer

#endif // RAYTRACER_H
