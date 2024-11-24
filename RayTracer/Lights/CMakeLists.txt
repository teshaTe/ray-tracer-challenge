cmake_minimum_required(VERSION 3.16)
project(RayTracer-lights LANGUAGES CXX)

####################### ESSENTIAL INCLUDES/PROJECT FILES ##########################

set(LIGHTS_SRC  point_light.cpp)

set(LIGHTS_HEADERS  point_light.h)

############################ CREATING EXECUTABLES TO RUN ##########################

add_library(lights_lib ${LIGHTS_SRC} ${LIGHTS_HEADERS})
target_link_libraries(lights_lib core_lib)
