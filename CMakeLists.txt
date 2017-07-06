cmake_minimum_required(VERSION 2.8.11)

# Options
option(build_tests "Build unit tests" OFF)

# Handling of relative directories by link_directories()
cmake_policy(SET CMP0015 NEW) 

project( "j-math" )

################################################################
# External libraries 
################################################################

# -

################################################################
# Project structure
################################################################

set(PROJECT_LIB_NAME "${PROJECT_NAME}-lib")
set(PROJECT_MAIN_NAME "${PROJECT_NAME}-main")
set(PROJECT_TEST_NAME "${PROJECT_NAME}-test")
			 
set(SRC_LIB src/numeric_comparison.h
			src/shape_types.h
			src/sphere.h
			src/vector.h
			src/point.h
			src/line.h
			src/plane.h
			src/coordinate_frame.h
			src/pi.h
)

add_library( ${PROJECT_LIB_NAME} ${SRC_LIB})
set_target_properties(${PROJECT_LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)
add_executable( ${PROJECT_MAIN_NAME} src/main.cc )
# target_link_libraries( ${PROJECT_MAIN_NAME} ${PROJECT_LIB_NAME} )

################################################################
# Unit tests
################################################################
if (build_tests)
	# GTest
	configure_file(CMakeLists.gtest.txt googletest-download/CMakeLists.txt)
	execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
	  RESULT_VARIABLE result
	  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
	if(result)
	  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
	endif()
	execute_process(COMMAND ${CMAKE_COMMAND} --build .
	  RESULT_VARIABLE result
	  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
	if(result)
	  message(FATAL_ERROR "Build step for googletest failed: ${result}")
	endif()
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # Prevent overriding the parent project's compiler/linker settings on Windows
	add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
					 ${CMAKE_BINARY_DIR}/googletest-build)

	# Unit test project
	set(SRC_TEST    test/main.cc
					test/numeric_comparison_test.cc
					test/coordinate_frame_test.cc
					test/vector_test.cc
					test/point_test.cc
					test/line_test.cc
					test/plane_test.cc
					test/sphere_test.cc
	)
	add_executable( ${PROJECT_TEST_NAME} ${SRC_TEST} )
	target_link_libraries( ${PROJECT_TEST_NAME} gtest gtest_main)
	# target_link_libraries( ${PROJECT_TEST_NAME} ${PROJECT_LIB_NAME} )
endif (build_tests)