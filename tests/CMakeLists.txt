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
