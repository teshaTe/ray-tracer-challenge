#include "RayTracer.h"
#include "Containers/Color.hpp"


namespace ray_tracer {

Color<float> RayTracer::compute_lightning(materials::BaseMaterial &material,
                                          lights::Light &light,
                                          Vector<float> &point,
                                          Vector<float> &eye_dir,
                                          Vector<float> &normal)
{
    // combine the surface color with the light's color/intensity
    Color<float> effective_color = material.color.hadamard_product(light.get_intensity());

    // find the direction to the ligth source
    Vector<float> light_dir = (light.get_origin() - point).normalize();

    // compute the ambient contribution
    Color<float> ambient = effective_color * material.ambient;

    // light_dot_normal - the cosine of the angle between the light vector and the normal vector;
    // a negative number -> light on the other side of the surface
    float light_dot_normal = light_dir.dot(normal);

    Color<float> black{0, 0, 0};
    Color<float> diffuse{0, 0, 0};
    Color<float> specular{0, 0, 0};

    if(light_dot_normal < 0.0)
    {
        diffuse = black;
        specular = black;
    } else {
        // compute the diffuse contribution
        diffuse = effective_color * material.diffuse * light_dot_normal;

        // reflect_dot_eye - the cosine of the angle between the reflection vector and eye_dir vector;
        // a negative number -> light reflects away from the eye
        Vector<float> reflect_dir = light_dir.negate().reflect(normal);
        float reflect_dot_eye = reflect_dir.dot(eye_dir);

        if(reflect_dot_eye <= 0)
        {
            specular = black;
        } else {
            // compute the specular contribution
            float factor = std::pow(reflect_dot_eye, material.shininess);
            specular = light.get_intensity() * material.specular * factor;
        }
    }

    return ambient + diffuse + specular;
}

Color<float> RayTracer::compute_shading(WorldScene &world_scene, types::intersection_state &intersection_state)
{
    const auto& shapes = world_scene.get_shapes();
    const auto& lights = world_scene.get_lights();

    std::unique_ptr<shapes::Shape> cur_shape;
    for(int i=0; i < shapes.size(); i++)
    {
        if(shapes[i]->get_id() == intersection_state.obj_id && shapes[i]->get_type() == intersection_state.obj_type)
        {
            cur_shape = shapes[i]->clone();
            break;
        }
    }

    Color<float> final_color{0, 0, 0};
    for(int j=0; j < lights.size(); j++)
    {
        materials::BaseMaterial material = cur_shape.get()->get_assigned_material();
        Color<float> color = compute_lightning(material,
                                               *lights[j],
                                               intersection_state.point,
                                               intersection_state.eye_dir,
                                               intersection_state.normal);
        final_color = final_color + color;
    }

    return final_color;

}


} // namespace ray_tracer
