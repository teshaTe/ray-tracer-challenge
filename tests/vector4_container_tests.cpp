#include <gtest/gtest.h>
#include "Vector.hpp"


TEST(AddingVectorsTest, TestingVector4_sum)
{
    const math_types::Vector4<int> v_ref_i{1, 1, 6, 4};
    const math_types::Vector4<int> v1_i{3, -2, 5, 1};
    const math_types::Vector4<int> v2_i{-2, 3, 1, 3};
    const math_types::Vector4<int> res_i = v1_i + v2_i;
    ASSERT_EQ(v_ref_i, res_i);

    const math_types::Vector4<float> v_ref_f{1.5, 1.f, 6.1, 4.1};
    const math_types::Vector4<float> v1_f{3.5, -2.f, 5.1, 2.1};
    const math_types::Vector4<float> v2_f{-2.f, 3.f, 1.f, 2.f};
    const math_types::Vector4<float> res_f = v1_f + v2_f;
    ASSERT_EQ(v_ref_f, res_f);
}

TEST(AddingVectorsTest, TestingVector3_subtr)
{
    const math_types::Vector4<int> v_ref_i{-3, -4, -6, 1};
    const math_types::Vector4<int> v1_i{3, 2, 1, 3};
    const math_types::Vector4<int> v2_i{6, 6, 7, 2};
    const math_types::Vector4<int> res_i = v1_i - v2_i;
    ASSERT_EQ(v_ref_i, res_i);

    const math_types::Vector4<float> v_ref_f{-2.7, -4.f, -5.7, 2.5};
    const math_types::Vector4<float> v1_f{3.5, 2.f, 1.5, 3.5};
    const math_types::Vector4<float> v2_f{6.2, 6.f, 7.2, 1.f};
    const math_types::Vector4<float> res_f = v1_f - v2_f;
    ASSERT_EQ(v_ref_f, res_f);
}

TEST(AddingVectorsTest, TestingVector3_multi_by_scalar)
{
    const math_types::Vector4<int> v_ref_i{-9, 6, -3, -6};
    const math_types::Vector4<int> v_i{3, -2, 1, 2};
    const int scalar_i = -3;
    const math_types::Vector4<int> res_i = v_i * scalar_i;
    ASSERT_EQ(v_ref_i, res_i);

    const math_types::Vector4<float> v_ref_f{-8.75, -5.f, 3.75, -7.5};
    const math_types::Vector4<float> v_f{3.5, 2.0, -1.5, 3.f};
    const float scalar_f = -2.5;
    const math_types::Vector4<float> res_f = v_f * scalar_f;
    ASSERT_EQ(v_ref_f, res_f);
}

TEST(AddingVectorsTest, TestingVector3_divide_by_scalar)
{
    const math_types::Vector4<int> v_ref_i{-1, 0, 0, 3};
    const math_types::Vector4<int> v_i{3, -2, 1, -9};
    const int scalar_i = -3;
    const math_types::Vector4<int> res_i = v_i / scalar_i;
    ASSERT_EQ(v_ref_i, res_i);

    const math_types::Vector4<float> v_ref_f{-1.4, -0.8, 0.6, -2.f};
    const math_types::Vector4<float> v_f{3.5, 2.0, -1.5, 5.f};
    const float scalar_f = -2.5;
    const math_types::Vector4<float> res_f = v_f / scalar_f;
    ASSERT_EQ(v_ref_f, res_f);
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
