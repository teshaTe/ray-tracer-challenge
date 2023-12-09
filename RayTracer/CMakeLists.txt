cmake_minimum_required(VERSION 3.16)
project(RayTracer-project LANGUAGES CXX)

####################### ESSENTIAL INCLUDES/PROJECT FILES ##########################
include_directories(Containers)
add_subdirectory(Shapes)
add_subdirectory(Core)
