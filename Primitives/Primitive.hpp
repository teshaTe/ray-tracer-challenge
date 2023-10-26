#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include <RayTracer/Ray.hpp>
#include <string>
#include <vector>


namespace ray_tracer::prims {

/**
 * @brief The PrimitiveObj class
 */
class PrimitiveObj
{
public:
    PrimitiveObj(const PrimitiveObj&) = delete;
    PrimitiveObj(const PrimitiveObj&&) = delete;
    PrimitiveObj& operator=(const PrimitiveObj&) = delete;

    virtual int get_id() const = 0;
    virtual Vector<float> get_origin() const = 0;
    virtual std::vector<int> intersect(const Ray &ray) const = 0;
    //    virtual void transform(Vector<float> transform) = 0;

    virtual ~PrimitiveObj() = default;

protected:
    PrimitiveObj() = default;
    std::string m_type;
};

} // namespace ray_tracer::prims


#endif // PRIMITIVE_HPP
