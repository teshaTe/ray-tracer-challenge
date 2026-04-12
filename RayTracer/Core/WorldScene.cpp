#include <iostream>
#include <memory>

#include "WorldScene.h"
#include "Lights/point_light.h"
#include "Shapes/Sphere.h"


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

void WorldScene::delete_shape(const int &id, const std::string shape_type)
{
    m_shapes.erase(std::remove_if(m_shapes.begin(), m_shapes.end(),
                                  [&](const std::unique_ptr<shapes::Shape>& s) {
                                      return (s.get()->get_id()==id && s.get()->get_type()==shape_type);
                                  }
                                  ), m_shapes.end());
}

void WorldScene::delete_light(const int &id, const std::string light_type)
{
    m_lights.erase(std::remove_if(m_lights.begin(), m_lights.end(),
                                  [&](const std::unique_ptr<lights::Light>& l) {
                                      return (l.get()->get_id()==id && l.get()->get_type()==light_type);
                                  }
                                  ), m_lights.end());
}

std::vector<types::intersection> WorldScene::intersect(Ray &ray)
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

types::intersection_state WorldScene::precompute_intersection_state(shapes::Shape &shape, types::intersection &intersection, Ray &ray)
{
    Vector<float> point = ray.position(intersection.t);
    Vector<float> eye_dir = ray.get_direction().negate();
    Vector<float> normal = shape.get_normal(point);

    bool inside = false;
    if(normal.dot(eye_dir) < 0)
    {
        inside = true;
        normal = normal.negate();
    }

    Vector<float> over_point = point + normal * 1e-3;

    types::intersection_state state{
        intersection.obj_type,
        intersection.obj_id,
        point,
        over_point,
        eye_dir,
        normal,
        intersection.t,
        inside
    };
    return state;
}

void WorldScene::create_default_world()
{
    materials::BaseMaterial mat1;
    mat1.color = Color<float>{0.8, 1.0, 0.6};
    mat1.ambient = 0.1;
    mat1.diffuse = 0.7;
    mat1.specular = 0.2;
    mat1.shininess = 200.0;

    shapes::Sphere sp1{1.0, 0};
    sp1.set_material(mat1);

    shapes::Sphere sp2{0.5, 1};
    materials::BaseMaterial mat2;
    sp2.set_material(mat2);

    add_shape(sp1);
    add_shape(sp2);

    lights::PointLight plight1{Vector<float>{-10, 10, -10}, Color<float>{1, 1, 1}, 0};
    add_light(plight1);
}

} // namespace ray_tracer
