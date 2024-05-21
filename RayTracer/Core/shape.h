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

    virtual void transform(const Matrix<float> &transform) = 0;
    virtual void transform(const Vector<float> &tr_vec, const Matrix<float> &rot_mat) = 0;
    virtual Matrix<float> get_transform() = 0;
    virtual Matrix<float> get_rotation_matrix() = 0;
    virtual Vector<float> get_translation() = 0;
    // virtual std::vector<Vector<float>> get_normals() = 0;
    virtual Vector<float> get_normal(const Vector<float> &point) = 0;

    virtual void scale(const Vector<float> &scale_vec) = 0;

    virtual int get_id() const = 0;
    virtual std::string get_name() const = 0;

    bool get_surface_hit(const std::vector<types::intersection> &intersections, float *res);
};

} // namespace ray_tracer::prims

#endif // SHAPE_H
