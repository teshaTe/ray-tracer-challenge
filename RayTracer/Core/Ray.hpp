#ifndef RAY_HPP
#define RAY_HPP

#include "Containers/Vector.hpp"
#include "MatrixUtils.hpp"

namespace ray_tracer {

/**
 * @brief The Ray class
 */
class Ray
{
private:
    Vector<float> m_origin;
    Vector<float> m_direction;

public:
    Ray(const Vector<float> &origin, const Vector<float> &direction): m_origin(origin), m_direction(direction) {}

    /**
     * @brief position
     * @param ray
     * @param t
     * @return
     */
    Vector<float> position(const Ray &ray, const float t)
    {
        return ray.m_origin + ray.m_direction * t;
    }

    Ray translate(const Vector<float> &translation)
    {
        Vector<float> new_origin = m_origin + translation;
        return Ray(new_origin, m_direction);
    }

    Ray scale(const Vector<float> &scaling_vec)
    {
        Vector<float> new_origin = Vector<float>{m_origin[0]*scaling_vec[0], m_origin[1]*scaling_vec[1], m_origin[2]*scaling_vec[2]};
        Vector<float> new_direction = Vector<float>{m_direction[0]*scaling_vec[0], m_direction[1]*scaling_vec[1], m_direction[2]*scaling_vec[2]};
        return Ray(new_origin, new_direction);
    }

    const Vector<float> get_origin() const { return m_origin; }
    const Vector<float> get_direction() const { return m_direction; }
};

} //namespace ray_tracer

#endif // RAY_HPP
