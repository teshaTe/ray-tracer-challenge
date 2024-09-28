#include "math.h"

#include <gtest/gtest.h>

#include "Shapes/sphere.h"
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

TEST(ObjectHitCheckTest, TestingRayHit)
{
    shapes::Sphere sphere1{Vector<float>{0, 0, 0}, 1.0, 1};
    std::vector<types::intersection> intersections1(2);
    intersections1[0].t = 1;
    intersections1[1].t = 2;

    float hit1;
    bool res1 = sphere1.get_surface_hit(intersections1, &hit1);
    ASSERT_EQ(res1, true);
    ASSERT_FLOAT_EQ(hit1, 1);

    std::vector<types::intersection> intersections2(2);
    intersections2[0].t = -1;
    intersections2[1].t = 1;

    float hit2;
    bool res2 = sphere1.get_surface_hit(intersections2, &hit2);
    ASSERT_EQ(res2, true);
    ASSERT_FLOAT_EQ(hit2, 1);

    std::vector<types::intersection> intersections3(2);
    intersections3[0].t = -2;
    intersections3[1].t = -1;

    float hit3;
    bool res3 = sphere1.get_surface_hit(intersections3, &hit3);
    ASSERT_EQ(res3, false);
    ASSERT_FLOAT_EQ(hit3, -1.0f);

    std::vector<types::intersection> intersections4(4);
    intersections4[0].t = 5;
    intersections4[1].t = 7;
    intersections4[2].t = -3;
    intersections4[3].t = 2;

    float hit4;
    bool res4 = sphere1.get_surface_hit(intersections4, &hit4);
    ASSERT_EQ(res4, true);
    ASSERT_FLOAT_EQ(hit4, 2.0f);
}


TEST(SphereTransformmTest, TestingSphereTransform)
{
    shapes::Sphere sphere1{Vector<float>{0, 0, 0}, 1.0, 1};
    Matrix<float> R1{3, 3};
    R1.I();
    Vector<float> T1{2, 3, 4};

    std::vector<std::vector<float>> tr1{{1, 0, 0, 2}, {0, 1, 0, 3}, {0, 0, 1, 4}, {0, 0, 0, 1}};
    Matrix<float> transform_ref{4, 4, tr1};
    sphere1.transform(T1, R1);
    ASSERT_EQ(sphere1.get_translation(), T1);
    ASSERT_EQ(sphere1.get_rotation_matrix(), R1);
    ASSERT_EQ(sphere1.get_transform(), transform_ref);
}

TEST(SphereScaledRayIntersectionTest, TestingScaledSphereRayIntersection)
{
    Ray ray{Vector<float>{0, 0, -5}, Vector<float>{0, 0, 1}};
    shapes::Sphere sphere(Vector<float>{0, 0, 0}, 1.0, 1);
    sphere.scale(Vector<float>{2, 2, 2});

    Matrix<float> ray_tr_mat = sphere.get_transform().inv();
    Vector<float> ray_orig = ray_tr_mat.mul(ray.get_origin()).to_vec_1x3();
    Vector<float> ray_dir = ray_tr_mat.mul(ray.get_direction()).to_vec_1x3();

    Ray new_ray{ray_orig, ray_dir};

    std::vector<types::intersection> intersections = sphere.intersect(new_ray);

    ASSERT_EQ(intersections.size(), 2);
    ASSERT_EQ(intersections[0].t, 3);
    ASSERT_EQ(intersections[1].t, 7);
}

TEST(SphereTranslatedRayIntersectionTest, TestingTranslatedSphereRayIntersection)
{
    Ray ray{Vector<float>{0, 0, -5}, Vector<float>{0, 0, 1}};
    shapes::Sphere sphere(Vector<float>{0, 0, 0}, 1.0, 1);
    Matrix<float> R1{3, 3};
    R1.I();
    Vector<float> T1{5, 0, 0};

    sphere.transform(T1, R1);

    Matrix<float> ray_tr_mat = sphere.get_transform().inv();
    Vector<float> ray_orig = ray_tr_mat.mul(ray.get_origin()).to_vec_1x3();
    Vector<float> ray_dir = ray_tr_mat.mul(ray.get_direction()).to_vec_1x3();

    Ray new_ray{ray_orig, ray_dir};

    std::vector<types::intersection> intersections = sphere.intersect(new_ray);

    ASSERT_EQ(intersections.size(), 0);
}

TEST(SphereNormalComputationTest, TestingNormalComputation)
{
    shapes::Sphere sphere1(Vector<float>{0, 0, 0}, 1.0, 1);
    Vector<float> n1 = sphere1.get_normal(Vector<float>{1, 0, 0});
    Vector<float> n1_ref{1, 0, 0};
    ASSERT_EQ(n1, n1_ref);

    Vector<float> n2 = sphere1.get_normal(Vector<float>{0, 1, 0});
    Vector<float> n2_ref{0, 1, 0};
    ASSERT_EQ(n2, n2_ref);

    Vector<float> n3 = sphere1.get_normal(Vector<float>{0, 0, 1});
    Vector<float> n3_ref{0, 0, 1};
    ASSERT_EQ(n3, n3_ref);

    float val1 = std::sqrt(3.0)/3.0;
    Vector<float> n4 = sphere1.get_normal(Vector<float>{val1, val1, val1});

    float magn1 = n4.magnitude();
    ASSERT_FLOAT_EQ(magn1, 1.0);

    std::vector<std::vector<float>> tr1{{1, 0, 0, 0}, {0, 1, 0, 1}, {0, 0, 1, 0}, {0, 0, 0, 1}};
    Matrix<float> tr1_mat{4, 4, tr1};
    sphere1.transform(tr1_mat);
    Vector<float> n5 = sphere1.get_normal(Vector<float>{0, 1.70711, -0.70711});
    Vector<float> n5_ref{0, 0.923879, -0.382684};
    ASSERT_EQ(n5, n5_ref);

    shapes::Sphere sphere2(Vector<float>{0, 0, 0}, 1.0, 2);
    sphere2.scale(Vector<float>{1, 0.5, 1});

    MatrixUtlities mat_utils;
    Matrix<float> R = mat_utils.rotation_mat_ZAxis(M_PI/5.0);
    sphere2.transform(Vector<float>{0, 0, 0}, R);
    float val2 = std::sqrt(2.0)/2.0;
    Vector<float> n6 = sphere2.get_normal(Vector<float>{0, val2, -val2});
    Vector<float> n6_ref = Vector<float>{0, 0.97014, -0.24254};
    ASSERT_EQ(n6, n6_ref);
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
