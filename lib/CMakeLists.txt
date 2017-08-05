set(TARGET_NAME "${PROJECT_NAME}-lib")

set(SRC "")
set(SRC_GEOMETRY 
			geometry/shape_types.h
			geometry/sphere.h
			geometry/vector.h
			geometry/point.h
			geometry/line.h
			geometry/plane.h
			geometry/coordinate_frame.h
)
source_group(geometry FILES ${SRC_GEOMETRY})
list(APPEND SRC ${SRC_GEOMETRY})

set(SRC_ANALYSIS 
			analysis/sequence.h
			analysis/interpolation.h
)
source_group(analysis FILES ${SRC_ANALYSIS})
list(APPEND SRC ${SRC_ANALYSIS})

set(SRC_UTILITY 
			utility/pi.h
			utility/clamp.h
			utility/numeric_comparison.h
)
source_group(utility FILES ${SRC_UTILITY})
list(APPEND SRC ${SRC_UTILITY})

add_library( ${TARGET_NAME} ${SRC})
set_target_properties(${TARGET_NAME} PROPERTIES LINKER_LANGUAGE CXX)

################################################################
# Installing
################################################################

install(DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/analysis" DESTINATION "install/include")
install(DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/geometry" DESTINATION "install/include")
install(DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/utility" DESTINATION "install/include")