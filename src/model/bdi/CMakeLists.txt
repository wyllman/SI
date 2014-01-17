set (CMAKE_POSITION_INDEPENDENT_CODE TRUE)

add_library (
	BDI
	STATIC
	Belief.cpp
	BeliefSet.cpp
	Desire.cpp
	Intention.cpp
  )

set (CMAKE_POSITION_INDEPENDENT_CODE FALSE)