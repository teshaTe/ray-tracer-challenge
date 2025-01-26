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

    WorldScene world_scene;
    world_scene.add_light(plight);
    world_scene.add_shape(sp1);
    world_scene.add_shape(sp2);

    ASSERT_EQ(world_scene.contains_lights(), true);
    ASSERT_EQ(world_scene.contains_shapes(), true);

    world_scene.clear();
    ASSERT_EQ(world_scene.contains_lights(), false);
    ASSERT_EQ(world_scene.contains_shapes(), false);
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
