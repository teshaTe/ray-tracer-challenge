cmake_minimum_required(VERSION 3.16)
project(RayTracer-materials LANGUAGES CXX)

####################### ESSENTIAL INCLUDES/PROJECT FILES ##########################

set(MATERIALS_SRC  phong_material.cpp)

set(MATERIALS_HEADERS  phong_material.h)

############################ CREATING EXECUTABLES TO RUN ##########################

add_library(materials_lib ${MATERIALS_SRC} ${MATERIALS_HEADERS})
target_link_libraries(materials_lib core_lib)
