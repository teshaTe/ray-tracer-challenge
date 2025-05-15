#ifndef DATATYPES_HPP
#define DATATYPES_HPP


#include <string>

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

} // namespace ray_tracer::types

#endif // DATATYPES_HPP
