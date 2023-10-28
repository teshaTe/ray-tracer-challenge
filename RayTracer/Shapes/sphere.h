#ifndef SPHERE_H
#define SPHERE_H

#include "Containers/Vector.hpp"
#include "Core/shape.h"
#include "Core/DataTypes.hpp"
#include "Core/Ray.hpp"


namespace ray_tracer::shapes {

class Sphere : public Shape
{
private:
    Vector<float> m_origin;
    std::string m_obj_name;
    float m_radius;
    int m_id;

public:
    Sphere(const Vector<float> &origin, const float radius, const int id);

    /**
     * @brief get_origin
     * @return
     */
    Vector<float> get_origin() const override { return m_origin; }

    /**
     * @brief get_id
     * @return
     */
    int get_id() const override { return m_id; }

    /**
     * @brief intersect
     * @param ray
     * @return
     */
    std::vector<types::intersection> intersect(const Ray &ray) const override;

    /**
     * @brief get_name
     * @return
     */
    std::string get_name() const override { return m_obj_name; }

    /**
     * @brief get_radius
     * @return
     */
    float get_radius() const { return m_radius; }

    ~Sphere() = default;
};

} // namespace ray_tracer::shapes

#endif // SPHERE_H
