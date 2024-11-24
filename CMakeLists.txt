cmake_minimum_required(VERSION 3.16)
project(RayTracer-project LANGUAGES CXX)

########################### GLOBAL CMAKE PROPERTIES ###############################

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 17)

########################### AVAILABLE PROJECT OPTIONS #############################


####################### ESSENTIAL INCLUDES/PROJECT FILES ##########################

include_directories("${PROJECT_ROOT_DIR}/RayTracer")

enable_testing()
add_subdirectory(tests)
add_subdirectory(RayTracer)

############################ CREATING EXECUTABLES TO RUN ##########################

add_executable(ProjectileSample "${PROJECT_ROOT_DIR}/Samples/projectile_gen_sample.cpp" ${CONTAINERS} ${RAYTRACER_SOURCE})
add_executable(ClockSample "${PROJECT_ROOT_DIR}/Samples/clock_drawing_sample.cpp" ${CONTAINERS} ${RAYTRACER_SOURCE})
add_executable(SphereSample "${PROJECT_ROOT_DIR}/Samples/sphere_rendering_sample.cpp" ${CONTAINERS} ${RAYTRACER_SOURCE})
target_link_libraries(SphereSample core_lib)
