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


add_executable(vector_test vector_container_tests.cpp)
target_include_directories(vector_test PUBLIC "${PROJECT_ROOT_DIR}/Containers")
target_link_libraries(vector_test PRIVATE GTest::GTest)
add_test(vector_gtest vector_test)

add_executable(matrix_test matrix_container_tests.cpp)
target_include_directories(matrix_test PUBLIC "${PROJECT_ROOT_DIR}/Containers")
target_link_libraries(matrix_test PRIVATE GTest::GTest)
add_test(matrix_gtest matrix_test)

add_executable(color_test color_container_tests.cpp)
target_include_directories(color_test PUBLIC "${PROJECT_ROOT_DIR}/Containers")
target_link_libraries(color_test PRIVATE GTest::GTest)
add_test(color_gtest color_test)

add_executable(canvas_test canvas_tests.cpp)
target_include_directories(canvas_test PUBLIC "${PROJECT_ROOT_DIR}/RayTracer" "${PROJECT_ROOT_DIR}")
target_link_libraries(canvas_test PRIVATE GTest::GTest)
add_test(canvas_gtest canvas_test)

add_executable(matrix_utils_test matrix_utilities_tests.cpp)
target_include_directories(matrix_utils_test PUBLIC "${PROJECT_ROOT_DIR}/RayTracer" "${PROJECT_ROOT_DIR}")
target_link_libraries(matrix_utils_test PRIVATE GTest::GTest)
add_test(matrix_utils_gtest matrix_utils_test)
