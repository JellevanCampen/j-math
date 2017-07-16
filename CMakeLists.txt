cmake_minimum_required(VERSION 2.8.11)

# Options
option(build_tests "Build unit tests" OFF)
option(build_main "Build main loop (can be used for quick testing)" OFF)

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
if (build_tests)
	add_subdirectory(test)
endif (build_tests)
if (build_main)
	add_subdirectory(main)
endif(build_main)