cmake_minimum_required(VERSION 3.16)
project(RayTracer-project LANGUAGES CXX)

########################### GLOBAL CMAKE PROPERTIES ###############################

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 20)

########################### AVAILABLE PROJECT OPTIONS #############################


####################### ESSENTIAL INCLUDES/PROJECT FILES ##########################

set(CONTAINERS Containers/Vector.hpp
               Containers/Matrix.hpp
               Containers/Color.hpp)

set(RAYTRACER_SOURCE RayTracer/Canvas.hpp
                     RayTracer/MatrixUtils.hpp)

set(RAYTRACER_HEADERS )

enable_testing()
add_subdirectory(tests)

############################ CREATING EXECUTABLES TO RUN ##########################

add_executable(ProjectileSample "${PROJECT_ROOT_DIR}/Samples/projectile_gen_sample.cpp" ${CONTAINERS} ${RAYTRACER_SOURCE})
add_executable(ClockSample "${PROJECT_ROOT_DIR}/Samples/clock_drawing_sample.cpp" ${CONTAINERS} ${RAYTRACER_SOURCE})

add_executable(RayTracer ray_tracer.cpp ${CONTAINERS} ${RAYTRACER_SOURCE} ${RAYTRACER_HEADERS})
