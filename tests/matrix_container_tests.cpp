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
    Matrix<float> m2{2, 2, &data};
    ASSERT_FLOAT_EQ(m2(0, 0), 1.0f);
    ASSERT_FLOAT_EQ(m2(0, 1), 2.0f);
    ASSERT_FLOAT_EQ(m2(1, 0), 3.0f);
    ASSERT_FLOAT_EQ(m2(1, 1), 4.0f);
}

TEST(AddingMatrixTest, TestingMatrix_sum)
{
    std::vector<std::vector<float>> data1{{1, 2, 3}, {3, 2, 1}, {0, 0, 1}};
    Matrix<float> m1{3, 3, &data1};

    std::vector<std::vector<float>> data2{{1, 0, 0}, {3, 2, 1}, {1, 2, 3}};
    Matrix<float> m2{3, 3, &data2};

    Matrix<float> m3 = m1+m2;

    std::vector<std::vector<float>> data_ref{{2, 2, 3}, {6, 4, 2}, {1, 2, 4}};
    Matrix<float> m_ref{3, 3, &data_ref};

    ASSERT_EQ(m3, m_ref);
}

TEST(SubtractinMatricesTest, TestingMatrix_subtr)
{
    std::vector<std::vector<float>> data1{{1, 2, 3}, {3, 2, 1}, {0, 0, 1}};
    Matrix<float> m1{3, 3, &data1};

    std::vector<std::vector<float>> data2{{1, 0, 0}, {3, 2, 1}, {1, 2, 3}};
    Matrix<float> m2{3, 3, &data2};

    Matrix<float> m3 = m1-m2;

    std::vector<std::vector<float>> data_ref{{0, 2, 3}, {0, 0, 0}, {-1, -2, -2}};
    Matrix<float> m_ref{3, 3, &data_ref};

    ASSERT_EQ(m3, m_ref);
}

TEST(DivideByScalarMatrixTest, TestingMatrix_div_by_scalar)
{
    std::vector<std::vector<float>> data1{{4, 2, 6}, {0, -2, 1}, {2, -8, 4}};
    Matrix<float> m1{3, 3, &data1};

    Matrix<float> m3 = m1 / 2.0f;

    std::vector<std::vector<float>> data_ref{{2, 1, 3}, {0, -1, 0.5}, {1, -4, 2}};
    Matrix<float> m_ref{3, 3, &data_ref};

    ASSERT_EQ(m3, m_ref);
}

TEST(MultiplyByScalarMatrixTest, TestingMatrix_multi_by_scalar)
{
    std::vector<std::vector<float>> data1{{4, 2, 6}, {0, -2, 1}, {2, -8, 4}};
    Matrix<float> m1{3, 3, &data1};

    Matrix<float> m3 = m1 * 2.0f;

    std::vector<std::vector<float>> data_ref{{8, 4, 12}, {0, -4, 2}, {4, -16, 8}};
    Matrix<float> m_ref{3, 3, &data_ref};

    ASSERT_EQ(m3, m_ref);
}

TEST(IdentityMatrixTest, TestingIdentityMatrix)
{
     Matrix<float> m1{3, 3};
     m1.I();

     std::vector<std::vector<float>> data_ref{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
     Matrix<float> m_ref{3, 3, &data_ref};

     ASSERT_EQ(m1, m_ref);
}

//TEST(MultiplyMatricesTest, TestingMatrices_multi)
//{

//}

//TEST(EqualityMatricesTest, TestingMatrices_equal)
//{

//}

//TEST(TransposeMatrixTest, TestingMatrix_transpose)
//{

//}

//TEST(invertMatrixTest, TestingMatrix_invert)
//{

//}

//TEST(DeterminantMatrixTest, TestingMatrix_det)
//{

//}

//TEST(MinorMatrixTest, TestingMatrix_comp_minor)
//{

//}

//TEST(CofactorMatrixTest, TestingMatrix_comp_cofactor)
//{

//}

//TEST(BlockMatrixTest, TestingMatrix_block)
//{

//}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
