#ifndef WORLDSCENE_H
#define WORLDSCENE_H

#include <vector>
#include <memory>

#include "shape.h"
#include "Ray.hpp"
#include "Light.hpp"
#include "DataTypes.hpp"


namespace ray_tracer {

class WorldScene
{
public:
    WorldScene() = default;

    bool contains_shapes() const { return !m_shapes.empty(); }
    bool contains_lights() const { return !m_lights.empty(); };

    void print_scene_objects();
    void add_shape(const shapes::Shape &shape) { m_shapes.push_back(shape.clone()); }
    void add_light(const lights::Light &light) { m_lights.push_back(light.clone()); }

    void delete_shape(const int& id);
    void delete_light(const int& id);

    void clear() {
        m_shapes.clear();
        m_shapes.resize(0);
        m_lights.clear();
        m_lights.resize(0);
    }

    std::vector<types::intersection> intersect(const Ray &ray);

    ~WorldScene() = default;

private:


private:
    std::vector<std::unique_ptr<shapes::Shape>> m_shapes;
    std::vector<std::unique_ptr<lights::Light>> m_lights;
};

}



#endif // WORLDSCENE_H
