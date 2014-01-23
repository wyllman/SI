set (CMAKE_POSITION_INDEPENDENT_CODE TRUE)

add_library (
	Node
        STATIC
	Node.cpp
)

add_library (
	PathFindingTree
	STATIC
	PathFindingTree.cpp
)

set (CMAKE_POSITION_INDEPENDENT_CODE FALSE)
