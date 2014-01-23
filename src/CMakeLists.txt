set (CMAKE_POSITION_INDEPENDENT_CODE TRUE)

add_library (
	Tools
	STATIC
	Tools.cpp
  )

add_library (
	Point
	STATIC
	Point.cpp
)

set (CMAKE_POSITION_INDEPENDENT_CODE FALSE)