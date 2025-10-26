#ifndef CAMERA_H
#define CAMERA_H

#include <memory>
#include "Core/MatrixUtils.hpp"
#include "Core/Ray.hpp"
#include "Containers/Matrix.hpp"
#include "Containers/Vector.hpp"


namespace ray_tracer {

class Camera {
public:
    Camera(const int h_size, const int v_size, const float fov);
    ~Camera() = default;

    std::unique_ptr<Camera> clone() const {
        return std::make_unique<Camera>(*this); // Copy itself
    }

    void compute_view_transform(const Vector<float> &from, const Vector<float> &to, const Vector<float> &up);

    // get functions
    inline Matrix<float> get_view_transform() const { return m_view_transform; }
    inline float get_pixel_size() const { return m_pixel_size; }
    inline float get_fov() const { return m_fov; }
    inline float get_aspect_ratio() const { return m_aspect_ratio; }
    inline int get_horizontal_size() const { return m_h_size; }
    inline int get_vertical_size() const { return m_v_size; }

    // set functions
    inline void set_view_transform(const Matrix<float> &view_transform) { m_view_transform = view_transform; }

private:
    Matrix<float> m_view_transform{4, 4};
    MatrixUtlities m_mat_utils;
    int m_h_size;
    int m_v_size;
    float m_fov;
    float m_pixel_size;
    float m_aspect_ratio;
    float m_half_width;
    float m_half_height;
};

} //namespace ray_tracer



#endif // LIGHT_HPP
