set (CMAKE_POSITION_INDEPENDENT_CODE TRUE)

add_library (
	Bureaucrat
	STATIC
	Bureaucrat.cpp
)

if (PROJECT_OS MATCHES "Linux")
	target_link_libraries (Bureaucrat Interface ${GLEW_LIBRARIES})
else (PROJECT_OS MATCHES "Linux")
	target_link_libraries (Bureaucrat Interface ${OPENGL_LIBRARIES})
endif (PROJECT_OS MATCHES "Linux")

add_library (
	Scenographer
	STATIC
	Scenographer.cpp
)

if (PROJECT_OS MATCHES "Linux")
	target_link_libraries (Scenographer Interface ${GLEW_LIBRARIES})
else (PROJECT_OS MATCHES "Linux")
	target_link_libraries (Scenographer Interface ${OPENGL_LIBRARIES})
endif (PROJECT_OS MATCHES "Linux")

set (CMAKE_POSITION_INDEPENDENT_CODE FALSE)