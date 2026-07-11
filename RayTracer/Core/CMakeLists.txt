cmake_minimum_required(VERSION 3.16)
project(RayTracer-core LANGUAGES CXX)

find_package(OpenMP)
IF(OPENMP_FOUND)
   message("OpenMP was found in the system!")
   SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
ENDIF()

####################### ESSENTIAL INCLUDES/PROJECT FILES ##########################

set(RAYTRACER_HEADERS Canvas.hpp
                      Camera.h
                      MatrixUtils.hpp
                      RayTracer.h
                      Ray.hpp
                      DataTypes.hpp
                      Shape.h
                      Light.hpp
                      Material.hpp
                      Patterns.hpp
                      WorldScene.h
                  )

set(RAYTRACER_SRC  RayTracer.cpp
                   Shape.cpp
                   Camera.cpp
                   WorldScene.cpp
               )

set(CONTAINERS_SRC ${PROJECT_ROOT_DIR}/RayTracer/Containers/Matrix.hpp
                   ${PROJECT_ROOT_DIR}/RayTracer/Containers/Vector.hpp
                   ${PROJECT_ROOT_DIR}/RayTracer/Containers/Color.hpp)

############################ CREATING EXECUTABLES TO RUN ##########################

add_library(core_lib ${RAYTRACER_SRC} ${RAYTRACER_HEADERS} ${CONTAINERS_SRC})
target_link_libraries(core_lib shapes_lib OpenMP::OpenMP_CXX)
