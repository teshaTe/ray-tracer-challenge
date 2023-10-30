cmake_minimum_required(VERSION 3.16)
project(RayTracer-core LANGUAGES CXX)

####################### ESSENTIAL INCLUDES/PROJECT FILES ##########################

set(RAYTRACER_HEADERS Canvas.hpp
                      MatrixUtils.hpp
                      RayTracer.h
                      Ray.hpp
                      DataTypes.hpp
                      Shape.h)

set(RAYTRACER_SRC  RayTracer.cpp
                   Shape.cpp)

############################ CREATING EXECUTABLES TO RUN ##########################

add_library(core_lib ${RAYTRACER_SRC} ${RAYTRACER_HEADERS})
target_link_libraries(core_lib shapes_lib)
