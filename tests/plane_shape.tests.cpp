#include "math.h"

#include <gtest/gtest.h>

#include "Shapes/Plane.h"
#include "Core/Ray.hpp"
#include "Core/DataTypes.hpp"
#include "Core/Material.hpp"
#include "Core/MatrixUtils.hpp"


using namespace ray_tracer;

TEST(CreatingPlaneTest, TestingPlaneCreation)
{
    shapes::Plane plane{1};
    ASSERT_EQ(plane.get_id(), 1);
}

TEST(PlaneRayIntersectionTest, TestingPlaneRayIntersection)
{
    shapes::Plane plane1{1};
    Ray ray1{Vector<float>{0, 10, 0}, Vector<float>{0, 0, 1}};
    std::vector<types::intersection> intersections1 = plane1.intersect(ray1);
    ASSERT_EQ(intersections1.size(), 0);

    Ray ray2{Vector<float>{0, 0, 0}, Vector<float>{0, 0, 1}};
    std::vector<types::intersection> intersections2 = plane1.intersect(ray2);
    ASSERT_EQ(intersections2.size(), 0);

    Ray ray3{Vector<float>{0, 1, 0}, Vector<float>{0, -1, 0}};
    std::vector<types::intersection> intersections3 = plane1.intersect(ray3);
    ASSERT_EQ(intersections3.size(), 1);
    ASSERT_EQ(intersections3[0].t, 1.0);

    Ray ray4{Vector<float>{0, -1, 0}, Vector<float>{0, 1, 0}};
    std::vector<types::intersection> intersections4 = plane1.intersect(ray4);
    ASSERT_EQ(intersections4.size(), 1);
    ASSERT_EQ(intersections4[0].t, 1.0);
}

TEST(PlaneTransformmTest, TestingPlaneTransform)
{
    shapes::Plane plane1{1};
    MatrixUtlities mat_utils{};
    Matrix<float> tr = mat_utils.translation_mat(2, 3, 4);
    plane1.transform(tr);

    std::vector<std::vector<float>> tr1{{1, 0, 0, 2}, {0, 1, 0, 3}, {0, 0, 1, 4}, {0, 0, 0, 1}};
    Matrix<float> transform_ref{4, 4, tr1};
    ASSERT_EQ(plane1.get_transform(), transform_ref);
}

TEST(PlaneNormalComputationTest, TestingPlaneNormalComputation)
{
    shapes::Plane plane(1);
    Vector<float> n1 = plane.get_normal(Vector<float>{0, 0, 0});
    Vector<float> n2 = plane.get_normal(Vector<float>{10, 0, -100});
    Vector<float> n3 = plane.get_normal(Vector<float>{-5, 0, 150});

    Vector<float> n_ref{0, 1, 0};
    ASSERT_EQ(n1, n_ref);
    ASSERT_EQ(n2, n_ref);
    ASSERT_EQ(n3, n_ref);
}

TEST(PlaneMaterialAssignmentTest, TestingPlaneMaterialAssignment)
{
    materials::BaseMaterial mat1;
    mat1.color = Color<float>{1, 1, 1};
    mat1.ambient = 0.1;
    mat1.diffuse = 0.9;
    mat1.specular = 0.9;
    mat1.shininess = 200.0;

    shapes::Plane plane(1);
    plane.set_material(mat1);

    materials::BaseMaterial mat_test = plane.get_assigned_material();
    ASSERT_EQ(mat1, mat_test);
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
