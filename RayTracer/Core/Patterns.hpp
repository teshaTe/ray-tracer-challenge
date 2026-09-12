#ifndef PATTERNS_H
#define PATTERNS_H

#include "Containers/Color.hpp"
#include "Containers/Vector.hpp"
#include "Containers/Matrix.hpp"

namespace ray_tracer{

struct BasePattern
{
    Color<float> color1;
    Color<float> color2;
    Matrix<float> pattern_tr{4, 4};

    BasePattern(const Color<float>& c1, const Color<float>& c2): color1(c1), color2(c2) { pattern_tr.I(); }
    virtual Color<float> pattern_at(const Vector<float> &point) = 0;
    Color<float> pattern_at_object(Matrix<float> &shape_tr, const Vector<float> &point)
    {
        Vector<float> obj_point = shape_tr.inv().mul(point).to_vec_1x4();
        Vector<float> pattern_point = pattern_tr.inv().mul(obj_point).to_vec_1x3();
        return pattern_at(pattern_point);
    }

    void set_pattern_transform(const Matrix<float> &transform)
    {
        pattern_tr = transform;
    }

    virtual ~BasePattern() = default;
};


struct StripePattern: BasePattern
{
    using BasePattern::BasePattern;

    Color<float> pattern_at(const Vector<float> &point)
    {
        int n = static_cast<int>(std::floor(point[0]));
        if(n % 2 == 0)
            return color1;
        else
            return color2;
    }
};

} // namespace raytracer
#endif // PATTERNS_H
