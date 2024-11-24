#include "math.h"

#include <gtest/gtest.h>

#include "Containers/Vector.hpp"
#include "Core/Material.hpp"
#include "Core/RayTracer.h"
#include "Lights/point_light.h"


using namespace ray_tracer;

TEST(RayTracerShadingTest, TestingShading)
{
    materials::BaseMaterial mat1;
    mat1.color = Color<float>{1, 1, 1};
    mat1.ambient = 0.1;
    mat1.diffuse = 0.9;
    mat1.specular = 0.9;
    mat1.snininess = 200.0;

    Vector<float> position1{0, 0, 0};
    Vector<float> eye_dir1{0, 0, -1};
    Vector<float> normal1{0, 0, -1};

    lights::PointLight plight1{Vector<float>{0, 0, -10}, Color<float>{1, 1, 1}};
    RayTracer ray_tracer;

    Color<float> resutl1 = ray_tracer.compute_lightning(mat1, plight1, position1, eye_dir1, normal1);
    Color<float> ref1{1.9, 1.9, 1.9};
    ASSERT_EQ(ref1, resutl1);

    float val = std::sqrt(2)/2.0;
    Vector<float> eye_dir2{0, val, val};
    Color<float> resutl2 = ray_tracer.compute_lightning(mat1, plight1, position1, eye_dir2, normal1);
    Color<float> ref2{1.0, 1.0, 1.0};
    ASSERT_EQ(ref2, resutl2);

    lights::PointLight plight2{Vector<float>{0, 10, -10}, Color<float>{1, 1, 1}};
    Color<float> resutl3 = ray_tracer.compute_lightning(mat1, plight2, position1, eye_dir1, normal1);
    Color<float> ref3{0.7364, 0.7364, 0.7364};
    ASSERT_EQ(ref3, resutl3);

    Vector<float> eye_dir3{0, -val, -val};
    Color<float> resutl4 = ray_tracer.compute_lightning(mat1, plight2, position1, eye_dir3, normal1);
    Color<float> ref4{1.6364, 1.6364, 1.6364};
    ASSERT_EQ(ref3, resutl3);

    lights::PointLight plight3{Vector<float>{0, 0, 10}, Color<float>{1, 1, 1}};
    Color<float> resutl5 = ray_tracer.compute_lightning(mat1, plight3, position1, eye_dir1, normal1);
    Color<float> ref5{0.1, 0.1, 0.1};
    ASSERT_EQ(ref3, resutl3);
}




int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
