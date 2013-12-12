add_subdirectory (tools)

add_library (
	Director
	STATIC
	Director.cpp)

target_link_libraries (Director FileLog MainLoop)