set (CMAKE_POSITION_INDEPENDENT_CODE TRUE)

add_library (
	Model
	STATIC
	Model.cpp
)

set (CMAKE_POSITION_INDEPENDENT_CODE FALSE)
