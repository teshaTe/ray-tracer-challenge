#include "Containers/Vector.hpp"
#include "RayTracer/Core/Canvas.hpp"
#include "RayTracer/Shapes/sphere.h"
#include "RayTracer/Core/Ray.hpp"


using namespace ray_tracer;


int main(int argc, char *argv[])
{
    shapes::Sphere sphere{Vector<float>{0, 0, 0}, 1.0, 0};
    Vector<float> rays_origin{0, 0, -5};

    int canvas_size = 512;

    Canvas<int> image{canvas_size, canvas_size};
    const Color<int> c{255, 0, 0};

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
                image.set_pixel(x, y, c);
        }
    }

    std::string file_name = "sphere_image";
    std::string path = "/home/tesha/Documents/C++/ray-tracer-challenge/Build/";

    image.save_to_ppm(file_name, path);
    return 0;
}
