#include "Containers/Vector.hpp"
#include "Containers/Color.hpp"
#include "RayTracer/Core/Canvas.hpp"
#include "RayTracer/Core/Material.hpp"
#include "RayTracer/Core/RayTracer.h"
#include "RayTracer/Core/MatrixUtils.hpp"
#include "RayTracer/Lights/point_light.h"
#include "RayTracer/Shapes/Sphere.h"
#include "RayTracer/Shapes/Plane.h"


using namespace ray_tracer;


int main(int argc, char *argv[])
{
    // creating scene floor
    shapes::Plane floor{0};
    materials::BaseMaterial floor_mat;
    floor_mat.color = Color<float>{1., 0.9, 0.9};
    floor_mat.specular = 0.0;
    floor.set_material(floor_mat);

    // creating left wall
    MatrixUtlities mat_utils{};
    shapes::Plane left_wall{1};
    Matrix<float> left_wall_tr = mat_utils.translation_mat(0, 0, 5).
                                 mul(mat_utils.rotation_mat_YAxis(mat_utils.toRadiance(-45.0))).
                                 mul(mat_utils.rotation_mat_XAxis(mat_utils.toRadiance(90)));

    left_wall.transform(left_wall_tr);
    left_wall.set_material(floor_mat);

    // creating right wall
    shapes::Plane right_wall{2};
    Matrix<float> right_wall_tr = mat_utils.translation_mat(0, 0, 5).
                                  mul(mat_utils.rotation_mat_YAxis(mat_utils.toRadiance(45.0))).
                                  mul(mat_utils.rotation_mat_XAxis(mat_utils.toRadiance(90)));

    right_wall.transform(right_wall_tr);
    right_wall.set_material(floor_mat);

    // creating 1st sphere
    shapes::Sphere sphere1{1.0, 3};
    Matrix<float> sphere1_tr = mat_utils.translation_mat(-0.5, 1.0, 0.5);
    sphere1.transform(sphere1_tr);

    materials::BaseMaterial sphere1_mat;
    sphere1_mat.color = Color<float>{0.1, 1, 0.5};
    sphere1_mat.diffuse = 0.7;
    sphere1_mat.specular = 0.3;
    sphere1.set_material(sphere1_mat);

    // creating right sphere
    shapes::Sphere sphere2{1.0, 4};
    Matrix<float> sphere2_tr = mat_utils.translation_mat(1.5, 0.5, -0.5).
                               mul(mat_utils.scaling_mat(0.5, 0.5, 0.5));
    sphere2.transform(sphere2_tr);

    materials::BaseMaterial sphere2_mat;
    sphere2_mat.color = Color<float>{0.5, 1, 0.1};
    sphere2_mat.diffuse = 0.7;
    sphere2_mat.specular = 0.3;
    sphere2.set_material(sphere2_mat);

    // creating left sphere
    shapes::Sphere sphere3{1.0, 5};
    Matrix<float> sphere3_tr = mat_utils.translation_mat(-1.5, 0.33, -0.75).
                               mul(mat_utils.scaling_mat(0.33, 0.33, 0.33));
    sphere3.transform(sphere3_tr);

    materials::BaseMaterial sphere3_mat;
    sphere3_mat.color = Color<float>{1.0, 0.8, 0.1};
    sphere3_mat.diffuse = 0.7;
    sphere3_mat.specular = 0.3;
    sphere3.set_material(sphere3_mat);

    // creating light in the scene
    lights::PointLight plight{Vector<float>{-10, 10, -10}, Color<float>{1, 1, 1}, 0};

    // creating camera
    Camera camera{1024, 800, 60};
    camera.compute_view_transform(Vector<float>{0, 1.5, -5}, Vector<float>{0, 1, 0}, Vector<float>{0, 1, 0});

    // creting scene and adding objects to it
    WorldScene scene{};
    scene.add_shape(floor);
    scene.add_shape(left_wall);
    scene.add_shape(right_wall);
    scene.add_shape(sphere1);
    scene.add_shape(sphere2);
    scene.add_shape(sphere3);
    scene.add_light(plight);

    RayTracer ray_tracer{};
    Canvas image = ray_tracer.render(camera, scene);

    std::string file_name = "spheres_image";
    std::string path = "../";

    image.save_to_ppm(file_name, path);
    return 0;
}
