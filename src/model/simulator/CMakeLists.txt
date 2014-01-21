add_library (
	Simulator
	SHARED
	Simulator.cpp
)

target_link_libraries (Simulator Tools Model Map MapConsoleInterface BDI FIPA Agents ${BOOST_RANDOM_LIB})