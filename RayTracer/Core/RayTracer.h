#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Material.hpp"
#include "Core/Light.hpp"
#include "Core/Ray.hpp"
#include "Core/Canvas.hpp"
#include "Core/WorldScene.h"
#include "Containers/Vector.hpp"
#include "Containers/Color.hpp"
#include "DataTypes.hpp"
#include "WorldScene.h"


namespace ray_tracer {

class RayTracer
{
private:
    std::unique_ptr<shapes::Shape> get_shape_by_id(
        const std::vector<std::unique_ptr<shapes::Shape>> shapes, const int shape_id, const std::string &shape_type
        );

public:
    RayTracer() = default;

    Color<float> compute_lightning(materials::BaseMaterial &material,
                                   lights::Light &light,
                                   Vector<float> &point,
                                   Vector<float> &eye_dir,
                                   Vector<float> &normal,
                                   const bool &in_shadow,
                                   Matrix<float> *shape_tr=nullptr);

    const bool is_shadowed(lights::Light &light, WorldScene &world, Vector<float> &point);

    Color<float> compute_shading(
        std::unique_ptr<shapes::Shape> shape,
        std::vector<std::unique_ptr<lights::Light> > &lights,
        types::intersection_state &intersection_state,
        WorldScene &world_scene);

    Color<float> get_color_at(WorldScene &world_scene, Ray &ray);

    Canvas<int> render(Camera &camera, WorldScene &world_scene);

    ~RayTracer() = default;
};

} // namespace ray_tracer

#endif // RAYTRACER_H
