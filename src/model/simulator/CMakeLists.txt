add_library (
	Simulator
	STATIC
	Simulator.cpp
)

target_link_libraries (Simulator Model Map MapConsoleInterface)