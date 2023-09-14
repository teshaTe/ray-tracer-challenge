#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <algorithm>

namespace ray_tracer {

template<class T>
class Matrix
{
private:
    std::vector<std::vector<T>> m_mat;
    int m_rows;
    int m_cols;

    typedef typename std::vector<std::vector<T>>::iterator iterator;
    typedef typename std::vector<std::vector<T>>::const_iterator const_iterator;

public:
    Matrix(const int rows, const int cols, const std::vector<std::vector<T>> *data = nullptr): m_rows{rows}, m_cols{cols}
    {
        m_mat.resize(rows);
        for(auto &c : m_mat)
        {
            c.resize(cols);
            std::fill(c.begin(), c.end(), 0);
        }

        if(data != nullptr)
            if(data->size() == rows && data[0].size() == cols)
                m_mat = *data;
    }

    Matrix(const Matrix<T>& other) { this->m_mat = other.m_mat; }

    T& operator()(int i, int j) { return m_mat[i][j]; }

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
    Matrix<T> operator/(const T scalar)
    {
        for(size_t r = 0; r < m_mat.size(); ++r)
            std::transform(m_mat[r].begin(), m_mat[r].end(), m_mat[r].begin(), [scalar](T &e){ return e/scalar; });
        return Matrix<T>(m_rows, m_cols, &m_mat);
    }

    Matrix<T> operator*(const T scalar)
    {
        for(size_t r = 0; r < m_mat.size(); ++r)
            std::transform(m_mat[r].begin(), m_mat[r].end(), m_mat[r].begin(), [scalar](T &e){ return e*scalar; });
        return Matrix<T>(m_rows, m_cols, &m_mat);
    }

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

    iterator begin() { return m_mat.begin(); }
    const_iterator begin() const { return m_mat.begin(); }

    iterator end() { return m_mat.end(); }
    const_iterator end() const { return m_mat.end(); }

    void I()
    {
        for(size_t r=0; r < m_rows; ++r)
            m_mat[r][r] = 1;
    }
    Matrix<T> tr()
    {

    }
    Matrix<T> inv()
    {

    }
    Matrix<T> det()
    {

    }
    Matrix<T> compute_minor()
    {

    }
    Matrix<T> compute_cofactor()
    {

    }
    Matrix<T> block(const int width, const int height, const int row, const int col)
    {
        Matrix<T> tmp{width, height};

        size_t i = 0;
        for(size_t r = row; r < m_rows; ++r)
            std::transform(m_mat[r].begin()+col, m_mat[r].end(), tmp.m_mat[i].begin(), [](T e){ return e; });

        return tmp;
    }

    Matrix<T> mul(const Matrix<T> mat)
    {

    }

    ~Matrix() = default;
};

} // namespace ray_tracer


#endif // MATRIX_HPP
