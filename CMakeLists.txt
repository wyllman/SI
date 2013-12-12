cmake_minimum_required (VERSION 2.8)
cmake_policy (VERSION 2.8)

project (SI C CXX)
set (SI_VERSION_MAJOR 0)
set (SI_VERSION_MINOR 2)

set (PROJECT_DIR ${PROJECT_SOURCE_DIR})
set (PROJECT_INCLUDE_DIR ${PROJECT_DIR}/include)
set (PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)
set (PROJECT_BINARY_DIR ${PROJECT_DIR}/build)

set (CMAKE_MODULE_PATH ${PROJECT_DIR}/cmake/modules)

configure_file (
	"${PROJECT_INCLUDE_DIR}/SIConfig.h.in"
	"${PROJECT_BINARY_DIR}/SIConfig.h"
)

option (
	VERBOSE_BUILD
	"Sets VERBOSE=1 for debugging purposes"
	OFF
)

option (
	CONSOLE_BUILD
	"Sets the console build instead of the OpenGL"
	OFF
)

option (
	BUILD_DOCUMENTATION
	"Poseso"
	OFF
)

if (BUILD_DOCUMENTATION)
	generate_documentation (${PROJECT_DIR}/Doxyfile)
	return ()
endif (BUILD_DOCUMENTATION)

if (VERBOSE_BUILD)
	set (CMAKE_VERBOSE_MAKEFILE ON)
endif ()

if (CONSOLE_BUILD)
	# TODO
endif ()

set (CMAKE_BUILD_TYPE Debug)

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
endforeach ()

link_directories (${PROJECT_BINARY_DIR}/controller/director)
link_directories (${PROJECT_BINARY_DIR}/controller/abstracts)
link_directories (${PROJECT_BINARY_DIR}/view/interface)
link_directories (${PROJECT_BINARY_DIR}/model/simulator)

add_executable (${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/PreColonia.cpp)
target_link_libraries (
	SI
	Director
	Interface
	Simulator
	Controller
)
