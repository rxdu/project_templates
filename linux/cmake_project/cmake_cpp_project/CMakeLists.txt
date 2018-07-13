cmake_minimum_required(VERSION 2.8.11)
project(cmake_cpp_template)

# cmake module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

# automatically build LCM types.  This also defines a number of CMake
# variables, see cmake/lcmtypes.cmake for details
# include(cmake/lcmtypes.cmake)
# lcmtypes_build()

## Chosse build type
# set(CMAKE_BUILD_TYPE Debug)

## Optionally built modules: on/off
set(ENABLE_LOGGING off)
set(BUILD_TESTS off)

## Add sub source directories
add_subdirectory(examples)
add_subdirectory(lightviz)
add_subdirectory(interface)
add_subdirectory(libraries)

## Add test source directories
if(BUILD_TESTS)
    add_subdirectory(gtests)
endif()
