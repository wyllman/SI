# ### Initial configuration ###
cmake_minimum_required (VERSION 2.8)
cmake_policy (VERSION 2.8)

project (SI C CXX)
set (SI_VERSION_MAJOR 0)
set (SI_VERSION_MINOR 3)

set (PROJECT_DIR ${PROJECT_SOURCE_DIR})
set (PROJECT_INCLUDE_DIR ${PROJECT_DIR}/include)
set (PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)
set (PROJECT_BINARY_DIR ${PROJECT_DIR}/build)

set (CMAKE_MODULE_PATH ${PROJECT_DIR}/cmake/modules)

include_directories (${PROJECT_INCLUDE_DIR})

configure_file (
	"${PROJECT_INCLUDE_DIR}/SIConfig.h.in"
	"${PROJECT_BINARY_DIR}/SIConfig.h"
)

# ### Platform detection ###
if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	set (PROJECT_OS "Linux")
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set (PROJECT_OS "OSX")
endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")

# ### Options ###
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
	DEBUG_BUILD
	"Sets CMAKE_BUILD_TYPE to Debug to compile debuggins symbols (Default=ON)"
	ON
)

option (
	BUILD_DOCUMENTATION
	"Poseso"
	OFF
)
# ### Options parsing ###
if (BUILD_DOCUMENTATION)
	generate_documentation (${PROJECT_DIR}/Doxyfile)
	return ()
endif (BUILD_DOCUMENTATION)

if (VERBOSE_BUILD)
	set (CMAKE_VERBOSE_MAKEFILE ON)
endif (VERBOSE_BUILD)

if (CONSOLE_BUILD)
	# TODO
endif (CONSOLE_BUILD)

if (DEBUG_BUILD)
	set (CMAKE_BUILD_TYPE Debug)
endif (DEBUG_BUILD)

# ### Package finding ###
find_package (Boost REQUIRED)
if (Boost_FOUND)
	include_directories (${Boost_INCLUDE_DIRS})
endif (Boost_FOUND)

if (${PROJECT_OS} MATCHES "Linux")
	find_package (GLEW)
	if (GLEW_FOUND)
		include_directories (${GLEW_INCLUDE_DIR})
	endif (GLEW_FOUND)
endif (${PROJECT_OS} MATCHES "Linux")

## FIXME: Volver a escribir el workaround de glew a ver si esta vez
## funciona

find_package (OpenGL REQUIRED)
if (OPENGL_FOUND)
	include_directories (${OPENGL_INCLUDE_DIR})
endif (OPENGL_FOUND)

find_package (SDL2 REQUIRED)
if (SDL2_FOUND)
	include_directories (${SDL2_INCLUDE_DIR})
endif (SDL2_FOUND)

# ### Compilation ###
set (DIRS /controller /view /model)

foreach (DIR ${DIRS})
	add_subdirectory (${PROJECT_SOURCE_DIR}${DIR})
endforeach ()

# ### Linking ###
link_directories (
	${PROJECT_BINARY_DIR}/controller/director
	${PROJECT_BINARY_DIR}/controller/abstracts
	${PROJECT_BINARY_DIR}/view/interface
	${PROJECT_BINARY_DIR}/model/simulator
)

# ### Final compilation and linkage ###
if (CMAKE_BUILD_TYPE MATCHES Debug)
	set (PROJECT_EXEC_NAME ${PROJECT_NAME}-Debug)
else (CMAKE_BUILD_TYPE MATCHES Debug)
	set (PROJECT_EXEC_NAME ${PROJECT_NAME}-Release)
endif (CMAKE_BUILD_TYPE MATCHES Debug)

add_executable (${PROJECT_EXEC_NAME} ${PROJECT_SOURCE_DIR}/PreColonia.cpp)

target_link_libraries (
	${PROJECT_EXEC_NAME}
	Director
	Interface
	Simulator
)