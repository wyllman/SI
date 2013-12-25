# ### Initial configuration ###
cmake_minimum_required (VERSION 2.8)
cmake_policy (VERSION 2.8)

# ### Options ###
option (
	USE_CLANG
	"Build application with clang (Default=OFF)"
	OFF
)

option (
	VERBOSE_BUILD
	"Sets VERBOSE=1 for debugging purposes (Default=OFF)"
	OFF
)

option (
	CONSOLE_BUILD
	"Sets the console build instead of the OpenGL (Default=OFF)"
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

# ### Compiler option parsing (must be done before setting the project) ###
if (USE_CLANG)
	set (ENV{CC} /usr/bin/clang)
	set (ENV{CXX} /usr/bin/clang++)
	set (CMAKE_USER_MAKE_RULES_OVERRIDE ./ClangOverrides.txt)
endif (USE_CLANG)

# ### Project configuration ###
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
	set (CMAKE_BUILD_TYPE DEBUG)
endif (DEBUG_BUILD)

# ### Platform detection ###
if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	set (PROJECT_OS "Linux")
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set (PROJECT_OS "OSX")
endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")

# ### Package finding ###
find_file (
	FINDGLEW_FOUND
	FindGLEW.cmake
	PATHS ${CMAKE_ROOT}/Modules/
)

find_package (Boost REQUIRED)
if (Boost_FOUND)
	include_directories (${Boost_INCLUDE_DIRS})
endif (Boost_FOUND)

if (${PROJECT_OS} MATCHES "Linux")
	if (FINDGLEW_FOUND)
		set (CMAKE_MODULE_PATH "")
		find_package (GLEW REQUIRED)
		set (CMAKE_MODULE_PATH ${PROJECT_DIR}/cmake/modules)
	else (FINDGLEW_FOUND)
		find_package (GLEW)
	endif (FINDGLEW_FOUND)
	
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
if (CMAKE_BUILD_TYPE MATCHES DEBUG)
	set (PROJECT_EXEC_NAME ${PROJECT_NAME}-Debug)
	message ("-- Building Debug Project --")
else (CMAKE_BUILD_TYPE MATCHES DEBUG)
	set (PROJECT_EXEC_NAME ${PROJECT_NAME}-Release)
	message ("-- Building Release Project --")
endif (CMAKE_BUILD_TYPE MATCHES DEBUG)

add_executable (${PROJECT_EXEC_NAME} ${PROJECT_SOURCE_DIR}/PreColonia.cpp)

target_link_libraries (
	${PROJECT_EXEC_NAME}
	Director
	Interface
	Simulator
)
