#include "point_light.h"

namespace ray_tracer::lights {

PointLight::PointLight(const Vector<float> &origin, const Color<float> &intensity, int id):
    m_origin(origin),
    m_intensity(intensity),
    m_id(id){}


} // namespace ray_tracer::lights
