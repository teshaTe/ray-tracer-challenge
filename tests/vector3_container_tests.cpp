#include <gtest/gtest.h>
#include "Vector.hpp"


TEST(AddingVectorsTest, TestingVector3_sum)
{
    const math_types::Vector3<int> v_ref_i{1, 1, 6};
    const math_types::Vector3<int> v1_i{3, -2, 5};
    const math_types::Vector3<int> v2_i{-2, 3, 1};
    const math_types::Vector3<int> res_i = v1_i + v2_i;
    ASSERT_EQ(v_ref_i, res_i);

    const math_types::Vector3<float> v_ref_f{1.5f, 1.0f, 6.1f};
    const math_types::Vector3<float> v1_f{3.5f, -2.0f, 5.1f};
    const math_types::Vector3<float> v2_f{-2.0f, 3.0f, 1.0f};
    const math_types::Vector3<float> res_f = v1_f + v2_f;
    ASSERT_EQ(v_ref_f, res_f);
}

TEST(AddingVectorsTest, TestingVector3_subtr)
{
    const math_types::Vector3<int> v_ref_i{-3, -4, -6};
    const math_types::Vector3<int> v1_i{3, 2, 1};
    const math_types::Vector3<int> v2_i{6, 6, 7};
    const math_types::Vector3<int> res_i = v1_i - v2_i;
    ASSERT_EQ(v_ref_i, res_i);

    const math_types::Vector3<float> v_ref_f{-2.7, -4, -5.7};
    const math_types::Vector3<float> v1_f{3.5, 2.0, 1.5};
    const math_types::Vector3<float> v2_f{6.2, 6.0, 7.2};
    const math_types::Vector3<float> res_f = v1_f - v2_f;
    ASSERT_EQ(v_ref_f, res_f);
}

TEST(AddingVectorsTest, TestingVector3_multi_by_scalar)
{
    const math_types::Vector3<int> v_ref_i{-9, 6, -3};
    const math_types::Vector3<int> v_i{3, -2, 1};
    const int scalar_i = -3;
    const math_types::Vector3<int> res_i = v_i * scalar_i;
    ASSERT_EQ(v_ref_i, res_i);

    const math_types::Vector3<float> v_ref_f{-8.75, -5.0, 3.75};
    const math_types::Vector3<float> v_f{3.5, 2.0, -1.5};
    const float scalar_f = -2.5;
    const math_types::Vector3<float> res_f = v_f * scalar_f;
    ASSERT_EQ(v_ref_f, res_f);
}

TEST(AddingVectorsTest, TestingVector3_divide_by_scalar)
{
    const math_types::Vector3<int> v_ref_i{-1, 0, 0};
    const math_types::Vector3<int> v_i{3, -2, 1};
    const int scalar_i = -3;
    const math_types::Vector3<int> res_i = v_i / scalar_i;
    ASSERT_EQ(v_ref_i, res_i);

    const math_types::Vector3<float> v_ref_f{-1.4, -0.8, 0.6};
    const math_types::Vector3<float> v_f{3.5, 2.0, -1.5};
    const float scalar_f = -2.5;
    const math_types::Vector3<float> res_f = v_f / scalar_f;
    ASSERT_EQ(v_ref_f, res_f);
}

TEST(AddingVectorsTest, TestingVector3_magnitude)
{
    const math_types::Vector3<float> v1{1, 0, 0};
    const float magn1 = v1.magnitude();
    ASSERT_EQ(1.0f, magn1);

    const math_types::Vector3<float> v2{0, 1, 0};
    const float magn2 = v2.magnitude();
    ASSERT_EQ(1.0f, magn2);

    const math_types::Vector3<float> v3{0, 0, 1};
    const float magn3 = v3.magnitude();
    ASSERT_EQ(1.0f, magn3);

    const math_types::Vector3<float> v4{1, 2, 3};
    const float magn4 = v4.magnitude();
    const float magn4_ref = std::sqrt(1.f*1.f + 2.f*2.f + 3.f*3.f);
    ASSERT_EQ(magn4_ref, magn4);

    const math_types::Vector3<int> v5{1, 2, 3};
    const float magn5 = v5.magnitude();
    const float magn5_ref = std::sqrt(1*1 + 2*2 + 3*3);
    ASSERT_EQ(magn5_ref, magn5);

    const math_types::Vector3<float> v6{-1, -2, -3};
    const float magn6 = v6.magnitude();
    const float magn6_ref = std::sqrt((-1.f)*(-1.f) + (-2.f)*(-2.f) + (-3.f)*(-3.f));
    ASSERT_EQ(magn6_ref, magn6);

    const math_types::Vector3<int> v7{-1, -2, -3};
    const float magn7 = v5.magnitude();
    const float magn7_ref = std::sqrt((-1)*(-1) + (-2)*(-2) + (-3)*(-3));
    ASSERT_EQ(magn7_ref, magn7);
}

TEST(AddingVectorsTest, TestingVector3_normalization)
{
    const math_types::Vector3<int> v1_i{4, 0, 0};
    const math_types::Vector3<int> v1_i_normed = v1_i.normalize();
    const math_types::Vector3<int> v1_i_ref{1, 0, 0};
    ASSERT_EQ(v1_i_ref, v1_i_normed);

    const math_types::Vector3<float> v1_f{4, 0, 0};
    const math_types::Vector3<float> v1_f_normed = v1_f.normalize();
    const math_types::Vector3<float> v1_f_ref{1, 0, 0};
    ASSERT_EQ(v1_f_ref, v1_f_normed);

    const math_types::Vector3<int> v2_i{1, 2, 3};
    const math_types::Vector3<int> v2_i_normed = v2_i.normalize();

    const float v2_i_norm = std::sqrt(1*1 + 2*2 + 3*3);
    const math_types::Vector3<int> v2_i_ref{1/static_cast<int>(v2_i_norm), 2/static_cast<int>(v2_i_norm), 3/static_cast<int>(v2_i_norm)};
    ASSERT_EQ(v2_i_ref, v2_i_normed);

    const int norm2_i = std::sqrt(v2_i_normed[0]*v2_i_normed[0] + v2_i_normed[1]*v2_i_normed[1] + v2_i_normed[2]*v2_i_normed[2]);
    ASSERT_EQ(1, norm2_i);

    const math_types::Vector3<float> v2_f{1, 2, 3};
    const math_types::Vector3<float> v2_f_normed = v2_f.normalize();
    const float v2_f_norm = std::sqrt(1.f*1.f + 2.f*2.f + 3.f*3.f);
    const math_types::Vector3<float> v2_f_ref{1.f/v2_f_norm, 2.f/v2_f_norm, 3.f/v2_f_norm};
    ASSERT_EQ(v2_f_ref, v2_f_normed);

    const float norm2_f = std::sqrt(v2_f_normed[0]*v2_f_normed[0] + v2_f_normed[1]*v2_f_normed[1] + v2_f_normed[2]*v2_f_normed[2]);
    ASSERT_FLOAT_EQ(1.f, norm2_f);
}

TEST(AddingVectorsTest, TestingVector3_dot_prod)
{
    const math_types::Vector3<int> v1_i{1, 2, 3};
    const math_types::Vector3<int> v2_i{2, 3, 4};
    const int res_i_ref = 20;
    const int res_i = v1_i.dot(v2_i);
    ASSERT_EQ(res_i_ref, res_i);

    const math_types::Vector3<float> v1_f{1.5, -2, 3};
    const math_types::Vector3<float> v2_f{2.5, 3, 4};
    const float res_f_ref = 9.75;
    const float res_f = v1_f.dot(v2_f);
    ASSERT_EQ(res_f_ref, res_f);
}

TEST(AddingVectorsTest, TestingVector3_cross_prod)
{
    const math_types::Vector3<int> v1_i{1, 2, 3};
    const math_types::Vector3<int> v2_i{2, 3, 4};

    const math_types::Vector3<int> res1_i = v1_i.cross(v2_i);
    const math_types::Vector3<int> res2_i = v2_i.cross(v1_i);

    const math_types::Vector3<int> res1_i_ref{-1, 2, -1};
    const math_types::Vector3<int> res2_i_ref{1, -2, 1};

    ASSERT_EQ(res1_i_ref, res1_i);
    ASSERT_EQ(res2_i_ref, res2_i);

    const math_types::Vector3<float> v1_f{1.5, -2, 3};
    const math_types::Vector3<float> v2_f{2.5, 3, 4};

    const math_types::Vector3<float> res1_f = v1_f.cross(v2_f);
    const math_types::Vector3<float> res2_f = v2_f.cross(v1_f);

    const math_types::Vector3<float> res1_f_ref{-2*4 - 3*3, 3*2.5 - 1.5*4, 1.5*3 + 2*2.5};
    const math_types::Vector3<float> res2_f_ref{3*3 + 4*2,  4*1.5 - 2.5*3, -2.5*2 -3*1.5};

    ASSERT_EQ(res1_f_ref, res1_f);
    ASSERT_EQ(res2_f_ref, res2_f);
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
