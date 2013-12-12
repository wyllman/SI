include_directories (${PROJECT_DIR}/assets)

add_library (
	MapBuilder
	SHARED
	MapBuilder.cpp)
	
add_library (
	Map
	SHARED
	Map.cpp)

add_library (
	MapConsoleInterface
	SHARED
	MapConsoleInterface.cpp
)

target_link_libraries (Map MapBuilder)