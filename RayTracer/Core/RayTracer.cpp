#include "RayTracer.h"
#include "Containers/Color.hpp"


namespace ray_tracer {

std::unique_ptr<shapes::Shape> RayTracer::get_shape_by_id(const std::vector<std::unique_ptr<shapes::Shape> > shapes, const int shape_id, const std::string &shape_type)
{
    std::unique_ptr<shapes::Shape> cur_shape;
    for(int i=0; i < shapes.size(); i++)
    {
        if(shapes[i]->get_id() == shape_id && shapes[i]->get_type() == shape_type)
        {
            cur_shape = shapes[i]->clone();
            break;
        }
    }
    return cur_shape;
}

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

Color<float> RayTracer::compute_shading(std::unique_ptr<shapes::Shape> shape,
                                        std::vector<std::unique_ptr<lights::Light>> &lights,
                                        types::intersection_state &intersection_state)
{
    Color<float> final_color{0, 0, 0};
    for(int j=0; j < lights.size(); j++)
    {
        materials::BaseMaterial material = shape.get()->get_assigned_material();
        Color<float> color = compute_lightning(material,
                                               *lights[j],
                                               intersection_state.point,
                                               intersection_state.eye_dir,
                                               intersection_state.normal);
        final_color = final_color + color;
    }

    return final_color;
}

Color<float> RayTracer::get_color_at(WorldScene &world_scene, Ray &ray)
{
    auto &shapes = world_scene.get_shapes();
    auto &lights = world_scene.get_lights();
    float closest_hit = std::numeric_limits<float>::max();
    int closest_index = -1;
    for(int i = 0; i < shapes.size(); i++)
    {
        std::vector<types::intersection> intersections = shapes[i]->intersect(ray);
        float hit = 0;
        if(shapes[i]->get_surface_hit(intersections, &hit) && hit < closest_hit)
        {
            closest_hit = hit;
            closest_index = i;
        }
    }
    Color<float> shaded_pixel{0, 0, 0};
    if(closest_index >= 0)
    {
        types::intersection found_intersection;
        found_intersection.obj_type = shapes[closest_index]->get_type();
        found_intersection.obj_id = shapes[closest_index]->get_id();
        found_intersection.t = closest_hit;
        types::intersection_state intersection_state = world_scene.precompute_intersection_state(
            *shapes[closest_index],
            found_intersection,
            ray);
        shaded_pixel = compute_shading(shapes[closest_index]->clone(), lights, intersection_state);
    }
    return shaded_pixel;
}

Canvas<int> RayTracer::render(Camera &camera, WorldScene &world_scene)
{
    Canvas<int> canvas{camera.get_horizontal_size(), camera.get_vertical_size()};

    if(world_scene.contains_shapes())
    {
        #pragma omp parallel for
        for(int y=0; y < camera.get_vertical_size(); y++)
            #pragma omp parallel for
            for(int x=0; x < camera.get_horizontal_size(); x++)
            {
                Ray ray = canvas.shoot_ray_for_pixel(&camera, x, y);
                Color<float> color = get_color_at(world_scene, ray);
                canvas.set_pixel(x, y, color.to_int_rgb());
            }
    }
    return canvas;
}


} // namespace ray_tracer
