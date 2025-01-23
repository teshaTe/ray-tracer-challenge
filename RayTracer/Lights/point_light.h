#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "Containers/Vector.hpp"
#include "Containers/Color.hpp"
#include "Core/Light.hpp"

namespace ray_tracer::lights {

class PointLight: public Light
{
private:
    Vector<float> m_origin;
    Color<float> m_intensity;

public:
    PointLight(const Vector<float> &origin, const Color<float> &intensity);

    Vector<float> get_origin() const override { return m_origin; };
    Color<float> get_intensity() const override { return m_intensity; };

    void set_origin(const Vector<float> &origin) override { m_origin = origin; };
    void set_intensity(const Color<float> &intensity) override { m_intensity = intensity; };

    ~PointLight() = default;
};

} // namespace ray_tracer::lights
#endif // POINT_LIGHT_H
