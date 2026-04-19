#include "Sphere.h"
#include "Core/MatrixUtils.hpp"


namespace ray_tracer::shapes {

Sphere::Sphere(const float radius, const int id): m_radius(radius),
                                                  m_obj_name("sphere"),
                                                  m_id(id),
                                                  m_transform_mat{Matrix<float>{4, 4}},
                                                  m_origin(Vector<float>{0, 0, 0})
{
    m_transform_mat.I();
    m_transform_mat = m_mat_utils.scaling_mat(radius, radius, radius).mul(m_transform_mat);
    m_transform_mat(3, 3) = 1;

    m_material = ray_tracer::materials::BaseMaterial();
}

void Sphere::transform(Matrix<float> &transform)
{
    m_transform_mat = transform.mul(m_transform_mat);
    m_origin = m_transform_mat.block(3, 1, 0, 3).to_vec_1x3();
}

Vector<float> Sphere::get_normal(const Vector<float> &point)
{
    Matrix<float> inv_obj_tr = m_transform_mat.inv();
    Vector<float> obj_point = inv_obj_tr.mul(point).to_vec_1x3();
    Vector<float> normal = Vector<float>{obj_point[0], obj_point[1], obj_point[2], 0};
    Vector<float> world_normal = inv_obj_tr.tr().mul(normal).to_vec_1x3();
    return world_normal.normalize();
}

void Sphere::scale(const Vector<float> &scale_vec)
{
    Matrix<float> S = m_mat_utils.scaling_mat(scale_vec[0], scale_vec[1], scale_vec[2]);
    transform(S);
}

void Sphere::set_material(materials::BaseMaterial &material)
{
    m_material = material;
}

std::vector<types::intersection> Sphere::m_local_intersect(Ray &ray)
{
    Vector<float> sphere_to_ray_vec = ray.get_origin() - Vector<float>{0, 0, 0};
    float a = ray.get_direction().dot(ray.get_direction());
    float b = 2.0f * ray.get_direction().dot(sphere_to_ray_vec);
    float c = sphere_to_ray_vec.dot(sphere_to_ray_vec) - 1.0f;

    std::vector<types::intersection> intersections_out;
    float D = b*b - 4.0f*a*c;
    if(D < 0.0f)
    {
        return intersections_out;
    }
    else
    {
        intersections_out.resize(2);
        float t1 = (-b - std::sqrt(D)) / (2.0f * a);
        float t2 = (-b + std::sqrt(D)) / (2.0f * a);
        intersections_out[0].obj_type = m_obj_name;
        intersections_out[1].obj_type = m_obj_name;

        if (t1 > t2)
        {
            intersections_out[0].t = t2;
            intersections_out[1].t = t1;
        }
        else
        {
            intersections_out[0].t = t1;
            intersections_out[1].t = t2;
        }
        return intersections_out;
    }
}

std::vector<types::intersection> Sphere::intersect(Ray &ray)
{
    Ray tr_ray = ray.transform(m_transform_mat);
    std::vector<types::intersection> intersections = m_local_intersect(tr_ray);
    return intersections;
}

} // namespace ray_tracer::shapes
