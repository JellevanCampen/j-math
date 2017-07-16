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

set(SRC_UTILITY 
			utility/pi.h
			utility/numeric_comparison.h
)
source_group(utility FILES ${SRC_UTILITY})
list(APPEND SRC ${SRC_UTILITY})

add_library( ${TARGET_NAME} ${SRC})
set_target_properties(${TARGET_NAME} PROPERTIES LINKER_LANGUAGE CXX)