#include "math.h"

#include <gtest/gtest.h>

#include "Containers/Vector.hpp"
#include "RayTracer/Shapes/sphere.h"
#include "Core/Material.hpp"
#include "Core/RayTracer.h"
#include "Lights/point_light.h"
#include "Core/worldscene.h"


using namespace ray_tracer;

TEST(WorldSceneEmptyTest, TestingWorldSceneEmpty)
{
    WorldScene world_scene;
    ASSERT_EQ(world_scene.contains_lights(), false);
    ASSERT_EQ(world_scene.contains_shapes(), false);
}

TEST(WorldSceneCreationTest, TestingWorldScene)
{
    lights::PointLight plight{Vector<float>(-10, 10, -10), Color<float>{1, 1, 1}};

    shapes::Sphere sp1{Vector<float>{0, 0, 0}, 1.0, 0};
    materials::BaseMaterial mat1;
    mat1.ambient = 0.1;
    mat1.color = Color<float>{0.8, 1.0, 0.6};
    mat1.snininess = 200.0;
    mat1.diffuse = 0.7;
    mat1.specular = 0.2;
    sp1.set_material(mat1);

    shapes::Sphere sp2{Vector<float>{0.5, 0, 0.5}, 1.0, 1};
    sp2.scale(Vector<float>{0.5, 0.5, 0.5});

    WorldScene world_scene{};
    world_scene.add_light(plight);
    world_scene.add_shape(sp1);
    world_scene.add_shape(sp2);

    ASSERT_EQ(world_scene.contains_lights(), true);
    ASSERT_EQ(world_scene.contains_shapes(), true);

    world_scene.clear();
    ASSERT_EQ(world_scene.contains_lights(), false);
    ASSERT_EQ(world_scene.contains_shapes(), false);
}

TEST(WorldSceneIntersectionTest, TestingWOrldSceneIntersection)
{
    shapes::Sphere sp1{Vector<float>{0, 0, 0}, 1.0, 0};
    materials::BaseMaterial mat1;
    mat1.ambient = 0.1;
    mat1.color = Color<float>{0.8, 1.0, 0.6};
    mat1.snininess = 200.0;
    mat1.diffuse = 0.7;
    mat1.specular = 0.2;
    sp1.set_material(mat1);

    shapes::Sphere sp2{Vector<float>{0, 0, 0}, 1.0, 1};
    sp2.scale(Vector<float>{0.5, 0.5, 0.5});

    WorldScene world_scene{};
    world_scene.add_shape(sp1);
    world_scene.add_shape(sp2);

    Ray ray{Vector<float>{0, 0, -5}, Vector<float>{0, 0, 1}};
    std::vector<types::intersection> intersections = world_scene.intersect(ray);

    ASSERT_EQ(intersections.size(), 4);
    ASSERT_EQ(intersections[0].t, 4);
    ASSERT_EQ(intersections[1].t, 4.5);
    ASSERT_EQ(intersections[2].t, 5.5);
    ASSERT_EQ(intersections[3].t, 6);
}

TEST(WorldScenePrecompIntersectionStateTest, TestingWorldSceneIntersectionStatePrecomp)
{
    Ray ray{Vector<float>{0, 0, -5}, Vector<float>{0, 0, 1}};
    shapes::Sphere sp{Vector<float>{0, 0, 0}, 1.0, 0};
    types::intersection intersection;
    intersection.obj_type = sp.get_type();
    intersection.t = 4;

    WorldScene world_scene{};
    types::intersection_state intersection_state = world_scene.precompute_intersection_state(&sp, intersection, ray);

    Vector<float> point_ref{0, 0, -1};
    Vector<float> eye_dir_ref{0, 0, -1};
    Vector<float> normal_ref{0, 0, -1};

    ASSERT_EQ(intersection_state.t, intersection.t);
    ASSERT_EQ(intersection_state.obj_type, intersection.obj_type);
    ASSERT_EQ(intersection_state.point, point_ref);
    ASSERT_EQ(intersection_state.eye_dir, eye_dir_ref);
    ASSERT_EQ(intersection_state.normal, normal_ref);
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
