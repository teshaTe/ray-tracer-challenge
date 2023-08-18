#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <array>
#include <cmath>
#include <iostream>

namespace math_types {


template <class T>
class Vector3
{
private:
    std::array<T, 3> m_vec={0, 0, 0};
    double _magnitude() const { return std::sqrt(m_vec[0]*m_vec[0] + m_vec[1]*m_vec[1] + m_vec[2]*m_vec[2]); }

public:
    Vector3() = default;
    Vector3(const T x, const T y, const T z) { m_vec = {x, y, z}; }
    Vector3(const Vector3<T>& v) { m_vec[0] = v.x(); m_vec[1] = v.y(); m_vec[2] = v.z(); }

    T& operator[](int i) { return m_vec[i]; }
    Vector3<T> operator+(const Vector3<T>& v) const { return Vector3<T>(this->m_vec[0]+v.x(), this->m_vec[1]+v.y(), this->m_vec[2]+v.z()); }
    Vector3<T> operator-(const Vector3<T>& v) const { return Vector3<T>(this->m_vec[0]-v.x(), this->m_vec[1]-v.y(), this->m_vec[2]-v.z()); }
    Vector3<T> operator-(Vector3<T> v) const { return Vector3<T>(-v.x(), -v.y(), -v.z()); }
    Vector3<T> operator*(const T s) const { return Vector3<T>(this->m_vec[0]*s, this->m_vec[1]*s, this->m_vec[2]*s); }
    Vector3<T> operator/(const T s) const { return Vector3<T>(this->m_vec[0]/s, this->m_vec[1]/s, this->m_vec[2]/s); }


    int size() const { return m_vec.size(); }
    T dot(const Vector3<T>& v) const { return m_vec[0] * v.x() + m_vec[1] * v.y() + m_vec[2] * v.z(); }
    T magnitude() const { return static_cast<T>(_magnitude()); }
    double magnitude_err_type_conv() const { return _magnitude() - magnitude(); }

    Vector3<T> cross(const Vector3<T>& v) const { return Vector3<T>(m_vec[1] * v.z() - m_vec[2] * v.y(),
                                                                    m_vec[2] * v.x() - m_vec[0] * v.z(),
                                                                    m_vec[0] * v.y() - m_vec[1] * v.x()); }
    Vector3<T> normalize() const { return Vector3<T>(m_vec[0], m_vec[1], m_vec[2]) / magnitude(); }
    Vector3<double> normalization_err_type_conv()
    {
        std::array<double, 3> vec = static_cast<double>(m_vec) / _magnitude();
        return Vector3<double>(vec[0], vec[1], vec[2]) - normalize();
    }

    T x() const { return m_vec[0]; }
    T y() const { return m_vec[1]; }
    T z() const { return m_vec[2]; }

    ~Vector3() = default;
};


template<class T>
class Vector4
{
private:
    std::array<T, 4> m_vec={0, 0, 0, 0};
    double _magnitude() const { return std::sqrt(m_vec[0]*m_vec[0] + m_vec[1]*m_vec[1] + m_vec[2]*m_vec[2] + m_vec[3]*m_vec[3]); }

public:
    Vector4() = default;
    Vector4(const T x, const T y, const T z, const T w) { m_vec = {x, y, z, w}; }
    Vector4(const Vector4<T>& v) { m_vec[0] = v.x(); m_vec[1] = v.y(); m_vec[2] = v.z(); m_vec[3] = v.w(); }

    T& operator[](int i) { return m_vec[i]; }
    Vector4<T> operator+(const Vector4<T>& v) const { return Vector4<T>(this->m_vec[0]+v.x(), this->m_vec[1]+v.y(), this->m_vec[2]+v.z(), this->m_vec[3]+v.w()); }
    Vector4<T> operator-(const Vector4<T>& v) const { return Vector4<T>(this->m_vec[0]-v.x(), this->m_vec[1]-v.y(), this->m_vec[2]-v.z(), this->m_vec[3]-v.w()); }
    Vector4<T> operator-(Vector4<T> v) const { return Vector4<T>(-v.x(), -v.y(), -v.z(), -v.w()); }
    Vector4<T> operator*(const T s) const { return Vector4<T>(this->m_vec[0]*s, this->m_vec[1]*s, this->m_vec[2]*s, this->m_vec[3]*s); }
    Vector4<T> operator/(const T s) const { return Vector4<T>(this->m_vec[0]/s, this->m_vec[1]/s, this->m_vec[2]/s, this->m_vec[3]/s); }

    int size() const { return m_vec.size(); }
    T magnitude() const { return static_cast<T>(_magnitude()); }
    double magnitude_err_type_conv() const { return _magnitude() - magnitude(); }

    Vector4<T> normalize() const { return Vector4<T>(m_vec[0], m_vec[1], m_vec[2], m_vec[3]) / magnitude(); }
    Vector4<double> normalization_err_type_conv()
    {
        std::array<double, 4> vec = static_cast<double>(m_vec) / _magnitude();
        return Vector4<double>(vec[0], vec[1], vec[2], vec[3]) - normalize();
    }

    T x() const { return m_vec[0]; }
    T y() const { return m_vec[1]; }
    T z() const { return m_vec[2]; }
    T w() const { return m_vec[3]; }

    ~Vector4() = default;

};

} // namespace math_types


#endif // VECTOR_HPP
