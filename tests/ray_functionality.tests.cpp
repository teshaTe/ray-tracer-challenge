#include <gtest/gtest.h>
#include "Core/Ray.hpp"

using namespace ray_tracer;

TEST(CreatingRayTest, TestingRayCreation)
{
    Vector<float> origin{2, 3, 4};
    Vector<float> direction{1, 0, 0};
    Ray ray(origin, direction);

    ASSERT_EQ(ray.get_origin(), origin);
    ASSERT_EQ(ray.get_direction(), direction);
}


TEST(ComputingPositionTest, TestingRayPositionComputation)
{
    Vector<float> origin{2, 3, 4};
    Vector<float> direction{1, 0, 0};
    Ray ray(origin, direction);

    Vector<float> p1 = ray.position(ray, 0);
    Vector<float> p2 = ray.position(ray, 1);
    Vector<float> p3 = ray.position(ray, -1);
    Vector<float> p4 = ray.position(ray, 2.5);

    Vector<float> p2_ref{3, 3, 4};
    Vector<float> p3_ref{1, 3, 4};
    Vector<float> p4_ref{4.5, 3, 4};

    ASSERT_EQ(p1, origin);
    ASSERT_EQ(p2, p2_ref);
    ASSERT_EQ(p3, p3_ref);
    ASSERT_EQ(p4, p4_ref);
}

TEST(TranslationTest, TestingRayTranslation)
{
    Vector<float> origin{1, 2, 3};
    Vector<float> direction{0, 1, 0};
    Ray ray(origin, direction);

    Vector<float> tr_vec{3, 4, 5};
    Ray tr_ray = ray.translate(tr_vec);

    Vector<float> orig_ref{4, 6, 8};
    ASSERT_EQ(tr_ray.get_origin(), orig_ref);
    ASSERT_EQ(tr_ray.get_direction(), ray.get_direction());
}

TEST(ScalingTest, TestingRayScaling)
{
    Vector<float> origin{1, 2, 3};
    Vector<float> direction{0, 1, 0};
    Ray ray(origin, direction);

    Vector<float> scaling_vec{2, 3, 4};
    Ray tr_ray = ray.scale(scaling_vec);

    Vector<float> orig_ref{2, 6, 12};
    Vector<float> dir_ref{0, 3, 0};

    ASSERT_EQ(tr_ray.get_origin(), orig_ref);
    ASSERT_EQ(tr_ray.get_direction(), dir_ref);
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
