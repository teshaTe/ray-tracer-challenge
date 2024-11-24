#include "point_light.h"

namespace ray_tracer::lights {

PointLight::PointLight(const Vector<float> &origin, const Color<float> &intensity): m_origin(origin), m_intensity(intensity){}


} // namespace ray_tracer::lights
