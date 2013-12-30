add_library (
	Simulator
	SHARED
	Simulator.cpp
)

target_link_libraries (Simulator Model Map MapConsoleInterface ${BOOST_RANDOM_LIB})