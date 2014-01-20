set (CMAKE_POSITION_INDEPENDENT_CODE TRUE)

add_subdirectory (tools)

add_library (
	Agents
	STATIC
	Agent.cpp
	MainAgent.cpp
	SearchAgent.cpp
	WorkingAgent.cpp
  )

target_link_Libraries (Agents Node PathFindingTree)

set (CMAKE_POSITION_INDEPENDENT_CODE FALSE)

