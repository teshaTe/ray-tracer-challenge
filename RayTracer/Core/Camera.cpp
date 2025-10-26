#include "Core/Camera.h"


namespace ray_tracer {

Camera::Camera(const int h_size, const int v_size, const float fov): m_h_size(h_size),
                                                                     m_v_size(v_size),
                                                                     m_fov(m_mat_utils.toRadiance(fov))
{
    m_view_transform.I();
    float half_view = std::tan(m_fov / 2.0f);
    m_aspect_ratio = static_cast<float>(m_h_size) / static_cast<float>(m_v_size);
    if(m_aspect_ratio >= 1.0f)
    {
        m_half_width = half_view;
        m_half_height = half_view / m_aspect_ratio;
    }
    else
    {
        m_half_width = half_view * m_aspect_ratio;
        m_half_height = half_view;
    }

    m_pixel_size = 2 * m_half_width / m_h_size;
}

void Camera::compute_view_transform(const Vector<float> &from, const Vector<float> &to, const Vector<float> &up)
{
    Vector<float> forward = (to - from).normalize();
    Vector<float> up_normalized = up.normalize();
    Vector<float> left = forward.cross(up_normalized);
    Vector<float> true_up = left.cross(forward);

    Matrix<float> orientation{4, 4};
    orientation.I();

    orientation(0, 0) = left[0];
    orientation(0, 1) = left[1];
    orientation(0, 2) = left[2];

    orientation(1, 0) = true_up[0];
    orientation(1, 1) = true_up[1];
    orientation(1, 2) = true_up[2];

    orientation(2, 0) = -forward[0];
    orientation(2, 1) = -forward[1];
    orientation(2, 2) = -forward[2];

    Matrix<float> translation_mat = m_mat_utils.translation_mat(-from[0], -from[1], -from[2]);
    m_view_transform = orientation.mul(translation_mat);
}

} // namespace ray_tracer
