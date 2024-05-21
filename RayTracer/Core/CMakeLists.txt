cmake_minimum_required(VERSION 3.16)
project(RayTracer-core LANGUAGES CXX)

####################### ESSENTIAL INCLUDES/PROJECT FILES ##########################

set(RAYTRACER_HEADERS Canvas.hpp
                      MatrixUtils.hpp
                      RayTracer.h
                      Ray.hpp
                      DataTypes.hpp
                      shape.h)

set(RAYTRACER_SRC  RayTracer.cpp
                   shape.cpp)

set(CONTAINERS_SRC ${PROJECT_ROOT_DIR}/RayTracer/Containers/Matrix.hpp
                   ${PROJECT_ROOT_DIR}/RayTracer/Containers/Vector.hpp
                   ${PROJECT_ROOT_DIR}/RayTracer/Containers/Color.hpp)

############################ CREATING EXECUTABLES TO RUN ##########################

add_library(core_lib ${RAYTRACER_SRC} ${RAYTRACER_HEADERS} ${CONTAINERS_SRC})
target_link_libraries(core_lib shapes_lib)
