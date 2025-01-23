#include "Containers/Vector.hpp"
#include "Containers/Color.hpp"
#include "RayTracer/Core/Canvas.hpp"
#include "RayTracer/Core/Ray.hpp"
#include "RayTracer/Core/Material.hpp"
#include "RayTracer/Core/RayTracer.h"
#include "RayTracer/Lights/point_light.h"
#include "RayTracer/Shapes/sphere.h"


using namespace ray_tracer;


int main(int argc, char *argv[])
{
    shapes::Sphere sphere{Vector<float>{0, 0, 0}, 1.0, 0};
    materials::BaseMaterial mat;
    mat.color = Color<float>{1., 0.2, 1.};
    mat.ambient = 0.1;
    mat.diffuse = 0.9;
    mat.snininess = 200.0;
    mat.specular = 0.9;
    sphere.set_material(mat);

    lights::PointLight plight{Vector<float>{-10, 10, -10}, Color<float>{1, 1, 1}};
    RayTracer ray_tracer;

    Vector<float> rays_origin{0, 0, -5};

    int canvas_size = 512;

    Canvas<int> image{canvas_size, canvas_size};

    float wall_size = 7.0;
    float pixel_size = wall_size / canvas_size;
    float half_size = wall_size / 2.0;
    float wall_z_coord = 10.0;

    for(int y=0; y < canvas_size; y++)
    {
        float world_y_coord = half_size - pixel_size * y;
        for(int x = 0; x < canvas_size; x++)
        {
            float world_x_coord = -half_size + pixel_size * x;
            Vector<float> wall_position{world_x_coord, world_y_coord, wall_z_coord};
            Vector<float> ray_dirs = (wall_position - rays_origin).normalize();
            Ray ray{rays_origin, ray_dirs};

            std::vector<types::intersection> intersections = sphere.intersect(ray);

            if(intersections.size() > 0)
            {
                Vector<float> point = ray.position(ray, intersections[0].t);
                Vector<float> normal = sphere.get_normal(point);
                Vector<float> eye = ray.get_direction().negate();
                materials::BaseMaterial sp_mat = sphere.get_assigned_material();
                Color<float> color = ray_tracer.compute_lightning(sp_mat, plight, point, eye, normal);

                image.set_pixel(x, y, color.to_int_rgb());
            }
        }
    }

    std::string file_name = "sphere_image";
    std::string path = "/home/tesha/Documents/C++/ray-tracer-challenge/Build";

    image.save_to_ppm(file_name, path);
    return 0;
}
