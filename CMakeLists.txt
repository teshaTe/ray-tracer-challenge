cmake_minimum_required(VERSION 3.10)
project(AddressBookPrj)

########################## GLOBAL CMAKE PROPERTIES ########################

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 17)

####################### ESSENTIAL INCLUDES/LINKS/SOUTCES ##########################
set(CONTAINERS Containers/Vector.hpp
               Containers/Matrix.hpp)

#set(SOURCES src/AddressBook.cpp)

add_executable(RayTracer ray_tracer.cpp ${CONTAINERS})
