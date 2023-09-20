#include <gtest/gtest.h>
#include "Matrix.hpp"

using namespace ray_tracer;

TEST(CreatingMatrixTest, TestingMatrix_creation)
{
    Matrix<float> m1{2, 2};
    ASSERT_FLOAT_EQ(m1(0, 0), 0.0f);
    ASSERT_FLOAT_EQ(m1(0, 1), 0.0f);
    ASSERT_FLOAT_EQ(m1(1, 0), 0.0f);
    ASSERT_FLOAT_EQ(m1(1, 1), 0.0f);

    std::vector<std::vector<float>> data{{1, 2}, {3, 4}};
    Matrix<float> m2{2, 2, data};
    ASSERT_FLOAT_EQ(m2(0, 0), 1.0f);
    ASSERT_FLOAT_EQ(m2(0, 1), 2.0f);
    ASSERT_FLOAT_EQ(m2(1, 0), 3.0f);
    ASSERT_FLOAT_EQ(m2(1, 1), 4.0f);
}

TEST(AddingMatrixTest, TestingMatrix_sum)
{
    std::vector<std::vector<float>> data1{{1, 2, 3}, {3, 2, 1}, {0, 0, 1}};
    Matrix<float> m1{3, 3, data1};

    std::vector<std::vector<float>> data2{{1, 0, 0}, {3, 2, 1}, {1, 2, 3}};
    Matrix<float> m2{3, 3, data2};

    Matrix<float> m3 = m1+m2;

    std::vector<std::vector<float>> data_ref{{2, 2, 3}, {6, 4, 2}, {1, 2, 4}};
    Matrix<float> m_ref{3, 3, data_ref};

    ASSERT_EQ(m3, m_ref);
}

TEST(SubtractinMatricesTest, TestingMatrix_subtr)
{
    std::vector<std::vector<float>> data1{{1, 2, 3}, {3, 2, 1}, {0, 0, 1}};
    Matrix<float> m1{3, 3, data1};

    std::vector<std::vector<float>> data2{{1, 0, 0}, {3, 2, 1}, {1, 2, 3}};
    Matrix<float> m2{3, 3, data2};

    Matrix<float> m3 = m1-m2;

    std::vector<std::vector<float>> data_ref{{0, 2, 3}, {0, 0, 0}, {-1, -2, -2}};
    Matrix<float> m_ref{3, 3, data_ref};

    ASSERT_EQ(m3, m_ref);
}

TEST(DivideByScalarMatrixTest, TestingMatrix_div_by_scalar)
{
    std::vector<std::vector<float>> data1{{4, 2, 6}, {0, -2, 1}, {2, -8, 4}};
    Matrix<float> m1{3, 3, data1};

    Matrix<float> m3 = m1 / 2.0f;

    std::vector<std::vector<float>> data_ref{{2, 1, 3}, {0, -1, 0.5}, {1, -4, 2}};
    Matrix<float> m_ref{3, 3, data_ref};

    ASSERT_EQ(m3, m_ref);
}

TEST(MultiplyByScalarMatrixTest, TestingMatrix_multi_by_scalar)
{
    std::vector<std::vector<float>> data1{{4, 2, 6}, {0, -2, 1}, {2, -8, 4}};
    Matrix<float> m1{3, 3, data1};

    Matrix<float> m3 = m1 * 2.0f;

    std::vector<std::vector<float>> data_ref{{8, 4, 12}, {0, -4, 2}, {4, -16, 8}};
    Matrix<float> m_ref{3, 3, data_ref};

    ASSERT_EQ(m3, m_ref);
}

TEST(IdentityMatrixTest, TestingIdentityMatrix)
{
     Matrix<float> m1{3, 3};
     m1.I();

     std::vector<std::vector<float>> data_ref{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
     Matrix<float> m_ref{3, 3, data_ref};

     ASSERT_EQ(m1, m_ref);
}

TEST(MultiplyMatricesTest, TestingMatrices_multi)
{
     std::vector<std::vector<float>> data1{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}};
     std::vector<std::vector<float>> data2{{-2, 1, 2, 3}, {3, 2, 1, -1}, {4, 3, 6, 5}, {1, 2, 7, 8}};

     Matrix<float> m1{4, 4, data1};
     Matrix<float> m2{4, 4, data2};
     Matrix<float> m3 = m1.mul(m2);

     std::vector<std::vector<float>> data_ref1{{20, 22, 50, 48}, {44, 54, 114, 108}, {40, 58, 110, 102}, {16, 26, 46, 42}};
     Matrix<float> m_ref1{4, 4, data_ref1};

     ASSERT_EQ(m3, m_ref1);

     std::vector<std::vector<float>> data3{{1, 2, 3}, {5, 6, 7}, {9, 8, 7}};
     std::vector<std::vector<float>> data4{{-2, 1}, {3, 2}, {4, 3}};
     Matrix<float> m4{3, 3, data3};
     Matrix<float> m5{3, 2, data4};
     Matrix<float> m6 = m4.mul(m5);

     std::vector<std::vector<float>> data_ref2{{16, 14}, {36, 38}, {34, 46}};
     Matrix<float> m_ref2{3, 2, data_ref2};
     ASSERT_EQ(m6, m_ref2);

     std::vector<std::vector<float>> data5{{1, 2, 3, 4}, {2, 4, 4, 2}, {8, 6, 4 ,1}, {0, 0, 0, 1}};
     Matrix<float> m7{4, 4, data5};
     Vector<float> vec{1, 2, 3, 1};

     std::vector<std::vector<float>> data_ref3{{18}, {24}, {33}, {1}};
     Matrix<float> m_ref3{4, 1, data_ref3};
     Matrix<float> m8 = m7.mul(vec);

     ASSERT_EQ(m8, m_ref3);
}

//TEST(EqualityMatricesTest, TestingMatrices_equal)
//{

//}

TEST(TransposeMatrixTest, TestingMatrix_transpose)
{
     std::vector<std::vector<float>> data1{{0, 9, 3, 0}, {9, 8, 0, 8}, {1, 8, 5, 3}, {0, 0 ,5, 8}};
     Matrix<float> m1{4, 4, data1};
     Matrix<float> m2 = m1.tr();

     std::vector<std::vector<float>> data_ref1{{0, 9, 1, 0}, {9, 8, 8, 0}, {3, 0, 5, 5}, {0, 8, 3, 8}};
     Matrix<float> m_ref1{4, 4, data_ref1};
     ASSERT_EQ(m2, m_ref1);

     std::vector<std::vector<float>> data2{{0, 9, 3}, {9, 8, 0}, {1, 8, 5}, {0, 0 ,5}};
     Matrix<float> m3{4, 3, data2};
     Matrix<float> m4 = m3.tr();

     std::vector<std::vector<float>> data_ref2{{0, 9, 1, 0}, {9, 8, 8, 0}, {3, 0, 5, 5}};
     Matrix<float> m_ref2{3, 4, data_ref2};
     ASSERT_EQ(m4, m_ref2);
}

//TEST(invertMatrixTest, TestingMatrix_invert)
//{

//}

TEST(DeterminantMatrixTest, TestingMatrix_det)
{
     std::vector<std::vector<float>> data1{{1, 5}, {-3, 2}};
     Matrix<float> m1{2, 2, data1};
     float det = m1.det_2x2();
     ASSERT_FLOAT_EQ(det, 17.0f);
}

//TEST(MinorMatrixTest, TestingMatrix_comp_minor)
//{

//}

//TEST(CofactorMatrixTest, TestingMatrix_comp_cofactor)
//{

//}

TEST(BlockMatrixTest, TestingMatrix_block)
{
     std::vector<std::vector<float>> data1{{1, 5, 0}, {-3, 2, 7}, {0, 6, -3}};
     Matrix<float> m1{3, 3, data1};
     Matrix<float> sub_m1 = m1.block(2, 2, 1, 0);

     std::vector<std::vector<float>> data_ref1{{-3, 2}, {0, 6}};
     Matrix<float> m_ref1{2, 2, data_ref1};
     ASSERT_EQ(sub_m1, m_ref1);
}

TEST(SubMatrixTest, TestingMatrix_submatrix)
{
     std::vector<std::vector<float>> data1{{1, 5, 0}, {-3, 2, 7}, {0, 6, -3}};
     Matrix<float> m1{3, 3, data1};
     Matrix<float> sub_m1 = m1.submatrix(0, 2);

     std::vector<std::vector<float>> data_ref1{{-3, 2}, {0, 6}};
     Matrix<float> m_ref1{2, 2, data_ref1};
     ASSERT_EQ(sub_m1, m_ref1);

     std::vector<std::vector<float>> data2{{-6, 1, 1, 6}, {-8, 5, 8, 6}, {-1, 0, 8, 2}, {-7, 1, -1, 1}};
     Matrix<float> m2{4, 4, data2};
     Matrix<float> sub_m2 = m2.submatrix(2, 1);

     std::vector<std::vector<float>> data_ref2{{-6, 1, 6}, {-8, 8, 6}, {-7, -1, 1}};
     Matrix<float> m_ref2{3, 3, data_ref2};
     ASSERT_EQ(sub_m2, m_ref2);
}



int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
