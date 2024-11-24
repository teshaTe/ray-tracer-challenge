#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <cassert>


namespace ray_tracer {


/**
 * @brief The Vector class
 */

template <class T>
class Vector
{
private:
    std::vector<T> m_vec;
    T m_zero = 0;

public:
    /**
     * @brief Vector
     * @param size
     */
    Vector(size_t size){ set_zeros(size); };

    /**
     * @brief Vector
     * @param x
     * @param y
     */
    Vector(const T x, const T y)
    {
        m_vec.resize(2);
        m_vec[0] = x;
        m_vec[1] = y;
    }

    /**
     * @brief Vector
     * @param x
     * @param y
     * @param z
     */
    Vector(const T x, const T y, const T z)
    {
        m_vec.resize(3);
        m_vec[0] = x;
        m_vec[1] = y;
        m_vec[2] = z;
    }

    /**
     * @brief Vector
     * @param x
     * @param y
     * @param z
     * @param w
     */
    Vector(const T x, const T y, const T z, const T w)
    {
        m_vec.resize(4);
        m_vec[0] = x;
        m_vec[1] = y;
        m_vec[2] = z;
        m_vec[3] = w;
    }

    /**
     * @brief Vector
     * @param v
     */
    Vector(const std::vector<T> &v)
    {
        if(v.size() > 1 && v.size() < 5)
            m_vec = v;
        else
            throw std::runtime_error( "Specified vector size is unsupported by this class. Supported sizes are: 2, 3, 4.");
    }

    /**
     * @brief Vector
     * @param other
     */
    Vector(const Vector<T> &other) { m_vec = other.m_vec; }

    /**
     * @brief operator []
     * @param i
     * @return
     */
    T &operator[](int i) { return m_vec[i]; }
    const T& operator[] (int i) const { return m_vec[i]; }

    /**
     * @brief operator +
     * @param other
     * @return
     */
    Vector<T> operator+(const Vector<T> &other) const
    {
        assert(m_vec.size() == other.m_vec.size());
        std::vector<T> res;
        res.resize(m_vec.size());
        std::transform(this->m_vec.begin(), this->m_vec.end(), other.m_vec.begin(), res.begin(), std::plus<T>());
        return Vector<T>{res};
    }

    /**
     * @brief operator -
     * @param other
     * @return
     */
    Vector<T> operator-(const Vector<T> &other) const
    {
        assert(m_vec.size() == other.m_vec.size());
        std::vector<T> res;
        res.resize(m_vec.size());
        std::transform(m_vec.begin(), m_vec.end(), other.m_vec.begin(), res.begin(), std::minus<T>());
        return Vector<T>{res};
    }

    /**
     * @brief operator *
     * @param s
     * @return
     */
    Vector<T> operator*(const T s) const
    {
        std::vector<T> tmp;
        tmp.resize(m_vec.size());
        std::transform(m_vec.begin(), m_vec.end(), tmp.begin(), [s](T e) { return e*s; });
        return Vector<T>{tmp};
    }

    /**
     * @brief operator /
     * @param s
     * @return
     */
    Vector<T> operator/(const T s) const
    {
        std::vector<T> tmp;
        tmp.resize(m_vec.size());
        std::transform(m_vec.begin(), m_vec.end(), tmp.begin(), [s](T e) { return e/s; });
        return Vector<T>{tmp};
    }

    /**
     * @brief operator ==
     * @param other
     * @return
     */
    bool operator==(const Vector<T> &other) const
    {
        const double eps{0.00001};
        std::vector<T> diff;
        diff.resize(m_vec.size());
        std::transform(m_vec.begin(), m_vec.end(), other.m_vec.begin(), diff.begin(), std::minus<T>());
        bool ok = std::all_of(diff.begin(), diff.end(), [eps](T e) { return e < eps; });
        if(ok)
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
    friend std::ostream& operator<<(std::ostream& os, const Vector<T>& v)
    {
        os << "[ ";
        for(auto e : v.m_vec)
            os << e << ", ";
        os << "]";
        return os;
    }

    /**
     * @brief size
     * @return
     */
    size_t size() const { return m_vec.size(); }

    /**
     * @brief set_zeros
     * @param size
     */
    void set_zeros(size_t size)
    {
        if(size > 0 && size < 5)
        {
            m_vec.resize(size);
            std::fill(m_vec.begin(), m_vec.end(), m_zero);
        }
        else
            throw std::runtime_error("[ERROR] Cannot create vector of size 5 or more!");
    }

    /**
     * @brief dot
     * @param other
     */
    T dot(const Vector<T> other) const
    {
        std::vector<T> tmp;
        tmp.resize(m_vec.size());
        std::transform(m_vec.begin(), m_vec.end(), other.m_vec.begin(), tmp.begin(), std::multiplies<T>());
        T res = std::accumulate(tmp.begin(), tmp.end(), m_zero);
        return res;
    }

    /**
     * @brief magnitude
     */
    T magnitude() const
    {
        std::vector<T> tmp;
        tmp.resize(m_vec.size());
        std::transform(m_vec.begin(), m_vec.end(), m_vec.begin(), tmp.begin(), std::multiplies<T>());
        T res = std::accumulate(tmp.begin(), tmp.end(), m_zero);
        return std::sqrt(res);
    }

    /**
     * @brief cross
     * @param other
     * @return
     */
    Vector<T> cross(const Vector<T>& other) const
    {
        assert(m_vec.size() == other.size());
        assert(m_vec.size() == 3);
        assert(other.m_vec.size() == 3);

        std::vector<T> tmp{m_vec[1] * other.m_vec[2] - m_vec[2] * other.m_vec[1],
                           m_vec[2] * other.m_vec[0] - m_vec[0] * other.m_vec[2],
                           m_vec[0] * other.m_vec[1] - m_vec[1] * other.m_vec[0]};
        return Vector<T>{tmp};
    }

    /**
     * @brief normalize
     * @return
     */
    Vector<T> normalize() const
    {
        T magn = magnitude();
        std::vector<T> tmp;
        tmp.resize(m_vec.size());
        std::transform(m_vec.begin(), m_vec.end(), tmp.begin(), [magn](T e) { return e/static_cast<T>(magn); });
        return Vector<T>{tmp};
    }

    /**
     * @brief negate
     * @return
     */
    Vector<T> negate() const
    {
        std::vector<T> tmp;
        tmp.resize(m_vec.size());
        std::transform(m_vec.begin(), m_vec.end(), tmp.begin(), [](T e) { return -e; });
        return Vector<T>{tmp};
    }

    /**
     * @brief get_reflection
     * @param in_vec
     * @param normal
     * @return
     */
    Vector<float> reflect(const Vector<float> &normal)
    {
        Vector<float> in_vec{m_vec};
        return in_vec - normal * 2.0f * in_vec.dot(normal);
    }

    /**
     * @brief data
     * @return
     */
    std::vector<T> data() const { return m_vec; }

    ~Vector() = default;
};

} // namespace ray_tracer


#endif // VECTOR_HPP
