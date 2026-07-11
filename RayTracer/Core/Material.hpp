            #ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Containers/Color.hpp"
#include "Core/Patterns.hpp"


namespace ray_tracer::materials {

/**
 * @brief The Material class
 */
struct BaseMaterial
{
    Color<float> color{1, 1, 1};
    BasePattern *pattern = nullptr;
    float ambient = 0.1;
    float diffuse = 0.9;
    float specular = 0.9;
    float shininess = 200.0;

    bool operator==(const BaseMaterial &other) const
    {
        return other.color == color && other.ambient == ambient &&
               other.diffuse == diffuse && other.specular == specular &&
               other.shininess == shininess;
    }
};

} //namespace ray_tracer::materials

#endif // MATERIAL_HPP
