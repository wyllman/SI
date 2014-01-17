set (CMAKE_POSITION_INDEPENDENT_CODE TRUE)

add_library (
	Agents
	STATIC
	Agent.cpp
	MainAgent.cpp
	SearchAgent.cpp
	WorkingAgent.cpp
  )

set (CMAKE_POSITION_INDEPENDENT_CODE FALSE)