set (CMAKE_POSITION_INDEPENDENT_CODE TRUE)

add_library (
	FileLog
	STATIC
	FileLog.cpp
)

add_library (
	MainLoop
	STATIC
	MainLoop.cpp
)

set (CMAKE_POSITION_INDEPENDENT_CODE FALSE)