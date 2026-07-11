#ifndef PATTERNS_H
#define PATTERNS_H

#include "Containers/Color.hpp"
#include "Containers/Vector.hpp"


namespace ray_tracer{

struct BasePattern
{
    Color<float> color1;
    Color<float> color2;
    BasePattern(const Color<float>& c1, const Color<float>& c2): color1(c1), color2(c2) {}
    virtual Color<float> pattern_at(const Vector<float> &point) = 0;
    virtual ~BasePattern() = default;
};


struct StripePattern: BasePattern
{
    using BasePattern::BasePattern;

    Color<float> pattern_at(const Vector<float> &point)
    {
        int n = std::floor(point[0]);
        if(n % 2 == 0 )
            return color1;
        else
            return color2;
    }
};

} // namespace raytracer
#endif // PATTERNS_H
