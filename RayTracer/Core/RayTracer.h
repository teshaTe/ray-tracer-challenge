#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Material.hpp"
#include "Lights/point_light.h"
#include "Containers/Vector.hpp"
#include "Containers/Color.hpp"
#include "DataTypes.hpp"
#include "worldscene.h"


namespace ray_tracer {

class RayTracer
{
private:

public:
    RayTracer() = default;

    Color<float> compute_lightning(materials::BaseMaterial &material,
                                   lights::Light &light,
                                   Vector<float> &point,
                                   Vector<float> &eye_dir,
                                   Vector<float> &normal);

    Color<float> compute_shading(WorldScene &world_scene, types::intersection_state &intersection_state);


    ~RayTracer() = default;
};

} // namespace ray_tracer

#endif // RAYTRACER_H
