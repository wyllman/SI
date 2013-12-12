cmake_minimum_required (VERSION 2.8)

project (SI C CXX)

set (PROJECT_DIR ${PROJECT_SOURCE_DIR})
set (PROJECT_INCLUDE_DIR ${PROJECT_DIR}/include)
set (PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)
set (PROJECT_BINARY_DIR ${PROJECT_DIR}/build)

set (CMAKE_MODULE_PATH ${PROJECT_DIR}/cmake/modules)

include_directories (${PROJECT_INCLUDE_DIR})

find_package(Boost 1.54)
find_package(GLEW)
find_package(OpenGL)
find_package(SDL2)

add_subdirectory (${PROJECT_SOURCE_DIR}/controller)
add_subdirectory (${PROJECT_SOURCE_DIR}/view)
add_subdirectory (${PROJECT_SOURCE_DIR}/model)

link_directories (${PROJECT_BINARY_DIR}/controller)
link_directories (${PROJECT_BINARY_DIR}/view)
link_directories (${PROJECT_BINARY_DIR}/model)

add_executable (${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/PreColonia.cpp)