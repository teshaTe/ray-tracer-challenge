#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include "Vector.hpp"


namespace ray_tracer {

/**
 * @brief The Matrix class
 */

template<class T>
class Matrix
{
private:
    std::vector<std::vector<T>> m_mat;
    int m_rows;
    int m_cols;
    T m_zero = 0;

    typedef typename std::vector<std::vector<T>>::iterator iterator;
    typedef typename std::vector<std::vector<T>>::const_iterator const_iterator;

public:
    /**
     * @brief Matrix
     * @param rows
     * @param cols
     * @param data
     */
    Matrix(const int rows, const int cols, const std::vector<std::vector<T>> *data = nullptr): m_rows{rows}, m_cols{cols}
    {
        m_mat.resize(rows);
        for(auto &c : m_mat)
        {
            c.resize(cols);
            std::fill(c.begin(), c.end(), m_zero);
        }

        if(data != nullptr)
            if(data->size() == rows && data[0].size() == cols)
                m_mat = *data;
    }

    /**
     * @brief Matrix
     * @param other
     */
    Matrix(const Matrix<T>& other) { this->m_mat = other.m_mat; m_rows = other.m_rows; m_cols = other.m_cols; }

    /**
     * @brief begin
     * @return
     */
    iterator begin() { return m_mat.begin(); }

    /**
     * @brief begin
     * @return
     */
    const_iterator begin() const { return m_mat.begin(); }

    /**
     * @brief end
     * @return
     */
    iterator end() { return m_mat.end(); }

    /**
     * @brief end
     * @return
     */
    const_iterator end() const { return m_mat.end(); }

    /**
     * @brief operator ()
     * @param i
     * @param j
     * @return
     */
    T& operator()(int i, int j) { return m_mat[i][j]; }

    /**
     * @brief operator +
     * @param other
     * @return
     */
    Matrix<T> operator+(const Matrix<T>& other)
    {
        if(this->m_cols == other.m_cols && this->m_rows == other.m_rows)
        {
            for(size_t r = 0; r < m_mat.size(); ++r)
                std::transform(m_mat[r].begin(), m_mat[r].end(), other.m_mat[r].begin(), m_mat[r].begin(), std::plus<T>());
            return Matrix<T>(m_rows, m_cols, &m_mat);
        }
        else
            throw("Sizes of two matrices are mismatched");
    }

    /**
     * @brief operator -
     * @param other
     * @return
     */
    Matrix<T> operator-(const Matrix<T>& other)
    {
        if(this->m_cols == other.m_cols && this->m_rows == other.m_rows)
        {
            for(size_t r = 0; r < m_mat.size(); ++r)
                std::transform(m_mat[r].begin(), m_mat[r].end(), other.m_mat[r].begin(), m_mat[r].begin(), std::minus<T>());
            return Matrix<T>(m_rows, m_cols, &m_mat);
        }
        else
            throw("Sizes of two matrices are mismatched");
    }

    /**
     * @brief operator /
     * @param scalar
     * @return
     */
    Matrix<T> operator/(const T scalar)
    {
        for(size_t r = 0; r < m_mat.size(); ++r)
            std::transform(m_mat[r].begin(), m_mat[r].end(), m_mat[r].begin(), [scalar](T &e){ return e/scalar; });
        return Matrix<T>(m_rows, m_cols, &m_mat);
    }

    /**
     * @brief operator *
     * @param scalar
     * @return
     */
    Matrix<T> operator*(const T scalar)
    {
        for(size_t r = 0; r < m_mat.size(); ++r)
            std::transform(m_mat[r].begin(), m_mat[r].end(), m_mat[r].begin(), [scalar](T &e){ return e*scalar; });
        return Matrix<T>(m_rows, m_cols, &m_mat);
    }

    /**
     * @brief operator ==
     * @param other
     * @return
     */
    bool operator==(const Matrix<T>& other) const
    {
        if(this->m_cols == other.m_cols && this->m_rows == other.m_rows)
        {
            const double eps{0.00001};
            Matrix<T> diff(m_rows, m_cols);
            for(size_t r = 0; r < m_mat.size(); ++r)
            {
                std::transform(m_mat[r].begin(), m_mat[r].end(), other.m_mat[r].begin(), diff.m_mat[r].begin(), std::minus<T>());
                bool ok = std::all_of(diff.m_mat[r].begin(), diff.m_mat[r].end(), [eps](T e) { return e < eps; });
                if(!ok)
                    return false;
            }
            return true;
        }
        else
            throw("Sizes of two matrices are mismatched");
    }

    /**
     * @brief operator <<
     * @param os
     * @param m
     * @return
     */
    friend std::ostream& operator<<(std::ostream& os, Matrix<T>& m)
    {
        for(int i = 0; i < m.m_rows; ++i)
        {
            for(int j = 0; j < m.m_cols; ++j)
                os << m(i, j) << " ";
            os << std::endl;
        }
        return os;
    }

    /**
     * @brief mul
     * @param mat
     * @return
     */
    Matrix<T> mul(const Matrix<T>& mat)
    {
        if(m_cols == mat.m_rows)
        {
            Matrix<T> res{m_rows, mat.m_cols};

            for(size_t r = 0; r < m_rows; ++r)
                for(size_t c = 0; c < mat.m_cols; ++c)
                    for(size_t i = 0; i < mat.m_rows; ++i)
                        res(r, c) += m_mat[r][i] * mat.m_mat[i][c];
            return res;
        }
        else
            throw("Matrix dimesnions misalignment was detected. m1.cols != m2.rows!");
    }

    /**
     * @brief mul
     * @param vec
     * @return
     */
    Matrix<T> mul(const Vector<T>& vec)
    {
        std::vector<std::vector<T>> vec_d;
        vec_d.reserve(1);
        vec_d.push_back(vec.data());
        Matrix<T> v_col{static_cast<int>(vec.size()), 1, &vec_d};
        return mul(v_col);
    }

    /**
     * @brief I
     */
    void I()
    {
        for(size_t r=0; r < m_rows; ++r)
            m_mat[r][r] = 1;
    }

    /**
     * @brief tr
     * @return
     */
    Matrix<T> tr()
    {
        std::vector<std::vector<T>> tmp;
        tmp.resize(m_cols);

        for(int r = 0; r < m_cols; ++r)
        {
            tmp[r].resize(m_rows);
            for(int c=0; c < m_rows; ++c)
                tmp[r][c] = m_mat[c][r];
        }
        return Matrix<T>{m_cols, m_rows, &tmp};
    }

    /**
     * @brief inv
     * @return
     */
    Matrix<T> inv()
    {

    }

    /**
     * @brief det
     * @return
     */
    Matrix<T> det()
    {

    }

    /**
     * @brief compute_minor
     * @return
     */
    Matrix<T> compute_minor()
    {

    }

    /**
     * @brief compute_cofactor
     * @return
     */
    Matrix<T> compute_cofactor()
    {

    }

    /**
     * @brief block
     * @param width
     * @param height
     * @param row
     * @param col
     * @return
     */
    Matrix<T> block(const int width, const int height, const int row, const int col)
    {
        Matrix<T> tmp{width, height};

        size_t i = 0;
        for(size_t r = row; r < m_rows; ++r)
            std::transform(m_mat[r].begin()+col, m_mat[r].end(), tmp.m_mat[i].begin(), [](T e){ return e; });

        return tmp;
    }

    /**
     * @brief data
     * @return
     */
    std::vector<std::vector<T>> data() const { return m_mat; }

    ~Matrix() = default;
};

} // namespace ray_tracer


#endif // MATRIX_HPP
