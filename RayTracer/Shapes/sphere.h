#ifndef SPHERE_H
#define SPHERE_H

#include "Containers/Vector.hpp"
#include "Core/shape.h"
#include "Core/DataTypes.hpp"
#include "Core/Ray.hpp"


namespace ray_tracer::shapes {

class Sphere : public Shape
{
private:
    Matrix<float> m_transform_mat;
    Vector<float> m_origin;
    std::string m_obj_name;
    float m_radius;
    int m_id;

public:
    Sphere(const Vector<float> &origin, const float radius, const int id);

    /**
     * @brief get_radius
     * @return
     */
    float get_radius() const { return m_radius; }

    /**
     * @brief The descritption for functions below can be found in shape.h file.
     *        These methods override methods from the parent class.
     */
    // functions for changing/getting sphere transformation matrix/data
    void transform(const Matrix<float> &transform) override;
    void transform(const Vector<float> &tr_vec, const Matrix<float> &rot_mat) override;

    Matrix<float> get_transform() override { return m_transform_mat; }
    Matrix<float> get_rotation_matrix() override { return m_transform_mat.block(3, 3, 0, 0); }
    Vector<float> get_translation() override { return m_transform_mat.block(3, 1, 0, 3).to_vec_1x3(); }

    // virtual std::vector<Vector<float>> get_normals() override;
    virtual Vector<float> get_normal(const Vector<float> &point) override;

    // scale the object up or down
    virtual void scale(const Vector<float> &scale_vec) override;

    // returns the origin of the object
    Vector<float> get_origin() const override { return m_origin; }

    // returns the id of the object
    int get_id() const override { return m_id; }

    // returns the name of the created sphere
    std::string get_name() const override { return m_obj_name; }

    // compute the intersection of the rays with the sphere
    std::vector<types::intersection> intersect(const Ray &ray) const override;

    ~Sphere() = default;
};

} // namespace ray_tracer::shapes

#endif // SPHERE_H
