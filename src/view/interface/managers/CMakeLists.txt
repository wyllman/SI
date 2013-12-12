add_library (
	Bureaucrat
	SHARED
	Bureaucrat.cpp
)

add_library (
	Scenographer
	SHARED
	Scenographer.cpp
)

target_link_libraries (Scenographer ${OPENGL_LIBRARIES})