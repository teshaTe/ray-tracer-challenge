cmake_minimum_required(VERSION 3.16)
project(RayTracer-project LANGUAGES CXX)

########################### GLOBAL CMAKE PROPERTIES ###############################

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 17)

########################### AVAILABLE PROJECT OPTIONS #############################


####################### ESSENTIAL INCLUDES/PROJECT FILES ##########################

set(CONTAINERS Containers/Vector.hpp
               Containers/Matrix.hpp
               Containers/Color.hpp)

enable_testing()
add_subdirectory(tests)

############################ CREATING EXECUTABLES TO RUN ##########################

add_executable(ProjectileSample "${PROJECT_ROOT_DIR}/Samples/projectile_gen_sample.cpp" ${CONTAINERS})
add_executable(RayTracer ray_tracer.cpp ${CONTAINERS})
