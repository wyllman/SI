include_directories (${PROJECT_DIR}/assets)

add_library (
	MapBuilder
	STATIC
	MapBuilder.cpp)
	
add_library (
	Map
	STATIC
	Map.cpp)