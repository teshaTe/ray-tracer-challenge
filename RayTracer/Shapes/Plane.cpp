#include "Plane.h"

namespace ray_tracer::shapes{

Plane::Plane(const int id): m_obj_name("plane"),
                            m_id(id),
                            m_transform_mat{Matrix<float>{4, 4}},
                            m_origin(Vector<float>{0, 0, 0})
{
    m_transform_mat.I();
    m_material = ray_tracer::materials::BaseMaterial();
}

void Plane::transform(Matrix<float> &transform)
{
    m_transform_mat = transform.mul(m_transform_mat);
    m_origin = m_transform_mat.block(3, 1, 0, 3).to_vec_1x3();
}

Vector<float> Plane::get_normal(const Vector<float> &point)
{
    Matrix<float> inv_obj_tr = m_transform_mat.inv();
    Vector<float> normal = Vector<float>{0, 1, 0, 0};
    Vector<float> world_normal = inv_obj_tr.tr().mul(normal).to_vec_1x3();
    return world_normal.normalize();
}

void Plane::scale(const Vector<float> &scale_vec)
{
    Matrix<float> S = m_mat_utils.scaling_mat(scale_vec[0], scale_vec[1], scale_vec[2]);
    transform(S);
}

void Plane::set_material(materials::BaseMaterial &material)
{
    m_material = material;
}

std::vector<types::intersection> Plane::m_local_intersect(Ray &ray)
{
    std::vector<types::intersection> intersections_out;

    Vector<float> ray_dir = ray.get_direction();
    if(std::abs(ray_dir[1]) < 1e-3)
        return intersections_out;

    float t = ray.get_origin().negate()[1] / ray_dir[1];

    intersections_out.resize(1);
    intersections_out[0].t = t;
    intersections_out[0].obj_type=m_obj_name;

    return intersections_out;
}

std::vector<types::intersection> Plane::intersect(Ray &ray)
{
    Ray tr_ray = ray.transform(m_transform_mat);
    std::vector<types::intersection> intersections = m_local_intersect(tr_ray);
    return intersections;
}

} //namespace ray_tracer::shapes