#include "sphere.h"


namespace ray_tracer::shapes {

Sphere::Sphere(const Vector<float> &origin, const float radius, const int id): m_radius(radius),
                                                                               m_origin(origin),
                                                                               m_obj_name("sphere"),
                                                                               m_id(id),
                                                                               m_transform_mat{Matrix<float>{4, 4}}
{
    m_transform_mat.I();
}

void Sphere::transform(const Matrix<float> &transform)
{

}

void Sphere::transform(const Vector<float> &tr_vec, const Matrix<float> &rot_mat)
{

}

std::vector<types::intersection> Sphere::intersect(const Ray &ray) const
{
    Vector<float> sphere_to_ray_vec = ray.get_origin() - m_origin;
    float a = ray.get_direction().dot(ray.get_direction());
    float b = 2.0f * ray.get_direction().dot(sphere_to_ray_vec);
    float c = sphere_to_ray_vec.dot(sphere_to_ray_vec) - 1.0f;

    std::vector<types::intersection> intersections_out;
    float D = b*b - 4*a*c;
    if(D < 0)
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


} // namespace ray_tracer::shapes
