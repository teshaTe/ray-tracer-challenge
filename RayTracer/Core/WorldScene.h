#ifndef WORLDSCENE_H
#define WORLDSCENE_H

#include <vector>
#include <memory>

#include "Shape.h"
#include "Ray.hpp"
#include "Light.hpp"
#include "DataTypes.hpp"
#include "Camera.h"


namespace ray_tracer {

class WorldScene
{
public:
    WorldScene() = default;

    bool contains_shapes() const { return !m_shapes.empty(); }
    bool contains_lights() const { return !m_lights.empty(); }
    bool contains_camera() const { return m_camera != nullptr; }

    void print_scene_objects();
    void add_shape(const shapes::Shape &shape) { m_shapes.push_back(shape.clone()); }
    void add_light(const lights::Light &light) { m_lights.push_back(light.clone()); }
    void add_camera(const std::unique_ptr<Camera> &camera) { m_camera = camera->clone(); }

    std::vector<std::unique_ptr<shapes::Shape>>& get_shapes() { return m_shapes; }
    std::vector<std::unique_ptr<lights::Light>>& get_lights() { return m_lights; }
    Camera get_camera() { return *m_camera; }

    void delete_shape(const int& id, const std::string shape_type);
    void delete_light(const int& id, const std::string light_type);
    void delete_camera();

    void clear() {
        m_shapes.clear();
        m_shapes.resize(0);
        m_lights.clear();
        m_lights.resize(0);
        m_camera = nullptr;
    }

    std::vector<types::intersection> intersect(const Ray &ray);
    types::intersection_state precompute_intersection_state(shapes::Shape &shape, types::intersection &intersection, Ray &ray);

    void create_default_world();

    ~WorldScene() = default;

private:
    std::vector<std::unique_ptr<shapes::Shape>> m_shapes;
    std::vector<std::unique_ptr<lights::Light>> m_lights;
    std::unique_ptr<Camera> m_camera;
};

} //namespace ray_tracer



#endif // WORLDSCENE_H
