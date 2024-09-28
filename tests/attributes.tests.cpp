#include "math.h"

#include <gtest/gtest.h>

#include "Containers/Vector.hpp"
#include "Core/DataTypes.hpp"


using namespace ray_tracer;


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
