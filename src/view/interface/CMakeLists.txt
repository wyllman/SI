add_subdirectory (managers)
add_subdirectory (tools)

add_library (
	Interface
	STATIC
	Interface.cpp)

target_link_libraries (Interface Bureaucrat Scenographer Context Scene Window)