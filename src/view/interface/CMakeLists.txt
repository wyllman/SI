add_subdirectory (managers)
add_subdirectory (tools)

set (CMAKE_POSITION_INDEPENDENT_CODE TRUE)

add_library (
	Interface
	STATIC
	Interface.cpp
)

target_link_libraries (Interface View Bureaucrat Scenographer Context Scene Window ${OPENGL_LIBRARIES})

set (CMAKE_POSITION_INDEPENDENT_CODE TRUE)
