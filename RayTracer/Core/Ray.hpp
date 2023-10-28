#ifndef RAY_HPP
#define RAY_HPP

#include "Containers/Vector.hpp"

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

    const Vector<float> get_origin() const { return m_origin; }
    const Vector<float> get_direction() const { return m_direction; }
};

} //namespace ray_tracer

#endif // RAY_HPP
