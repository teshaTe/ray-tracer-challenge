#include "math.h"

#include <gtest/gtest.h>

#include "Containers/Color.hpp"
#include "Containers/Vector.hpp"
#include "Lights/point_light.h"


using namespace ray_tracer;
using namespace ray_tracer;


TEST(PointLight, TestingPointLight)
{
    const Color<float> intensity1{1, 1, 1};
    const Vector<float> plight_origin1{0, 0, 0};

    lights::PointLight plight(plight_origin1, intensity1);

    ASSERT_EQ(intensity1, plight.get_intensity());
    ASSERT_EQ(plight_origin1, plight.get_origin());

    const Color<float> intensity2{1, 0, 1};
    const Vector<float> plight_origin2{1, 0, 0};
    plight.set_intensity(intensity2);
    plight.set_origin(plight_origin2);

    ASSERT_EQ(intensity2, plight.get_intensity());
    ASSERT_EQ(plight_origin2, plight.get_origin());
}
