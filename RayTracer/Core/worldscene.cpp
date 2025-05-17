#include <iostream>
#include <memory>

#include "worldscene.h"


namespace ray_tracer {

void WorldScene::print_scene_objects()
{
    std::cout << "Scene contains the following shapes: " << std::endl;
    for(auto &shape : m_shapes)
    {
        std::cout << "shape < " << shape->get_type() << "> with id < " << shape->get_id() << " >;" << std::endl;
    }

    std::cout << "Scene contains the following lights: " << std::endl;
    for(auto &light : m_lights)
    {
        std::cout << "light < " << light->get_type() << "> with id < " << light->get_id() << " >;" << std::endl;
    }
}

std::vector<types::intersection> WorldScene::intersect(const Ray &ray)
{
    std::vector<types::intersection> all_intersections;
    for(auto &obj : m_shapes)
    {
        std::vector<types::intersection> intersections = obj->intersect(ray);
        all_intersections.insert(all_intersections.end(), intersections.begin(), intersections.end());
    }
    std::sort(all_intersections.begin(), all_intersections.end());
    return all_intersections;
}

types::intersection_state WorldScene::precompute_intersection_state(shapes::Shape *shape, types::intersection &intersection, Ray &ray)
{
    types::intersection_state state{
        intersection.obj_type,
        ray.position(intersection.t),
        ray.get_direction().negate(),
        shape->get_normal(state.point),
        intersection.t,
    };
    return state;
}

} // namespace ray_tracer
