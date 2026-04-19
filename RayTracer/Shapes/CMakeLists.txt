cmake_minimum_required(VERSION 3.16)
project(RayTracer-shapes LANGUAGES CXX)

####################### ESSENTIAL INCLUDES/PROJECT FILES ##########################

set(SHAPES_SRC  Sphere.cpp
                Plane.cpp
    )

set(SHAPES_HEADERS  Sphere.h
                    Plane.h
    )

############################ CREATING EXECUTABLES TO RUN ##########################

add_library(shapes_lib ${SHAPES_SRC} ${SHAPES_HEADERS})
target_link_libraries(shapes_lib core_lib)
