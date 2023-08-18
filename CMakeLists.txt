cmake_minimum_required(VERSION 3.16)
project(RayTracer-project LANGUAGES CXX)

########################## GLOBAL CMAKE PROPERTIES ########################

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 17)

####################### ESSENTIAL INCLUDES/LINKS/SOUTCES ##########################
set(CONTAINERS Containers/Vector.hpp
               Containers/Matrix.hpp)

enable_testing()
add_subdirectory(tests)

add_executable(RayTracer ray_tracer.cpp ${CONTAINERS})
