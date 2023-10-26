#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Containers/Vector.hpp"
#include "Primitive.hpp"


namespace ray_tracer::prims {

/**
 * @brief The Sphere class
 */
class Sphere : public PrimitiveObj
{
private:
    Vector<float> m_origin;
    float m_radius;
    int m_id;

public:
    Sphere(const Vector<float> &origin, const float radius, const int id): m_radius(radius), m_origin(origin), m_id(id) { m_type = "sphere"; }

    /**
     * @brief intersect
     * @param ray
     * @return
     */
    std::vector<int> intersect(const Ray &ray) const override
    {
        Vector<float> sphere_to_ray_vec = ray.get_origin() - m_origin;
        float a = ray.get_direction().dot(ray.get_direction());
        float b = 2.0f * ray.get_direction().dot(sphere_to_ray_vec);
        float c = sphere_to_ray_vec.dot(sphere_to_ray_vec) - 1.0f;

        std::vector<int> intersections_out;
        float D = b*b - 4*a*c;
        if(D < 0)
        {
            return intersections_out;
        }
        else
        {
            intersections_out.resize(2);
            intersections_out[0] = (-b - std::sqrt(D)) / (2.0f * a);
            intersections_out[1] = (-b + std::sqrt(D)) / (2.0f * a);
            return intersections_out;
        }
    }

    /**
     * @brief get_origin
     * @return
     */
    Vector<float> get_origin() const override { return m_origin; }

    /**
     * @brief get_radius
     * @return
     */
    float get_radius() const { return m_radius; }

    /**
     * @brief get_id
     * @return
     */
    int get_id() const override { return m_id; }

    ~Sphere() = default;
};

} // namespace ray_tracer::prims

#endif // SPHERE_HPP
