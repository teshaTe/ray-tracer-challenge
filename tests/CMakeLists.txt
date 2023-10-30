cmake_minimum_required(VERSION 3.16)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)


add_executable(vector_test vector_container.tests.cpp)
target_include_directories(vector_test PUBLIC "${PROJECT_ROOT_DIR}/Containers")
target_link_libraries(vector_test PRIVATE GTest::GTest)
add_test(vector_gtest vector_test)

add_executable(matrix_test matrix_container.tests.cpp)
target_include_directories(matrix_test PUBLIC "${PROJECT_ROOT_DIR}/Containers")
target_link_libraries(matrix_test PRIVATE GTest::GTest)
add_test(matrix_gtest matrix_test)

add_executable(color_test color_container.tests.cpp)
target_include_directories(color_test PUBLIC "${PROJECT_ROOT_DIR}/Containers")
target_link_libraries(color_test PRIVATE GTest::GTest)
add_test(color_gtest color_test)

add_executable(canvas_test canvas_functionality.tests.cpp)
target_include_directories(canvas_test PUBLIC "${PROJECT_ROOT_DIR}/RayTracer" "${PROJECT_ROOT_DIR}")
target_link_libraries(canvas_test PRIVATE GTest::GTest core_lib)
add_test(canvas_gtest canvas_test)

add_executable(matrix_utils_test matrix_utilities.tests.cpp)
target_include_directories(matrix_utils_test PUBLIC "${PROJECT_ROOT_DIR}/RayTracer" "${PROJECT_ROOT_DIR}")
target_link_libraries(matrix_utils_test PRIVATE GTest::GTest)
add_test(matrix_utils_gtest matrix_utils_test)

add_executable(ray_creation_test ray_functionality.tests.cpp)
target_include_directories(ray_creation_test PUBLIC "${PROJECT_ROOT_DIR}/RayTracer" "${PROJECT_ROOT_DIR}")
target_link_libraries(ray_creation_test PRIVATE GTest::GTest)
add_test(ray_creation_gtest ray_creation_test)

add_executable(sphere_prim_test sphere_shape.tests.cpp)
target_include_directories(sphere_prim_test PUBLIC "${PROJECT_ROOT_DIR}/RayTracer" "${PROJECT_ROOT_DIR}")
target_link_libraries(sphere_prim_test PRIVATE GTest::GTest shapes_lib)
add_test(sphere_prim_gtest sphere_prim_test)

add_executable(ray_tracer_test shapes_functionality.tests.cpp)
target_include_directories(ray_tracer_test PUBLIC "${PROJECT_ROOT_DIR}/RayTracer" "${PROJECT_ROOT_DIR}")
target_link_libraries(ray_tracer_test PRIVATE GTest::GTest)
add_test(ray_tracer_gtest ray_tracer_test)
