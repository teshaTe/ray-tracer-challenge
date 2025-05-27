#include "math.h"

#include <gtest/gtest.h>

#include "Containers/Vector.hpp"
#include "Core/Material.hpp"
#include "Core/RayTracer.h"
#include "Core/worldscene.h"
#include "Lights/point_light.h"
#include "Shapes/sphere.h"


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

    Color<float> resutl1 = ray_tracer.compute_lightning(mat1, plight1, position1, eye_dir1, normal1);
    Color<float> ref1{1.9, 1.9, 1.9};
    ASSERT_EQ(ref1, resutl1);

    float val = std::sqrt(2)/2.0;
    Vector<float> eye_dir2{0, val, val};    
    Color<float> resutl2 = ray_tracer.compute_lightning(mat1, plight1, position1, eye_dir2, normal1);
    Color<float> ref2{1.0, 1.0, 1.0};
    ASSERT_EQ(ref2, resutl2);

    lights::PointLight plight2{Vector<float>{0, 10, -10}, Color<float>{1, 1, 1}, 1};
    Color<float> resutl3 = ray_tracer.compute_lightning(mat1, plight2, position1, eye_dir1, normal1);
    Color<float> ref3{0.7364, 0.7364, 0.7364};
    ASSERT_EQ(ref3, resutl3);

    Vector<float> eye_dir3{0, -val, -val};
    Color<float> resutl4 = ray_tracer.compute_lightning(mat1, plight2, position1, eye_dir3, normal1);
    Color<float> ref4{1.6364, 1.6364, 1.6364};
    ASSERT_EQ(ref3, resutl3);

    lights::PointLight plight3{Vector<float>{0, 0, 10}, Color<float>{1, 1, 1}, 2};
    Color<float> resutl5 = ray_tracer.compute_lightning(mat1, plight3, position1, eye_dir1, normal1);
    Color<float> ref5{0.1, 0.1, 0.1};
    ASSERT_EQ(ref3, resutl3);
}


TEST(RayTracerWorldSceneShadingTest, TestingWorldSceneShading)
{
    WorldScene world_scene{};
    world_scene.create_default_world();
    Ray ray{Vector<float>{0, 0, -5}, Vector<float>{0, 0, 1}};

    types::intersection intersection{
        world_scene.get_shapes()[0].get()->get_type(),
        world_scene.get_shapes()[0].get()->get_id(),
        4
    };

    RayTracer ray_tracer{};
    types::intersection_state intersection_state = world_scene.precompute_intersection_state(*world_scene.get_shapes()[0],
                                                                                              intersection,
                                                                                              ray);
    Color<float> shading_color1 = ray_tracer.compute_shading(world_scene, intersection_state);
    Color<float> ref_color1{0.38066, 0.47583, 0.2855};

    ASSERT_EQ(shading_color1, ref_color1);
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

    types::intersection intersection{
        world_scene.get_shapes()[1].get()->get_type(),
        world_scene.get_shapes()[1].get()->get_id(),
        0.5
    };

    types::intersection_state intersection_state = world_scene.precompute_intersection_state(*world_scene.get_shapes()[1],
                                                                                             intersection,
                                                                                             ray);
    Color<float> shading_color = ray_tracer.compute_shading(world_scene, intersection_state);
    Color<float> ref_color{0.90498, 0.90498, 0.90498};

    ASSERT_EQ(shading_color, ref_color);

}



int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
