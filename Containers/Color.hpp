#ifndef COLOR_HPP
#define COLOR_HPP

#include <array>
#include <cmath>
#include <iostream>
#include <type_traits>
#include "Vector.hpp"


// TODO: color_checker call in the constructor creates an infinite loop - FIX it


namespace math_types {

template<class T>
class Color
{
private:
    Vector3<T> m_color;

public:
    Color():m_color({0, 0, 0}) {}
    Color(const T red, const T green, const T blue) { m_color = Vector3<T>(red, green, blue); }
    Color(const Vector3<T> color) { m_color = color; }
    Color(const Color<T>& other) { this->m_color = other.m_color; }


    Color<T> operator+(const Color<T>& other) const
    {
        Vector3<T> color = this->m_color + other.m_color;
        return Color<T>(color);
    }

    Color<T> operator-(const Color<T>& other) const
    {
        Vector3<T> color = this->m_color - other.m_color;
        return Color<T>(color);
    }

    Color<T> operator*(const T scalar) const
    {
        Vector3<T> color = this->m_color * scalar;
        return Color<T>(color);
    }

    Color<T> operator/(const T scalar) const
    {
        Vector3<T> color = this->m_color / scalar;
        return Color<T>(color);
    }

    bool operator==(const Color<T>& other) const
    {
        const double eps{0.00001};
        std::array<T, 3> diff{m_color[0] - other.m_color[0], m_color[1] - other.m_color[1], m_color[2] - other.m_color[2]};
        if((std::abs(diff[0]) < eps) && (std::abs(diff[1]) < eps) && (std::abs(diff[2]) < eps))
            return true;
        else
            return false;
    }

    Color<T> hadamard_product(const Color<T>& other) const
    {
        Color<T> color = Color<T>(m_color.x()*other.m_color.x(), m_color.y()*other.m_color.y(), m_color.z()*other.m_color.z());
        return color;
    }

    T r() const { return m_color.x(); }
    T g() const { return m_color.y(); }
    T b() const { return m_color.z(); }

    ~Color() = default;

};

} // namespace math_types


#endif // COLOR_HPP
