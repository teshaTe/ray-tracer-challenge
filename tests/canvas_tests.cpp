#include <gtest/gtest.h>
#include "Canvas.hpp"
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
    Canvas<int> canvas(5, 3);
}


int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
