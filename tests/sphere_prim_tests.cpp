#include <gtest/gtest.h>
#include "Shapes/Sphere.h"
#include "Core/Ray.hpp"
#include "Core/DataTypes.hpp"


using namespace ray_tracer;

TEST(CreatingSphereTest, TestingSphereCreation)
{
    Vector<float> origin1{0, 0, 0};
    shapes::Sphere sphere1{origin1, 1.0, 1};

    ASSERT_FLOAT_EQ(sphere1.get_radius(), 1.0);
    ASSERT_EQ(sphere1.get_origin(), origin1);
    ASSERT_EQ(sphere1.get_id(), 1);
}

TEST(SphereRayIntersectionTest, TestingRayIntersection)
{
    shapes::Sphere sphere1{Vector<float>{0, 0, 0}, 1.0, 1};
    Ray ray1{Vector<float>{0, 0, -5}, Vector<float>{0, 0, 1}};
    std::vector<types::intersection> intersections1 = sphere1.intersect(ray1);

    ASSERT_EQ(intersections1.size(), 2);
    ASSERT_EQ(intersections1[0].obj_type, "sphere");
    ASSERT_EQ(intersections1[1].obj_type, "sphere");
    ASSERT_EQ(intersections1[0].t, 4);
    ASSERT_EQ(intersections1[1].t, 6);

    Ray ray2{Vector<float>{0, 1, -5}, Vector<float>{0, 0, 1}};
    std::vector<types::intersection> intersections2 = sphere1.intersect(ray2);

    ASSERT_EQ(intersections2.size(), 2);
    ASSERT_EQ(intersections2[0].t, 5);
    ASSERT_EQ(intersections2[1].t, 5);

    Ray ray3{Vector<float>{0, 0, 0}, Vector<float>{0, 0, 1}};
    std::vector<types::intersection> intersections3 = sphere1.intersect(ray3);

    ASSERT_EQ(intersections3.size(), 2);
    ASSERT_EQ(intersections3[0].t, -1.0);
    ASSERT_EQ(intersections3[1].t, 1.0);

    Ray ray4{Vector<float>{0, 0, 5}, Vector<float>{0, 0, 1}};
    std::vector<types::intersection> intersections4 = sphere1.intersect(ray4);

    ASSERT_EQ(intersections4.size(), 2);
    ASSERT_EQ(intersections4[0].t, -6);
    ASSERT_EQ(intersections4[1].t, -4);

    Ray ray5{Vector<float>{0, 2, -5}, Vector<float>{0, 0, 1}};
    std::vector<types::intersection> intersections5 = sphere1.intersect(ray5);

    ASSERT_EQ(intersections5.size(), 0);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
