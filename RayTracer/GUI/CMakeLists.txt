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

set(SHAPES_SRC  #Shapes/shape.cpp
                Shapes/sphere.cpp)

set(SHAPES_HEADERS  #Shapes/shape.h
                    Shapes/sphere.h)

set(RAYTRACER_HEADERS RayTracer/Canvas.hpp
                      RayTracer/MatrixUtils.hpp
                      RayTracer/RayTracer.h
                      RayTracer/Ray.hpp
                      RayTracer/DataTypes.hpp)

set(RAYTRACER_SRC  RayTracer/RayTracer.cpp)

enable_testing()
add_subdirectory(tests)
add_subdirectory(Shapes)

############################ CREATING EXECUTABLES TO RUN ##########################

# add_executable(ProjectileSample "${PROJECT_ROOT_DIR}/Samples/projectile_gen_sample.cpp" ${CONTAINERS} ${RAYTRACER_SOURCE})
# add_executable(ClockSample "${PROJECT_ROOT_DIR}/Samples/clock_drawing_sample.cpp" ${CONTAINERS} ${RAYTRACER_SOURCE})

add_library(ray_tracer_lib ${CONTAINERS} ${RAYTRACER_SRC} ${RAYTRACER_HEADERS} ${SHAPES_SRC} ${SHAPES_HEADERS})
add_executable(ray_tracer ray_tracer.cpp)
target_link_libraries(ray_tracer ray_tracer_lib)
