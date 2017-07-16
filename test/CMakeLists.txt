set(TARGET_NAME "${PROJECT_NAME}-test")

################################################################
# GTest (downloaded from GIT)
################################################################

configure_file(CMakeLists.gtest.txt ${CMAKE_BINARY_DIR}/googletest-download/CMakeLists.txt)
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
set(SRC "")
set(SRC_MAIN 
				main.cc
)
source_group(// FILES ${SRC_MAIN})
list(APPEND SRC ${SRC_MAIN})

set(SRC_GEOMETRY 
				geometry/coordinate_frame_test.cc
				geometry/vector_test.cc
				geometry/point_test.cc
				geometry/line_test.cc
				geometry/plane_test.cc
				geometry/sphere_test.cc
)
source_group(//geometry FILES ${SRC_GEOMETRY})
list(APPEND SRC ${SRC_GEOMETRY})

set(SRC_UTILITY
				utility/numeric_comparison_test.cc
)
source_group(//utility FILES ${SRC_UTILITY})
list(APPEND SRC ${SRC_UTILITY})

add_executable( ${TARGET_NAME} ${SRC} )
target_link_libraries( ${TARGET_NAME} gtest gtest_main)
# target_link_libraries( ${PROJECT_TEST_NAME} ${PROJECT_LIB_NAME} )