set (CMAKE_POSITION_INDEPENDENT_CODE TRUE)

add_library (
	Context
	STATIC
	Context.cpp
)

if (PROJECT_OS MATCHES "Linux")
	target_link_libraries (Context Interface ${GLEW_LIBRARIES})
else (PROJECT_OS MATCHES "Linux")
	target_link_libraries (Context Interface ${OPENGL_LIBRARIES})
endif (PROJECT_OS MATCHES "Linux")

add_library (
	Scene
	STATIC
	Scene.cpp
)

target_link_libraries (Scene Interface)

add_library (
	Window
	STATIC
	Window.cpp
)

target_link_libraries (Window Interface ${SDL2_LIBRARY})

set (CMAKE_POSITION_INDEPENDENT_CODE FALSE)