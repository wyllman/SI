add_subdirectory (tools)

add_library (
	Director
	SHARED
	Director.cpp
)

target_link_libraries (
	Director
	Controller
	FileLog
	MainLoop
)