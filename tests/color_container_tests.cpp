#include <gtest/gtest.h>
#include "Color.hpp"

using namespace ray_tracer;

TEST(ColorAssignment, TestingColor_assignment)
{
    const Color<int> col_ref;
    const Color<int> test{0, 0, 0};
    ASSERT_EQ(col_ref, test);
}

TEST(AddingColorsTest, TestingColor_sum)
{
    const Color<int> color1_ref_i{30, 60, 90};
    const Color<int> c1_i{10, 25, 40};
    const Color<int> c2_i{20, 35, 50};
    const Color<int> res1_i = c1_i + c2_i;
    ASSERT_EQ(color1_ref_i, res1_i);

    const Color<float> color3_ref_f{0.7, 0.6, 0.9};
    const Color<float> c1_f{0.5, 0.1, 0.8};
    const Color<float> c2_f{0.2, 0.5, 0.1};
    const Color<float> res3_f = c1_f + c2_f;
    ASSERT_EQ(color3_ref_f, res3_f);
}

TEST(SubtractingColorsTest, TestingColor_subtr)
{
    const Color<int> color1_ref_i{30, 0, 50};
    const Color<int> c1_i{50, 35, 100};
    const Color<int> c2_i{20, 35, 50};
    const Color<int> res1_i = c1_i - c2_i;
    ASSERT_EQ(color1_ref_i, res1_i);

    const Color<float> color3_ref_f{0.3, 0.4, 0.7};
    const Color<float> c1_f{0.5, 0.9, 0.8};
    const Color<float> c2_f{0.2, 0.5, 0.1};
    const Color<float> res3_f = c1_f - c2_f;
    ASSERT_EQ(color3_ref_f, res3_f);
}

TEST(MultyColorsByScalarTest, TestingColor_multi_by_scalar)
{
    const Color<int> color1_ref_i{20, 60, 120};
    const Color<int> c1_i{10, 30, 60};
    const int scalar1 = 2;
    const Color<int> res1_i = c1_i * scalar1;
    ASSERT_EQ(color1_ref_i, res1_i);

    const Color<float> color3_ref_f{1.0, 0.2, 0.6};
    const Color<float> c1_f{0.5, 0.1, 0.3};
    const float scalar3 = 2.0;
    const Color<float> res3_f = c1_f * scalar3;
    ASSERT_EQ(color3_ref_f, res3_f);
}

TEST(DivideColorsTest, TestingColor_divide_by_scalar)
{
    const Color<int> color1_ref_i{5, 15, 30};
    const Color<int> c1_i{10, 30, 60};
    const int scalar1 = 2;
    const Color<int> res1_i = c1_i / scalar1;
    ASSERT_EQ(color1_ref_i, res1_i);

    const Color<float> color3_ref_f{0.25, 0.05, 0.15};
    const Color<float> c1_f{0.5, 0.1, 0.3};
    const float scalar3 = 2.0;
    const Color<float> res3_f = c1_f / scalar3;
    ASSERT_EQ(color3_ref_f, res3_f);
}

TEST(HadamardMultiColorsTest, TestingColor_hadamard_prod)
{
    const Color<int> color1_ref_i{100, 90, 120};
    const Color<int> c1_i{10, 30, 60};
    const Color<int> c2_i{10, 3, 2};
    const Color<int> res1_i = c1_i.hadamard_product(c2_i);
    ASSERT_EQ(color1_ref_i, res1_i);

    const Color<float> color3_ref_f{1.0, 0.3, 0.6};
    const Color<float> c1_f{0.5, 0.1, 0.3};
    const Color<float> c2_f{2.0, 3.0, 2.0};
    const Color<float> res3_f = c1_f.hadamard_product(c2_f);
    ASSERT_EQ(color3_ref_f, res3_f);
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
