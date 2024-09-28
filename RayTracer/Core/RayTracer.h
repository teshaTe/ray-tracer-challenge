#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "DataTypes.hpp"
#include "Ray.hpp"

#include <vector>
#include <string>
#include <memory>

namespace ray_tracer {

class RayTracer
{
private:

public:
    RayTracer() = default;

    Vector<float> get_reflection_vector(const Vector<float> &incident, const Vector<float> &normal);


    ~RayTracer() = default;
};

} // namespace ray_tracer

#endif // RAYTRACER_H
