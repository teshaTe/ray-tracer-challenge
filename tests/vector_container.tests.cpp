#include <gtest/gtest.h>
#include "Containers/Vector.hpp"

using namespace ray_tracer;

TEST(AddingVectorsTest, TestingVector_sum)
{
    const Vector<float> v_ref1{1.5, 1.0, 6.1, 2.0};
    const Vector<float> v1{3.5f, -2.0f, 5.1f, 1.5};
    const Vector<float> v2{-2.0f, 3.0f, 1.0f, 0.5};

    const Vector<float> res1 = v1 + v2;
    ASSERT_EQ(v_ref1, res1);

    const Vector<float> v_ref2{1.5, 1.0, 6.1};
    const Vector<float> v3{3.5f, -2.0f, 5.1f};
    const Vector<float> v4{-2.0f, 3.0f, 1.0f};
    const Vector<float> res2 = v1 + v2;
    ASSERT_EQ(v_ref2, res2);

    const Vector<float> v_ref3{1.5, 1.0};
    const Vector<float> v5{3.5f, -2.0f};
    const Vector<float> v6{-2.0f, 3.0f};
    const Vector<float> res3 = v3 + v4;
    ASSERT_EQ(v_ref3, res3);
}

TEST(AddingVectorsTest, TestingVector_subtr)
{
    const Vector<float> v_ref1{-2.7, -4, -5.7, 1.5};
    const Vector<float> v1{3.5, 2.0, 1.5, 2.0};
    const Vector<float> v2{6.2, 6.0, 7.2, 0.5};
    const Vector<float> res1 = v1 - v2;
    ASSERT_EQ(v_ref1, res1);

    const Vector<float> v_ref2{-2.7, -4, -5.7};
    const Vector<float> v3{3.5, 2.0, 1.5};
    const Vector<float> v4{6.2, 6.0, 7.2};
    const Vector<float> res2 = v3 - v4;
    ASSERT_EQ(v_ref2, res2);

    const Vector<float> v_ref3{-2.7, -4};
    const Vector<float> v5{3.5, 2.0};
    const Vector<float> v6{6.2, 6.0};
    const Vector<float> res3 = v5 - v6;
    ASSERT_EQ(v_ref3, res3);
}

TEST(MultiVectorsByScalarTest, TestingVector_multi_by_scalar)
{
    const float scalar = -2.5;
    const Vector<float> v_ref1{-8.75, -5.0, 3.75, -2.5};
    const Vector<float> v1{3.5, 2.0, -1.5, 1.0};
    const Vector<float> res1 = v1 * scalar;
    ASSERT_EQ(v_ref1, res1);

    const Vector<float> v_ref2{-8.75, -5.0, 3.75};
    const Vector<float> v2{3.5, 2.0, -1.5};
    const Vector<float> res2 = v2 * scalar;
    ASSERT_EQ(v_ref2, res2);

    const Vector<float> v_ref3{-8.75, -5.0};
    const Vector<float> v3{3.5, 2.0};
    const Vector<float> res3 = v3 * scalar;
    ASSERT_EQ(v_ref3, res3);
}

TEST(DivideVectorByScalarTest, TestingVector_divide_by_scalar)
{
    const float scalar = -2.5;
    const Vector<float> v_ref1{-1.4, -0.8, 0.6, 1.0};
    const Vector<float> v1{3.5, 2.0, -1.5, -2.5};
    const Vector<float> res1 = v1 / scalar;
    ASSERT_EQ(v_ref1, res1);

    const Vector<float> v_ref2{-1.4, -0.8, 0.6};
    const Vector<float> v2{3.5, 2.0, -1.5};
    const Vector<float> res2 = v2 / scalar;
    ASSERT_EQ(v_ref2, res2);

    const Vector<float> v_ref3{-1.4, -0.8};
    const Vector<float> v3{3.5, 2.0};
    const Vector<float> res3 = v2 / scalar;
    ASSERT_EQ(v_ref2, res2);
}

TEST(MagnitudeVectorTest, TestingVector_magnitude)
{
    const Vector<float> v1{1, 0, 0};
    const float magn1 = v1.magnitude();
    ASSERT_EQ(1.0f, magn1);

    const Vector<float> v2{0, 1, 0};
    const float magn2 = v2.magnitude();
    ASSERT_EQ(1.0f, magn2);

    const Vector<float> v3{0, 0, 1};
    const float magn3 = v3.magnitude();
    ASSERT_EQ(1.0f, magn3);

    const Vector<float> v4{1, 2, 3};
    const float magn4 = v4.magnitude();
    const float magn4_ref = std::sqrt(1.f*1.f + 2.f*2.f + 3.f*3.f);
    ASSERT_EQ(magn4_ref, magn4);

    const Vector<float> v6{-1, -2, -3};
    const float magn6 = v6.magnitude();
    const float magn6_ref = std::sqrt((-1.f)*(-1.f) + (-2.f)*(-2.f) + (-3.f)*(-3.f));
    ASSERT_EQ(magn6_ref, magn6);
}

TEST(NormalizationVectorsTest, TestingVector_normalization)
{
    const Vector<float> v1{4, 0, 0};
    Vector<float> v1_normed = v1.normalize();
    const Vector<float> v1_ref{1, 0, 0};
    ASSERT_EQ(v1_ref, v1_normed);

    const Vector<float> v2{1, 2, 3};
    Vector<float> v2_normed = v2.normalize();
    const float v2_norm = std::sqrt(1.f*1.f + 2.f*2.f + 3.f*3.f);
    const Vector<float> v2_ref{1.f/v2_norm, 2.f/v2_norm, 3.f/v2_norm};
    ASSERT_EQ(v2_ref, v2_normed);

    const float norm2_ref = std::sqrt(v2_normed[0]*v2_normed[0] + v2_normed[1]*v2_normed[1] + v2_normed[2]*v2_normed[2]);
    ASSERT_FLOAT_EQ(1.f, norm2_ref);
}

TEST(DotProductVectorTest, TestingVector_dot_product)
{
    const Vector<float> v1{1.5, -2, 3};
    const Vector<float> v2{2.5, 3, 4};
    const float res_ref = 9.75;
    const float res = v1.dot(v2);
    ASSERT_EQ(res_ref, res);
}

TEST(CrossProductVectorsTest, TestingVector_cross_prod)
{
    const Vector<float> v1{1.5, -2, 3};
    const Vector<float> v2{2.5, 3, 4};

    const Vector<float> res1 = v1.cross(v2);
    const Vector<float> res2 = v2.cross(v1);

    const Vector<float> ref1{-2*4 - 3*3, 3*2.5 - 1.5*4, 1.5*3 + 2*2.5};
    const Vector<float> ref2{3*3 + 4*2,  4*1.5 - 2.5*3, -2.5*2 -3*1.5};

    ASSERT_EQ(ref1, res1);
    ASSERT_EQ(ref2, res2);
}


TEST(ComputingReflectionTest, TestingReflectionVectorComputation)
{
    Vector<float> in_vec1{1, -1, 0};
    Vector<float> norm_vec1{0, 1, 0};

    Vector<float> refl_vec1 = in_vec1.reflect(norm_vec1);
    Vector<float> ref_reflect_vec1{1, 1, 0};
    ASSERT_EQ(refl_vec1, ref_reflect_vec1);

    Vector<float> in_vec2{0, -1, 0};
    float v2 = std::sqrt(2) / 2.0;
    Vector<float> norm_vec2{v2, v2, 0};

    Vector<float> refl_vec2 = in_vec2.reflect(norm_vec2);
    Vector<float> ref_reflect_vec2{1, 1, 0};
    ASSERT_EQ(refl_vec2, ref_reflect_vec2);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
