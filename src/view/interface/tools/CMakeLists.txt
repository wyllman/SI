add_library (
	Context
	SHARED
	Context.cpp
)

target_link_libraries (Context ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})

add_library (
	Scene
	SHARED
	Scene.cpp
)

target_link_libraries (Context ${OPENGL_LIBRARIES})

add_library (
	Window
	SHARED
	Window.cpp
)

target_link_libraries (Window ${SDL2_LIBRARY})