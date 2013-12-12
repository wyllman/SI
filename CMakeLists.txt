cmake_minimum_required (VERSION 2.8)
cmake_policy (VERSION 2.8)

project (SI C CXX)

set (PROJECT_DIR ${PROJECT_SOURCE_DIR})
set (PROJECT_INCLUDE_DIR ${PROJECT_DIR}/include)
set (PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)
set (PROJECT_BINARY_DIR ${PROJECT_DIR}/build)

set (CMAKE_MODULE_PATH ${PROJECT_DIR}/cmake/modules)

option (
	VERBOSE_BUILD
	"Sets VERBOSE=1 for debugging purposes"
	OFF)

option (
	CONSOLE_BUILD
	"Sets the console build instead of the OpenGL"
	OFF)

if (VERBOSE_BUILD)
	set (CMAKE_VERBOSE_MAKEFILE ON)
endif ()

if (CONSOLE_BUILD)
	# TODO
endif ()

include_directories (${PROJECT_INCLUDE_DIR})

foreach (A ${INCLUDE_DIRECTORIES})
	message ("${A}")
endforeach ()

find_package (Boost 1.54 REQUIRED)
find_package (GLEW)
find_package (OpenGL)
find_package (SDL2)

set (DIRS /controller /view /model)

foreach (DIR ${DIRS})
	add_subdirectory (${PROJECT_SOURCE_DIR}${DIR})
	link_directories (${PROJECT_BINARY_DIR}${DIR})
endforeach ()

#add_executable (${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/PreColonia.cpp)