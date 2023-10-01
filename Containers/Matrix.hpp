#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <algorithm>
#include <iostream>
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
    Matrix(const int rows, const int cols): m_rows{rows}, m_cols{cols}
    {
        m_mat.resize(rows);
        for(auto &c : m_mat)
        {
            c.resize(cols);
            std::fill(c.begin(), c.end(), m_zero);
        }
    }

    Matrix(const int rows, const int cols, const std::vector<std::vector<T>>& data): m_rows{rows}, m_cols{cols}
    {

        if(data.size() == rows && std::all_of(data.begin(), data.end(), [cols](std::vector<T> e) { return e.size() == cols; }))
            m_mat = data;
        else
            throw std::runtime_error("[ERROR] Cannot assign data to the Matrix. Wrong size!");
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
    const T& operator()(int i, int j) const { return m_mat[i][j]; }

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
            return Matrix<T>(m_rows, m_cols, m_mat);
        }
        else
            throw std::runtime_error("Sizes of two matrices are mismatched");
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
            return Matrix<T>(m_rows, m_cols, m_mat);
        }
        else
            throw std::runtime_error("Sizes of two matrices are mismatched");
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
        return Matrix<T>(m_rows, m_cols, m_mat);
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
        return Matrix<T>(m_rows, m_cols, m_mat);
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
            throw std::runtime_error("Sizes of two matrices are mismatched!\n");
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
     * @brief operator <<
     * @param os
     * @param v
     * @return
     */
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& m)
    {
        os << "[ ";
        for(int r=0; r < m.m_rows; ++r)
        {
            os << "[ ";
            for(int c=0; c < m.m_cols; ++c)
                os << m(r, c) << ", ";
            os << " ]" << std::endl;
        }
        os << "]";
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
            throw std::runtime_error("Matrix dimesnions misalignment was detected: m1.cols != m2.rows.");
    }

    /**
     * @brief mul
     * @param vec
     * @return
     */
    Matrix<T> mul(const Vector<T>& vec)
    {
        std::vector<std::vector<T>> vec_d;
        if(m_rows - vec.size() == 1)
        {
            vec_d.resize(vec.size()+1);
            vec_d[vec.size()].push_back(1);
        }
        else if(m_rows == vec.size())
            vec_d.resize(vec.size());
        else
            throw std::runtime_error("Matrix dimesnions misalignment was detected: mat.m_rows != vec.size().");

        for(size_t i = 0; i < vec.size(); ++i)
            vec_d[i].push_back(vec[i]);


        Matrix<T> v_col{static_cast<int>(vec_d.size()), 1, vec_d};
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
        return Matrix<T>{m_cols, m_rows, tmp};
    }

    /**
     * @brief inv
     * @return
     */
    Matrix<T> inv()
    {
        T determinant = det();
        if(determinant != 0)
        {
            Matrix<T> inv_mat(m_rows, m_cols);
            for(int r=0; r < m_rows; ++r)
                for(int c=0; c < m_cols; ++c)
                {
                    T cof = compute_cofactor(r, c) * compute_minor(r, c);
                    inv_mat(c, r) = cof / determinant;
                }
            return inv_mat;
        }
        else
            throw std::runtime_error("Cannot compute invert matrix for the matrix with det=0.");

    }

    /**
     * @brief det
     * @return
     */
    T det()
    {
        T determinant = 0;
        if(m_mat.size() == 2 && std::all_of(m_mat.begin(), m_mat.end(), [](std::vector<T> e) { return e.size() == 2; }))
            determinant =  m_mat[0][0]*m_mat[1][1] - m_mat[0][1]*m_mat[1][0];
        else
        {
            for(int c=0; c < m_cols; ++c)
                determinant += compute_cofactor(0, c) * compute_minor(0, c) * m_mat[0][c];
        }
        return determinant;
    }

    /**
     * @brief compute_minor
     * @return
     */
    T compute_minor(const int del_row, const int del_col)
    {
        if(m_mat.size() > 2 && std::all_of(m_mat.begin(), m_mat.end(), [](std::vector<T> e) { return e.size() > 2; }))
        {
            Matrix<T> submat = submatrix(del_row, del_col);
            T minor = submat.det();
            return minor;
        }
        else
            throw std::runtime_error("[ERROR] Matrix size should be > 2x2! ");

    }

    /**
     * @brief compute_cofactor
     * @return
     */
    T compute_cofactor(const int row, const int col)
    {
        int i = row + col;
        return std::pow(-1, i);
    }

    /**
     * @brief block
     * @param width
     * @param height
     * @param row
     * @param col
     * @return
     */
    Matrix<T> block(const int rows_num, const int cols_num, const int row, const int col)
    {
        assert(row < m_rows && row >= 0);
        assert(col < m_cols && col >= 0);

        Matrix<T> block_mat{rows_num, cols_num};

        size_t i = 0;
        for(size_t r = row; r < m_rows; ++r)
        {
            std::transform(m_mat[r].begin()+col, m_mat[r].begin()+col+cols_num, block_mat.m_mat[i].begin(), [](T e){ return e; });
            i++;
        }

        return block_mat;
    }

    /**
     * @brief submatrix
     * @param del_row
     * @param del_col
     * @return
     */
    Matrix<T> submatrix(const int del_row, const int del_col)
    {
        assert(del_row < m_rows && del_row >= 0);
        assert(del_col < m_cols && del_col >= 0);

        Matrix<T> submat{m_rows-1, m_cols-1};
        size_t sub_r = 0;

        for(size_t r=0; r < m_rows; ++r)
        {
            size_t sub_c = 0;
            if(r == del_row)
                continue;

            for(size_t c=0; c < m_cols; ++c)
            {
                if(c == del_col)
                    continue;
                else
                {
                    submat(sub_r, sub_c) = m_mat[r][c];
                    sub_c++;
                }
            }

            sub_r++;
        }
        return submat;
    }

    /**
     * @brief data
     * @return
     */
    std::vector<std::vector<T>> data() const { return m_mat; }

    /**
     * @brief to_vec_1x2
     * @return
     */
    Vector<T> to_vec_1x2()
    {
        if(m_rows > 1)
            return Vector<T>{m_mat[0][0], m_mat[1][0]};
        else
            return Vector<T>{m_mat[0][0], m_mat[0][1]};
    }

    /**
     * @brief to_vec_1x3
     * @return
     */
    Vector<T> to_vec_1x3()
    {
        if(m_rows > 1)
            return Vector<T>{m_mat[0][0], m_mat[1][0], m_mat[2][0]};
        else
            return Vector<T>{m_mat[0][0], m_mat[0][1], m_mat[0][2]};
    }

    /**
     * @brief to_vec_1x4
     * @return
     */
    Vector<T> to_vec_1x4()
    {
        if(m_rows > 1)
            return Vector<T>{m_mat[0][0], m_mat[1][0], m_mat[2][0], m_mat[3][0]};
        else
            return Vector<T>{m_mat[0][0], m_mat[0][1], m_mat[0][2], m_mat[0][3]};
    }

    ~Matrix() = default;
};

} // namespace ray_tracer


#endif // MATRIX_HPP
