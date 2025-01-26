#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <memory>

#include "Containers/Vector.hpp"
#include "Containers/Color.hpp"
#include "MatrixUtils.hpp"


namespace ray_tracer::lights {

class Light
{
public:
    virtual ~Light() = default;

    virtual Vector<float> get_origin() const = 0;
    virtual Color<float> get_intensity() const = 0;
    virtual int get_id() const = 0;
    virtual std::string get_type() const = 0;

    virtual void set_origin(const Vector<float> &origin) = 0;
    virtual void set_intensity(const Color<float> &intensity) = 0;

    virtual std::unique_ptr<Light> clone() const = 0; // Clone function

};

} //namespace ray_tracer

#endif // LIGHT_HPP
