#ifndef MATRIXUTLITIES_H
#define MATRIXUTLITIES_H


#include "Containers/Matrix.hpp"
#include <vector>
#include <cmath>

#define _USE_MATH_DEFINES
#include <math.h>


namespace ray_tracer {

class MatrixUtlities
{
public:
    MatrixUtlities() = default;

    Matrix<float> translation_mat(const float x, const float y, const float z)
    {
        std::vector<std::vector<float>> m_data{{1, 0, 0, x},
                                               {0, 1, 0, y},
                                               {0, 0, 1, z},
                                               {0, 0, 0, 1}};
        Matrix<float> tr_mat(4, 4, m_data);
        return tr_mat;
    }

    Matrix<float> scaling_mat(const float x, const float y, const float z)
    {
        std::vector<std::vector<float>> m_data{{x, 0, 0, 0},
                                               {0, y, 0, 0},
                                               {0, 0, z, 0},
                                               {0, 0, 0, 1}};
        Matrix<float> s_mat(4, 4, m_data);
        return s_mat;
    }

    Matrix<float> rotation_mat_XAxis(const float angle_rad)
    {
        std::vector<std::vector<float>> m_data{{1, 0, 0, 0},
                                               {0, std::cos(angle_rad), -std::sin(angle_rad), 0},
                                               {0, std::sin(angle_rad), std::cos(angle_rad), 0},
                                               {0, 0, 0, 1}};
        Matrix<float> Rx_mat(4, 4, m_data);
        return Rx_mat;
    }

    Matrix<float> rotation_mat_YAxis(const float angle_rad)
    {
        std::vector<std::vector<float>> m_data{{std::cos(angle_rad), 0, std::sin(angle_rad), 0},
                                               {0, 1, 0, 0},
                                               {-std::sin(angle_rad), 0, std::cos(angle_rad), 0},
                                               {0, 0, 0, 1}};
        Matrix<float> Ry_mat(4, 4, m_data);
        return Ry_mat;
    }

    Matrix<float> rotation_mat_ZAxis(const float angle_rad)
    {
        std::vector<std::vector<float>> m_data{{std::cos(angle_rad), -std::sin(angle_rad), 0, 0},
                                               {std::sin(angle_rad), std::cos(angle_rad), 0, 0},
                                               {0, 0, 1, 0},
                                               {0, 0, 0, 1}};
        Matrix<float> Rz_mat(4, 4, m_data);
        return Rz_mat;
    }

    Matrix<float> skew_mat(const float Xy, const float Xz, const float Yx, const float Yz, const float Zx, const float Zy)
    {
        std::vector<std::vector<float>> m_data{{1, Xy, Xz, 0},
                                               {Yx, 1, Yz, 0},
                                               {Zx, Zy, 1, 0},
                                               {0, 0, 0, 1}};
        Matrix<float> skew_mat(4, 4, m_data);
        return skew_mat;

    }

    float toRadiance(const float angle)
    {
        return (angle/180.0f) * M_PI;
    }

    float toDegrees(const float angle)
    {
        return (angle/M_PI) * 180.0f;
    }

    ~MatrixUtlities() = default;
};

} // namespace ray_tracer
#endif // MATRIXUTLITIES_H
