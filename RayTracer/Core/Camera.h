#ifndef CAMERA_H
#define CAMERA_H

#include <memory>
#include "Core/MatrixUtils.hpp"
#include "Containers/Matrix.hpp"
#include "Containers/Vector.hpp"


namespace ray_tracer {

class Camera {
public:
    Camera();
    ~Camera() = default;

    std::unique_ptr<Camera> clone() const {
        return std::make_unique<Camera>(*this); // Copy itself
    }

    void compute_view_transform(const Vector<float> &from, const Vector<float> &to, const Vector<float> &up);
    Matrix<float> get_view_transform() const { return m_view_transform; }

    void set_view_transform(const Matrix<float> &view_transform) { m_view_transform = view_transform; }

private:
    Matrix<float> m_view_transform{4, 4};
    MatrixUtlities m_mat_utils;

};

} //namespace ray_tracer



#endif // LIGHT_HPP
