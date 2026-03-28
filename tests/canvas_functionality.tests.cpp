#include <gtest/gtest.h>
#include "Core/Canvas.hpp"
#include "Core/Camera.h"
#include "Core/Ray.hpp"
#include "Core/MatrixUtils.hpp"
#include <iostream>

using namespace ray_tracer;

TEST(CreateCanvasTest, TestingCanvasAPI)
{
    Canvas<int> canvas(10, 20);
    ASSERT_EQ(10, canvas.get_canvas_width());
    ASSERT_EQ(20, canvas.get_canvas_height());
    ASSERT_EQ(200, canvas.get_canvas_container_size());

    Color<int> ref_color{0, 0, 0};
    for(int i=0; i < canvas.get_canvas_container_size(); ++i)
        ASSERT_EQ(ref_color, canvas[i]);

    Color<int> c1{255, 0, 255};
    canvas.set_pixel(2, 10, c1);
    Color<int> c1_check = canvas.get_pixel(2, 10);
    Color<int> c2_check = canvas[2 + 10 * 10];
    ASSERT_EQ(c1, c1_check);
    ASSERT_EQ(c1, c2_check);

    canvas[0] = c1;
    std::cout << canvas[0] << std::endl;
    ASSERT_EQ(c1, canvas[0]);
}

TEST(SavingCanvasTest, TestingCanvasSavingToFile)
{
    Canvas<int> canvas(3, 3);
    Color<int> c1{255, 0, 0};
    Color<int> c2{0, 255, 0};
    Color<int> c3{0, 0, 255};
    canvas.set_pixel(0, 0, c1);
    canvas.set_pixel(1, 1, c2);
    canvas.set_pixel(2, 2, c3);

    std::string file_name = "test_img";
    std::string path = "..";
    canvas.save_to_ppm(file_name, path);

    Canvas<int> canvas_dst(3, 3);
    canvas_dst = canvas.load_ppm(file_name, path);

    ASSERT_EQ(canvas, canvas_dst);
}

TEST(ConstructingRayThroughCanvasTest, TestingRayConstructionThroughCanvas)
{
    Canvas<int> canvas{201, 101};
    Camera camera{201, 101, 90};

    Ray ray1 = canvas.shoot_ray_for_pixel(&camera, 100, 50);
    Vector<float> ref_origin1{0, 0, 0};
    Vector<float> ref_dir1{0, 0, -1};

    ASSERT_EQ(ray1.get_origin(), ref_origin1);
    ASSERT_EQ(ray1.get_direction(), ref_dir1);

    Ray ray2 = canvas.shoot_ray_for_pixel(&camera, 0, 0);
    Vector<float> ref_origin2{0, 0, 0};
    Vector<float> ref_dir2{0.66519, 0.33259, -0.66851};

    ASSERT_EQ(ray2.get_origin(), ref_origin2);
    ASSERT_EQ(ray2.get_direction(), ref_dir2);

    MatrixUtlities mat_utils{};
    Matrix<float> cam_view_tr = mat_utils.rotation_mat_YAxis(mat_utils.toRadiance(45.0)).mul(mat_utils.translation_mat(0, -2, 5));
    camera.set_view_transform(cam_view_tr);
    Ray ray3 = canvas.shoot_ray_for_pixel(&camera, 100, 50);

    Vector<float> ref_origin3{0, 2, -5};
    float v1 = std::sqrt(2) / 2.0f;
    Vector<float> ref_dir3{v1, 0, -v1};

    ASSERT_EQ(ray3.get_origin(), ref_origin3);
    ASSERT_EQ(ray3.get_direction(), ref_dir3);
}


int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
