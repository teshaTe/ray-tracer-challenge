#ifndef SHAPE_H
#define SHAPE_H

#include "Containers/Vector.hpp"
#include "Core/DataTypes.hpp"
#include "Core/Ray.hpp"

#include <string>
#include <vector>

namespace ray_tracer::shapes {

class Shape
{
public:
    virtual ~Shape() = default;

    virtual Vector<float> get_origin() const = 0;
    virtual std::vector<types::intersection> intersect(const Ray &ray) const = 0;

    //    virtual void transform(Vector<float> transform) = 0;
    //    virtual void scale() = 0;

    virtual int get_id() const = 0;
    virtual std::string get_name() const = 0;

    bool get_surface_hit(const std::vector<types::intersection> &intersections, float *res);

};

} // namespace ray_tracer::prims

#endif // SHAPE_H
