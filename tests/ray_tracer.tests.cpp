#include "math.h"

#include <gtest/gtest.h>

#include "Containers/Vector.hpp"
#include "Core/Material.hpp"
#include "Core/RayTracer.h"
#include "Core/WorldScene.h"
#include "Core/Camera.h"
#include "Core/Canvas.hpp"
#include "Lights/point_light.h"
#include "Shapes/Sphere.h"


using namespace ray_tracer;

TEST(RayTracerShadingTest, TestingShading)
{
    materials::BaseMaterial mat1;
    mat1.color = Color<float>{1, 1, 1};
    mat1.ambient = 0.1;
    mat1.diffuse = 0.9;
    mat1.specular = 0.9;
    mat1.shininess = 200.0;

    Vector<float> position1{0, 0, 0};
    Vector<float> eye_dir1{0, 0, -1};
    Vector<float> normal1{0, 0, -1};

    lights::PointLight plight1{Vector<float>{0, 0, -10}, Color<float>{1, 1, 1}, 0};
    RayTracer ray_tracer;

    Color<float> resutl1 = ray_tracer.compute_lightning(mat1, plight1, position1, eye_dir1, normal1, false);
    Color<float> ref1{1.9, 1.9, 1.9};
    ASSERT_EQ(ref1, resutl1);

    float val = std::sqrt(2)/2.0;
    Vector<float> eye_dir2{0, val, val};
    Color<float> resutl2 = ray_tracer.compute_lightning(mat1, plight1, position1, eye_dir2, normal1, false);
    Color<float> ref2{1.0, 1.0, 1.0};
    ASSERT_EQ(ref2, resutl2);

    lights::PointLight plight2{Vector<float>{0, 10, -10}, Color<float>{1, 1, 1}, 1};
    Color<float> resutl3 = ray_tracer.compute_lightning(mat1, plight2, position1, eye_dir1, normal1, false);
    Color<float> ref3{0.7364, 0.7364, 0.7364};
    ASSERT_EQ(ref3, resutl3);

    Vector<float> eye_dir3{0, -val, -val};
    Color<float> resutl4 = ray_tracer.compute_lightning(mat1, plight2, position1, eye_dir3, normal1, false);
    Color<float> ref4{1.6364, 1.6364, 1.6364};
    ASSERT_EQ(ref3, resutl3);

    lights::PointLight plight3{Vector<float>{0, 0, 10}, Color<float>{1, 1, 1}, 2};
    Color<float> resutl5 = ray_tracer.compute_lightning(mat1, plight3, position1, eye_dir1, normal1, false);
    Color<float> ref5{0.1, 0.1, 0.1};
    ASSERT_EQ(ref3, resutl3);
}


TEST(RayTracerWorldSceneShadingTest, TestingWorldSceneShading)
{
    WorldScene world_scene{};
    world_scene.create_default_world();
    Ray ray{Vector<float>{0, 0, -5}, Vector<float>{0, 0, 1}};

    auto &shapes = world_scene.get_shapes();
    auto &lights = world_scene.get_lights();

    types::intersection intersection{
        shapes[0].get()->get_type(),
        shapes[0].get()->get_id(),
        4
    };

    RayTracer ray_tracer{};
    types::intersection_state intersection_state = world_scene.precompute_intersection_state(*shapes[0],
                                                                                              intersection,
                                                                                              ray);
    Color<float> shading_color1 = ray_tracer.compute_shading(shapes[0]->clone(), lights, intersection_state, world_scene);
    Color<float> ref_color1{0.38066, 0.47583, 0.2855};

    ASSERT_NEAR(shading_color1[0], ref_color1[0], 1e-4);
    ASSERT_NEAR(shading_color1[1], ref_color1[1], 1e-4);
    ASSERT_NEAR(shading_color1[2], ref_color1[2], 1e-4);
}


TEST(RayTracerWorldSceneShadingInsideTest, TestingWorldSceneShadingInside)
{
    WorldScene world_scene{};
    world_scene.create_default_world();

    RayTracer ray_tracer{};

    Ray ray{Vector<float>{0, 0, 0}, Vector<float>{0, 0, 1}};
    lights::PointLight plight{Vector<float>{0, 0.25, 0}, Color<float>{1, 1, 1}, 0};

    world_scene.delete_light(0, "point_light");
    world_scene.add_light(plight);

    auto &shapes = world_scene.get_shapes();
    auto &lights = world_scene.get_lights();

    types::intersection intersection{
        shapes[1].get()->get_type(),
        shapes[1].get()->get_id(),
        0.5
    };

    types::intersection_state intersection_state = world_scene.precompute_intersection_state(*shapes[1],
                                                                                             intersection,
                                                                                             ray);
    Color<float> shading_color = ray_tracer.compute_shading(shapes[1]->clone(), lights, intersection_state, world_scene);
    Color<float> ref_color{0.904661, 0.904661, 0.904661};

    ASSERT_NEAR(shading_color[0], ref_color[0], 1e-4);
    ASSERT_NEAR(shading_color[1], ref_color[1], 1e-4);
    ASSERT_NEAR(shading_color[2], ref_color[2], 1e-4);
}

TEST(RayTracerWorldSceneRenderingEdgeCasesTest, TestingWorldSceneRenderingEdgeCases)
{
    // test no object got intersected
    WorldScene world_scene1{};
    world_scene1.create_default_world();

    Ray ray1{Vector<float>{0, 0, -5}, Vector<float>{0, 1, 0}};
    RayTracer ray_tracer{};
    Color<float> shading_color1 = ray_tracer.get_color_at(world_scene1, ray1);
    Color<float> ref_color1{0.0, 0.0, 0.0};
    ASSERT_EQ(shading_color1, ref_color1);

    // test only exterior object got as hit
    Ray ray2{Vector<float>{0, 0, -5}, Vector<float>{0, 0, 1}};
    Color<float> shading_color2 = ray_tracer.get_color_at(world_scene1, ray2);

    Color<float> ref_color2{0.38066, 0.47583, 0.2855};
    ASSERT_NEAR(shading_color2[0], ref_color2[0], 1e-4);
    ASSERT_NEAR(shading_color2[1], ref_color2[1], 1e-4);
    ASSERT_NEAR(shading_color2[2], ref_color2[2], 1e-4);

    //  test only interior object got a hit
    WorldScene world_scene2{};
    materials::BaseMaterial mat1;
    mat1.ambient = 1.0;

    shapes::Sphere sp1{1.0, 0};
    sp1.set_material(mat1);

    shapes::Sphere sp2{0.5, 1};
    materials::BaseMaterial mat2;
    mat2.ambient = 1.0;
    sp2.set_material(mat2);

    world_scene2.add_shape(sp1);
    world_scene2.add_shape(sp2);

    lights::PointLight plight1{Vector<float>{-10, 10, -10}, Color<float>{1, 1, 1}, 0};
    world_scene2.add_light(plight1);

    Ray ray3{Vector<float>{0, 0, 0.75}, Vector<float>{0, 0, -1}};
    Color<float> shading_color3 = ray_tracer.get_color_at(world_scene2, ray3);

    Color<float> ref_color3{1, 1, 1};
    ASSERT_EQ(shading_color3, ref_color3);
}

TEST(RenderingWorldWithCameraTest, TestingWorldRenderingWithCamera)
{
    WorldScene world_scene{};
    world_scene.create_default_world();

    Camera camera{11, 11, 90};
    Vector<float> from{0, 0, -5};
    Vector<float> to{0, 0, 0};
    Vector<float> up{0, 1, 0};
    camera.compute_view_transform(from, to, up);

    RayTracer ray_tracer{};
    Canvas canvas = ray_tracer.render(camera, world_scene);
    Color<float> ref_pixel{0.38066, 0.47583, 0.2855};

    ASSERT_EQ(canvas.get_pixel(5, 5), ref_pixel.to_int_rgb());
}

TEST(RayTracerWithShadows, TestingRayTracerWithShadows)
{
    materials::BaseMaterial mat1;
    mat1.color = Color<float>{1, 1, 1};
    mat1.ambient = 0.1;
    mat1.diffuse = 0.9;
    mat1.specular = 0.9;
    mat1.shininess = 200.0;

    Vector<float> position1{0, 0, 0};
    Vector<float> eye_dir{0, 0, -1};
    Vector<float> normal{0, 0, -1};
    lights::PointLight plight{Vector<float>{0, 0, -10}, Color<float>{1, 1, 1}, 0};
    RayTracer ray_tracer;

    Color<float> result_color = ray_tracer.compute_lightning(mat1, plight, position1, eye_dir, normal, true);
    Color<float> ref_color{0.1, 0.1, 0.1};

    ASSERT_EQ(result_color, ref_color);

    WorldScene world_scene{};
    world_scene.create_default_world();
    auto &shapes = world_scene.get_shapes();
    auto &lights = world_scene.get_lights();

    // case 1: nothing lies between point and light
    Vector<float> position2{0, 10, 0};
    bool is_shadowed1 = ray_tracer.is_shadowed(*lights[0], world_scene, position2);
    ASSERT_EQ(is_shadowed1, false);

    // case 2: point is behind the sphere; sphere between light and point;
    Vector<float> position3{10, -10, 10};
    bool is_shadowed2 = ray_tracer.is_shadowed(*lights[0], world_scene, position3);
    ASSERT_EQ(is_shadowed2, true);

    // case 3: point is behind the light
    Vector<float> position4{-20, 20, -20};
    bool is_shadowed3 = ray_tracer.is_shadowed(*lights[0], world_scene, position4);
    ASSERT_EQ(is_shadowed3, false);

    // case 3: point is between light and sphere
    Vector<float> position5{-2, 2, -2};
    bool is_shadowed4 = ray_tracer.is_shadowed(*lights[0], world_scene, position5);
    ASSERT_EQ(is_shadowed4, false);
}

TEST(RayTracerWithshadowsFinal, TestingRayTracerWithshadowsFinal)
{
    lights::PointLight plight1{Vector<float>{0, 0, -10}, Color<float>{1, 1, 1}, 0};

    materials::BaseMaterial mat1;
    mat1.color = Color<float>{1, 1, 1};
    mat1.ambient = 0.1;
    mat1.diffuse = 0.9;
    mat1.specular = 0.9;
    mat1.shininess = 200.0;

    shapes::Sphere sp1{1.0, 0};
    sp1.set_material(mat1);

    MatrixUtlities mat_utils{};

    shapes::Sphere sp2{1.0, 0};
    Matrix<float> sphere2_tr = mat_utils.translation_mat(0.0, 0.0, 10.0);
    sp2.transform(sphere2_tr);

    WorldScene world_scene{};
    world_scene.add_shape(sp1);
    world_scene.add_shape(sp2);
    world_scene.add_light(plight1);

    RayTracer ray_tracer;
    Ray ray1{Vector<float>{0, 0, 5}, Vector<float>{0, 0, 1}};

    types::intersection found_intersection;
    found_intersection.obj_type = sp2.get_type();
    found_intersection.obj_id = sp2.get_id();
    found_intersection.t = 4;

    types::intersection_state intersection_state = world_scene.precompute_intersection_state(
        sp2,
        found_intersection,
        ray1);

    Color<float> color = ray_tracer.compute_shading(sp2.clone(), world_scene.get_lights(), intersection_state, world_scene);
    Color<float> color_ref{0.1, 0.1, 0.1};
    ASSERT_EQ(color, color_ref);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
