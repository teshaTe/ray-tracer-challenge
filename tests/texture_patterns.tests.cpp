#include <gtest/gtest.h>
#include "Containers/Color.hpp"
#include "Containers/Vector.hpp"
#include "Containers/Matrix.hpp"
#include "Core/MatrixUtils.hpp"
#include "Core/Patterns.hpp"
#include "Core/Material.hpp"
#include "Lights/point_light.h"
#include "Core/RayTracer.h"
#include "Shapes/Sphere.h"


using namespace ray_tracer;

TEST(StrippedPatternCreation, TestingStrippedPattern_creation)
{
    const Color<float> white{1, 1, 1};
    const Color<float> black{0, 0, 0};

    StripePattern pattern1{white, black};
    Color<float> col1 = pattern1.pattern_at(Vector<float>{0, 0, 0});
    Color<float> col2 = pattern1.pattern_at(Vector<float>{0, 1, 0});
    Color<float> col3 = pattern1.pattern_at(Vector<float>{0, 2, 0});

    ASSERT_EQ(col1, white);
    ASSERT_EQ(col2, white);
    ASSERT_EQ(col3, white);

    Color<float> col4 = pattern1.pattern_at(Vector<float>{0, 0, 0});
    Color<float> col5 = pattern1.pattern_at(Vector<float>{0, 0, 1});
    Color<float> col6 = pattern1.pattern_at(Vector<float>{0, 0, 2});
    ASSERT_EQ(col4, white);
    ASSERT_EQ(col5, white);
    ASSERT_EQ(col6, white);

    Color<float> col7 = pattern1.pattern_at(Vector<float>{0, 0, 0});
    Color<float> col8 = pattern1.pattern_at(Vector<float>{0.9, 0, 0});
    Color<float> col9 = pattern1.pattern_at(Vector<float>{1, 0, 0});
    Color<float> col10 = pattern1.pattern_at(Vector<float>{-0.1, 0, 0});
    Color<float> col11 = pattern1.pattern_at(Vector<float>{-1, 0, 0});
    Color<float> col12 = pattern1.pattern_at(Vector<float>{-1.1, 0, 0});
    ASSERT_EQ(col7, white);
    ASSERT_EQ(col8, white);
    ASSERT_EQ(col9, black);
    ASSERT_EQ(col10, black);
    ASSERT_EQ(col11, black);
    ASSERT_EQ(col12, white);
}

TEST(StrippedPatternMaterial, TestingStripPatern_material)
{
    const Color<float> white{1, 1, 1};
    const Color<float> black{0, 0, 0};
    StripePattern pattern1{white, black};

    materials::BaseMaterial mat1;
    mat1.pattern = &pattern1;
    mat1.ambient = 1;
    mat1.diffuse = 0;
    mat1.specular = 0;

    Vector<float> eye_dir{0, 0, -1};
    Vector<float> normal{0, 0, -1};

    lights::PointLight plight{Vector<float>{0, 0, -10}, Color<float>{1, 1, 1}, 0};
    RayTracer ray_tracer{};
    Matrix<float> tr{4, 4};
    tr.I();

    Vector<float> p1 = Vector<float>{0.9, 0, 0};
    Color<float> c1 = ray_tracer.compute_lightning(mat1, plight, p1, eye_dir, normal, false, &tr);
    Vector<float> p2 = Vector<float>{1.1, 0, 0};
    Color<float> c2 = ray_tracer.compute_lightning(mat1, plight, p2, eye_dir, normal, false, &tr);

    ASSERT_EQ(c1, white);
    ASSERT_EQ(c2, black);
}

TEST(StrippedPatternMaterialTransformation, TestingStripPatern_material_transformation)
{
    const Color<float> white{1, 1, 1};
    const Color<float> black{0, 0, 0};

    MatrixUtlities mat_utils{};
    Matrix<float> tr1{4, 4};
    tr1 = mat_utils.scaling_mat(2, 2, 2);

    StripePattern pattern1{white, black};
    Color<float> res_col1 = pattern1.pattern_at_object(tr1, Vector<float>{1.5, 0, 0});
    ASSERT_EQ(res_col1, white);

    StripePattern pattern2{white, black};
    pattern2.set_pattern_transform(tr1);
    Color<float> res_col2 = pattern2.pattern_at_object(tr1, Vector<float>{1.5, 0, 0});
    ASSERT_EQ(res_col2, white);
}


TEST(GradientPatternMaterial, TestingGradientPatternMaterial)
{
    const Color<float> white{1, 1, 1};
    const Color<float> black{0, 0, 0};

    GradientPattern grad_pattern{white, black};
    Color<float> test_val1 = grad_pattern.pattern_at(Vector<float>{0.25, 0, 0});
    Color<float> test_val2 = grad_pattern.pattern_at(Vector<float>{0.5, 0, 0});
    Color<float> test_val3 = grad_pattern.pattern_at(Vector<float>{0.75, 0, 0});

    const Color<float> ref_col1{0.75, 0.75, 0.75};
    const Color<float> ref_col2{0.5, 0.5, 0.5};
    const Color<float> ref_col3{0.25, 0.25, 0.25};

    ASSERT_EQ(test_val1, ref_col1);
    ASSERT_EQ(test_val2, ref_col2);
    ASSERT_EQ(test_val3, ref_col3);
}

TEST(RingPatternMaterial, TestingRingPatternMaterial)
{
    const Color<float> white{1, 1, 1};
    const Color<float> black{0, 0, 0};

    RingPattern ring_pattern{white, black};
    Color<float> test_val1 = ring_pattern.pattern_at(Vector<float>{0, 0, 0});
    Color<float> test_val2 = ring_pattern.pattern_at(Vector<float>{1.0, 0, 0});
    Color<float> test_val3 = ring_pattern.pattern_at(Vector<float>{0.0, 0, 1.0});
    Color<float> test_val4 = ring_pattern.pattern_at(Vector<float>{0.708, 0, 0.708});

    ASSERT_EQ(test_val1, white);
    ASSERT_EQ(test_val2, black);
    ASSERT_EQ(test_val3, black);
    ASSERT_EQ(test_val4, black);
}

TEST(CheckerBoxPatternMaterial, TestingCheckerBoxPatternMaterial)
{
    const Color<float> white{1, 1, 1};
    const Color<float> black{0, 0, 0};

    CheckerPattern checker_pattern{white, black};
    // pattern should repeat along x axis
    Color<float> test_val1 = checker_pattern.pattern_at(Vector<float>{0, 0, 0});
    Color<float> test_val2 = checker_pattern.pattern_at(Vector<float>{0.99, 0, 0});
    Color<float> test_val3 = checker_pattern.pattern_at(Vector<float>{1.01, 0, 0});

    ASSERT_EQ(test_val1, white);
    ASSERT_EQ(test_val2, white);
    ASSERT_EQ(test_val3, black);

    // pattern should repeat along y axis
    Color<float> test_val4 = checker_pattern.pattern_at(Vector<float>{0, 0, 0});
    Color<float> test_val5 = checker_pattern.pattern_at(Vector<float>{0, 0.99, 0});
    Color<float> test_val6 = checker_pattern.pattern_at(Vector<float>{0, 1.01, 0});

    ASSERT_EQ(test_val4, white);
    ASSERT_EQ(test_val5, white);
    ASSERT_EQ(test_val6, black);

    // pattern should repeat along Z axis
    Color<float> test_val7 = checker_pattern.pattern_at(Vector<float>{0, 0, 0});
    Color<float> test_val8 = checker_pattern.pattern_at(Vector<float>{0, 0, 0.99});
    Color<float> test_val9 = checker_pattern.pattern_at(Vector<float>{0, 0, 1.01});

    ASSERT_EQ(test_val7, white);
    ASSERT_EQ(test_val8, white);
    ASSERT_EQ(test_val9, black);
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
