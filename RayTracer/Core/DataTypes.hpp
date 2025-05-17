#ifndef DATATYPES_HPP
#define DATATYPES_HPP


#include <string>
#include "Containers/Vector.hpp"


namespace ray_tracer::types {

struct intersection
{
    std::string obj_type;
    float t;

    bool operator<(const intersection& obj) const
    {
        return t < obj.t;
    }
};


struct intersection_state
{
    std::string obj_type;
    Vector<float> point;
    Vector<float> eye_dir;
    Vector<float> normal;
    float t;
};

} // namespace ray_tracer::types

#endif // DATATYPES_HPP
