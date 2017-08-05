cmake_minimum_required(VERSION 2.8.11)

# Options
option(jmath_build_tests "Build unit tests" OFF)
option(jmath_build_main "Build main loop (can be used for quick testing)" OFF)

# Handling of relative directories by link_directories()
cmake_policy(SET CMP0015 NEW) 

project( "j-math" CXX )

################################################################
# External libraries 
################################################################

# -

################################################################
# Project structure
################################################################

add_subdirectory(lib)
if (jmath_build_tests)
	add_subdirectory(test)
endif (jmath_build_tests)
if (jmath_build_main)
	add_subdirectory(main)
endif(jmath_build_main)

################################################################
# Installing
################################################################

set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}")