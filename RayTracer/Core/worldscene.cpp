#include <iostream>

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

// std::vector<types::intersection> WorldScene::intersect(const Ray &ray)
// {

// }


} // namespace ray_tracer
