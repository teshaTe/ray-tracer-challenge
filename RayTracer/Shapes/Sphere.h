#ifndef SPHERE_H
#define SPHERE_H

#include <memory>
#include <string>

#include "Containers/Vector.hpp"
#include "Core/Shape.h"
#include "Core/DataTypes.hpp"
#include "Core/Ray.hpp"
#include "Core/Material.hpp"
#include "Core/MatrixUtils.hpp"


namespace ray_tracer::shapes {

class Sphere : public Shape
{
private:
    Matrix<float> m_transform_mat;
    Vector<float> m_origin;
    ray_tracer::materials::BaseMaterial m_material;
    std::string m_obj_name;
    float m_radius;
    int m_id;
    std::string m_type = "sphere";
    MatrixUtlities m_mat_utils{};

private:
    std::vector<types::intersection> m_local_intersect(Ray &ray);

public:
    Sphere(const float radius, const int id);

    /**
     * @brief The descritption for functions below can be found in shape.h file.
     *        These methods override methods from the parent class.
     */
    // functions for changing/getting sphere transformation matrix/data
    void transform(Matrix<float> &transform) override;

    float get_radius() const { return m_radius; }
    std::string get_type() const override { return m_type; }
    Matrix<float> get_transform() override { return m_transform_mat; }
    Matrix<float> get_rotation_matrix() override { return m_transform_mat.block(3, 3, 0, 0); }
    Vector<float> get_translation() override { return m_transform_mat.block(3, 1, 0, 3).to_vec_1x3(); }
    Vector<float> get_normal(const Vector<float> &point) override;
    Vector<float> get_origin() const override { return m_origin; }
    int get_id() const override { return m_id; }

    // scale the object up or down
    void scale(const Vector<float> &scale_vec) override;

    void set_material(ray_tracer::materials::BaseMaterial &material) override;
    ray_tracer::materials::BaseMaterial get_assigned_material() const override { return m_material; };

    // compute the intersection of the rays with the sphere
    std::vector<types::intersection> intersect(Ray &ray) override;

    std::unique_ptr<shapes::Shape> clone() const override {
        return std::make_unique<Sphere>(*this); // Copy itself
    }

    ~Sphere() = default;
};

} // namespace ray_tracer::shapes

#endif // SPHERE_H
