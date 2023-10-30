#include "shape.h"

namespace ray_tracer::shapes {

bool Shape::get_surface_hit(const std::vector<types::intersection> &intersections, float *res)
{
    std::vector<float> t_vals(intersections.size());
    std::transform(intersections.begin(), intersections.end(), t_vals.begin(), [](auto &e){ return e.t; });
    std::sort(t_vals.begin(), t_vals.end());

    for(auto &v : t_vals)
    {
        if(v >= 0)
        {
            *res = v;
            return true;
        }
    }

    *res = -1.0f;
    return false;
}

} // namespace ray_tracer::shapes
