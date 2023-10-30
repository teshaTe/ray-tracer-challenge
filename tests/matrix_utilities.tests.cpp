#include <gtest/gtest.h>
#include "Containers/Vector.hpp"
#include "Containers/Matrix.hpp"
#include "Core/MatrixUtils.hpp"


using namespace ray_tracer;

TEST(TranslationMatrixTest, TestingTranslation_operation)
{
    MatrixUtlities mutils;
    Matrix<float> tr_mat1 = mutils.translation_mat(5, -3, 2);
    Vector<float> point1{-3, 4, 5};
    Matrix<float> res1 = tr_mat1.mul(point1);
    Vector<float> res1_1x3 = res1.to_vec_1x3();

    Vector<float> ref1_1x3{2, 1, 7};
    ASSERT_EQ(res1_1x3, ref1_1x3);

    Matrix<float> tr_mat2 = mutils.translation_mat(5, -3, 2);
    Matrix<float> inv_tr_mat2 = tr_mat2.inv();
    Vector<float> point2{-3, 4, 5};
    Matrix<float> res2 = inv_tr_mat2.mul(point2);
    Vector<float> res2_1x3 = res2.to_vec_1x3();

    Vector<float> ref2_1x3{-8, 7, 3};
    ASSERT_EQ(res2_1x3, ref2_1x3);
}

TEST(ScalingMatrixTest, TestingScaling_operation)
{
    MatrixUtlities mutils;
    Matrix<float> tr_mat1 = mutils.scaling_mat(2, 3, 4);
    Vector<float> point1{-4, 6, 8};
    Matrix<float> res1 = tr_mat1.mul(point1);
    Vector<float> res1_1x3 = res1.to_vec_1x3();

    Vector<float> ref1_1x3{-8, 18, 32};
    ASSERT_EQ(res1_1x3, ref1_1x3);

    Matrix<float> tr_mat2 = mutils.scaling_mat(2, 3, 4);
    Matrix<float> inv_tr_mat2 = tr_mat2.inv();
    Vector<float> point2{-4, 6, 8};
    Matrix<float> res2 = inv_tr_mat2.mul(point2);
    Vector<float> res2_1x3 = res2.to_vec_1x3();

    Vector<float> ref2_1x3{-2, 2, 2};
    ASSERT_EQ(res2_1x3, ref2_1x3);

    Matrix<float> tr_mat3 = mutils.scaling_mat(-1, 1, 1);
    Vector<float> point3{2, 3, 4};
    Matrix<float> res3 = tr_mat3.mul(point3);
    Vector<float> res3_1x3 = res3.to_vec_1x3();

    Vector<float> ref3_1x3{-2, 3, 4};
    ASSERT_EQ(res3_1x3, ref3_1x3);
}

TEST(RotationXAxisMatrixTest, TestingRotation_XAxis_operation)
{
    Vector<float> point1{0, 1, 0};
    MatrixUtlities mutils;
    Matrix<float> Rx1 = mutils.rotation_mat_XAxis(mutils.toRadiance(45.0));
    Matrix<float> Rx2 = mutils.rotation_mat_XAxis(mutils.toRadiance(90.0));

    Vector<float> res1 = Rx1.mul(point1).to_vec_1x3();
    Vector<float> res2 = Rx2.mul(point1).to_vec_1x3();

    float tmp = std::sqrt(2.0)/2.0;
    Vector<float> ref1{0, tmp, tmp};
    Vector<float> ref2{0, 0, 1};

    ASSERT_EQ(res1, ref1);
    ASSERT_EQ(res2, ref2);

    // inverse of the RX1
    Vector<float> res3 = Rx1.inv().mul(point1).to_vec_1x3();

    Vector<float> ref3{0, tmp, -tmp};
    ASSERT_EQ(res3, ref3);
}

TEST(RotationYAxisMatrixTest, TestingRotation_YAxis_operation)
{
    Vector<float> point1{0, 0, 1};
    MatrixUtlities mutils;
    Matrix<float> Ry1 = mutils.rotation_mat_YAxis(mutils.toRadiance(45.0));
    Matrix<float> Ry2 = mutils.rotation_mat_YAxis(mutils.toRadiance(90.0));

    Vector<float> res1 = Ry1.mul(point1).to_vec_1x3();
    Vector<float> res2 = Ry2.mul(point1).to_vec_1x3();

    float tmp = std::sqrt(2.0)/2.0;
    Vector<float> ref1{tmp, 0, tmp};
    Vector<float> ref2{1, 0, 0};

    ASSERT_EQ(res1, ref1);
    ASSERT_EQ(res2, ref2);
}

TEST(RotationZAxisMatrixTest, TestingRotation_ZAxis_operation)
{
    Vector<float> point1{0, 1, 0};
    MatrixUtlities mutils;
    Matrix<float> Rz1 = mutils.rotation_mat_ZAxis(mutils.toRadiance(45.0));
    Matrix<float> Rz2 = mutils.rotation_mat_ZAxis(mutils.toRadiance(90.0));

    Vector<float> res1 = Rz1.mul(point1).to_vec_1x3();
    Vector<float> res2 = Rz2.mul(point1).to_vec_1x3();

    float tmp = std::sqrt(2.0)/2.0;
    Vector<float> ref1{-tmp, tmp, 0};
    Vector<float> ref2{-1, 0, 0};

    ASSERT_EQ(res1, ref1);
    ASSERT_EQ(res2, ref2);

}

TEST(SkewMatrixTest, TestingSkew_operation)
{
    Vector<float> point{2, 3, 4};
    MatrixUtlities mutils;

    Matrix<float> m1 = mutils.skew_mat(0, 1, 0, 0, 0, 0);
    Vector<float> res1 = m1.mul(point).to_vec_1x3();
    Vector<float> ref1{6, 3, 4};
    ASSERT_EQ(res1, ref1);

    Matrix<float> m2 = mutils.skew_mat(0, 0, 1, 0, 0, 0);
    Vector<float> res2 = m2.mul(point).to_vec_1x3();
    Vector<float> ref2{2, 5, 4};
    ASSERT_EQ(res2, ref2);

    Matrix<float> m3 = mutils.skew_mat(0, 0, 0, 1, 0, 0);
    Vector<float> res3 = m3.mul(point).to_vec_1x3();
    Vector<float> ref3{2, 7, 4};
    ASSERT_EQ(res3, ref3);

    Matrix<float> m4 = mutils.skew_mat(0, 0, 0, 0, 1, 0);
    Vector<float> res4 = m4.mul(point).to_vec_1x3();
    Vector<float> ref4{2, 3, 6};
    ASSERT_EQ(res4, ref4);

    Matrix<float> m5 = mutils.skew_mat(0, 0, 0, 0, 0, 1);
    Vector<float> res5 = m5.mul(point).to_vec_1x3();
    Vector<float> ref5{2, 3, 7};
    ASSERT_EQ(res5, ref5);
}

TEST(OperationComboMatrixTest, TestingCombo_operations)
{
    Vector<float> point{1, 0, 1};
    MatrixUtlities mutils;

    Matrix<float> m1 = mutils.rotation_mat_XAxis(mutils.toRadiance(90));
    Matrix<float> m2 = mutils.scaling_mat(5, 5, 5);
    Matrix<float> m3 = mutils.translation_mat(10, 5, 7);

    Vector<float> p1 = m1.mul(point).to_vec_1x3();
    Vector<float> p1_ref{1, -1, 0};
    ASSERT_EQ(p1, p1_ref);

    Vector<float> p2 = m2.mul(p1).to_vec_1x3();
    Vector<float> p2_ref{5, -5, 0};
    ASSERT_EQ(p2, p2_ref);

    Vector<float> p3 = m3.mul(p2).to_vec_1x3();
    Vector<float> p3_ref{15, 0, 7};
    ASSERT_EQ(p3, p3_ref);

    Vector<float> p4 = m3.mul(m2).mul(m1).mul(point).to_vec_1x3();
    ASSERT_EQ(p4, p3_ref);


}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
