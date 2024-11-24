#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Containers/Color.hpp"


namespace ray_tracer::materials {

/**
 * @brief The Material class
 */
struct BaseMaterial
{
    Color<float> color{0, 1, 0};
    float ambient = 0;
    float diffuse = 0;
    float specular = 0;
    float snininess = 0;

    bool operator==(const BaseMaterial &other) const
    {
        if(color == other.color)
        {
            if(ambient == other.ambient)
            {
                if(diffuse == other.diffuse)
                {
                    if (specular == other.specular)
                    {
                        if(snininess==other.snininess)
                        {
                            return true;
                        } else {
                            return false;
                        }
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
};

} //namespace ray_tracer::materials

#endif // MATERIAL_HPP
