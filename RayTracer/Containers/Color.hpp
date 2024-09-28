#ifndef COLOR_HPP
#define COLOR_HPP

#include <cmath>
#include <iostream>
#include <type_traits>
#include <cassert>
#include "Vector.hpp"


namespace ray_tracer {

/**
 * @brief The Color class
 */

template<class T>
class Color
{
private:
    Vector<T> m_color{0, 0, 0};

public:
    /**
     * @brief Color
     */
    Color() = default;

    /**
     * @brief Color
     * @param red
     * @param green
     * @param blue
     */
    Color(const T red, const T green, const T blue) { m_color = Vector<T>{red, green, blue}; }

    /**
     * @brief Color
     * @param color
     */
    Color(const Vector<T>& color)
    {
        assert(color.size() == 3);
        m_color = color;
    }

    /**
     * @brief Color
     * @param other
     */
    Color(const Color<T>& other) { this->m_color = other.m_color; }

    /**
     * @brief operator []
     * @param i
     * @return
     */
    T &operator[](int i) { return m_color[i]; }

    /**
     * @brief operator +
     * @param other
     * @return
     */
    Color<T> operator+(const Color<T>& other) const
    {
        Vector<T> color = this->m_color + other.m_color;
        return Color<T>(color);
    }

    /**
     * @brief operator -
     * @param other
     * @return
     */
    Color<T> operator-(const Color<T>& other) const
    {
        Vector<T> color = this->m_color - other.m_color;
        return Color<T>(color);
    }

    /**
     * @brief operator *
     * @param scalar
     * @return
     */
    Color<T> operator*(const T scalar) const
    {
        Vector<T> color = this->m_color * scalar;
        return Color<T>(color);
    }

    /**
     * @brief operator /
     * @param scalar
     * @return
     */
    Color<T> operator/(const T scalar) const
    {
        Vector<T> color = this->m_color / scalar;
        return Color<T>(color);
    }

    /**
     * @brief operator ==
     * @param other
     * @return
     */
    bool operator==(const Color<T>& other) const
    {
        const double eps{0.00001};
        Vector<T> diff = m_color - other.m_color;
        if((std::abs(diff[0]) < eps) && (std::abs(diff[1]) < eps) && (std::abs(diff[2]) < eps))
            return true;
        else
            return false;
    }

    /**
     * @brief operator <<
     * @param os
     * @param v
     * @return
     */
    friend std::ostream& operator<<(std::ostream& os, const Color<T>& v)
    {
        os << "[" << v.r() << ", " << v.g() << ", " << v.b() << "]";
        return os;
    }

    /**
     * @brief hadamard_product
     * @param other
     * @return
     */
    Color<T> hadamard_product(const Color<T>& other)
    {
        Color<T> color = Color<T>( m_color[0]*other.m_color[0],  m_color[1]*other.m_color[1], m_color[2]*other.m_color[2]);
        return color;
    }

    /**
     * @brief r
     * @return
     */
    T r() const { return m_color[0]; }

    /**
     * @brief g
     * @return
     */
    T g() const { return m_color[1]; }

    /**
     * @brief b
     * @return
     */
    T b() const { return m_color[2]; }

    ~Color() = default;
};

} // namespace ray_tracer


#endif // COLOR_HPP
