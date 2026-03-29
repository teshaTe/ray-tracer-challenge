#include "math.h"

#include <gtest/gtest.h>

#include "Core/Camera.h"
#include "Containers/Vector.hpp"
#include "Containers/Matrix.hpp"
#include "Core/MatrixUtils.hpp"


using namespace ray_tracer;


TEST(CameraCreationTest, TstingCameraCreation)
{
    MatrixUtlities mat_utils;
    Camera camera1{160, 120, 90.0f};
    ASSERT_EQ(camera1.get_horizontal_size(), 160);
    ASSERT_EQ(camera1.get_vertical_size(), 120);
    ASSERT_FLOAT_EQ(camera1.get_fov(), mat_utils.toRadiance(90.0f));

    Matrix<float> ref_view_transform{4, 4};
    ref_view_transform.I();
    ASSERT_EQ(camera1.get_view_transform(), ref_view_transform);

    Camera camera2{200, 125, 90.0f};
    ASSERT_FLOAT_EQ(camera2.get_pixel_size(), 0.01f);

    Camera camera3{125, 200, 90.0f};
    ASSERT_FLOAT_EQ(camera3.get_pixel_size(), 0.01f);
}



TEST(DefaultOrientationTest, TestingDefaultOrientation)
{
    Vector<float> from{0, 0, 0};
    Vector<float> to{0, 0, -1};
    Vector<float> up{0, 1, 0};

    Camera camera{1024, 1024, 90};
    camera.compute_view_transform(from, to, up);
    Matrix<float> view_transform = camera.get_view_transform();

    Matrix<float> ref_view_transform{4, 4};
    ref_view_transform.I();

    ASSERT_EQ(view_transform, ref_view_transform);
}

TEST(ViewTransformPosZTest, TestingViewTransformForPosZ)
{
    Vector<float> from{0, 0, 0};
    Vector<float> to{0, 0, 1};
    Vector<float> up{0, 1, 0};

    Camera camera{1024, 1024, 90};
    camera.compute_view_transform(from, to, up);
    Matrix<float> view_transform = camera.get_view_transform();

    MatrixUtlities mat_utils{};
    Matrix<float> ref_view_transform = mat_utils.scaling_mat(-1, 1, -1);

    ASSERT_EQ(view_transform, ref_view_transform);
}

TEST(ViewTransformMovingWorldTest, TestingViewTransformMovingWorld)
{
    Vector<float> from{0, 0, 8};
    Vector<float> to{0, 0, 0};
    Vector<float> up{0, 1, 0};

    Camera camera{1024, 1024, 90};
    camera.compute_view_transform(from, to, up);
    Matrix<float> view_transform = camera.get_view_transform();

    MatrixUtlities mat_utils{};
    Matrix<float> ref_view_transform = mat_utils.translation_mat(0, 0, -8);

    ASSERT_EQ(view_transform, ref_view_transform);
}

TEST(ViewTransformArbitraryDirTest, TestingViewTransformArbitraryDir)
{
    Vector<float> from{1, 3, 2};
    Vector<float> to{4, -2, 8};
    Vector<float> up{1, 1, 0};

    Camera camera{1024, 1024, 90};
    camera.compute_view_transform(from, to, up);
    Matrix<float> view_transform = camera.get_view_transform();

    std::vector<std::vector<float>> ref_transform{
                                                  {-0.50709, 0.50709, 0.67612, -2.36643},
                                                  {0.76772, 0.60609, 0.12122, -2.82843},
                                                  {-0.35857, 0.59761, -0.71714, 0.00000},
                                                  {0, 0, 0, 1}};
    Matrix<float> ref_view_transform{4, 4, ref_transform};

    ASSERT_EQ(view_transform, ref_view_transform);
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
