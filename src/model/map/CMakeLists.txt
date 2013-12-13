include_directories (${PROJECT_DIR}/assets)

add_library (
	MapBuilder
	STATIC
	MapBuilder.cpp)
	
add_library (
	Map
	STATIC
	Map.cpp)

add_library (
	MapConsoleInterface
	STATIC
	MapConsoleInterface.cpp
)

target_link_libraries (Map MapBuilder)