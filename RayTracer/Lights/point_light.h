#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include <string>

#include "Containers/Vector.hpp"
#include "Containers/Color.hpp"
#include "Core/Light.hpp"


namespace ray_tracer::lights {

class PointLight: public Light
{
private:
    Vector<float> m_origin;
    Color<float> m_intensity;
    int m_id;
    std::string m_type = "point_light";

public:
    PointLight(const Vector<float> &origin, const Color<float> &intensity);

    Vector<float> get_origin() const override { return m_origin; };
    Color<float> get_intensity() const override { return m_intensity; };
    int get_id() const override { return m_id; }
    std::string get_type() const override { return m_type; }

    void set_origin(const Vector<float> &origin) override { m_origin = origin; };
    void set_intensity(const Color<float> &intensity) override { m_intensity = intensity; };

    std::unique_ptr<Light> clone() const override {
        return std::make_unique<PointLight>(*this); // Copy itself
    }

    ~PointLight() = default;
};

} // namespace ray_tracer::lights
#endif // POINT_LIGHT_H
