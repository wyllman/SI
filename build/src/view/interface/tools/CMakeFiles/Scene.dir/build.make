# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/manwe/workspace/SI

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/manwe/workspace/SI/build

# Include any dependencies generated for this target.
include src/view/interface/tools/CMakeFiles/Scene.dir/depend.make

# Include the progress variables for this target.
include src/view/interface/tools/CMakeFiles/Scene.dir/progress.make

# Include the compile flags for this target's objects.
include src/view/interface/tools/CMakeFiles/Scene.dir/flags.make

src/view/interface/tools/CMakeFiles/Scene.dir/Scene.cpp.o: src/view/interface/tools/CMakeFiles/Scene.dir/flags.make
src/view/interface/tools/CMakeFiles/Scene.dir/Scene.cpp.o: ../src/view/interface/tools/Scene.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/manwe/workspace/SI/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/view/interface/tools/CMakeFiles/Scene.dir/Scene.cpp.o"
	cd /home/manwe/workspace/SI/build/src/view/interface/tools && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Scene.dir/Scene.cpp.o -c /home/manwe/workspace/SI/src/view/interface/tools/Scene.cpp

src/view/interface/tools/CMakeFiles/Scene.dir/Scene.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Scene.dir/Scene.cpp.i"
	cd /home/manwe/workspace/SI/build/src/view/interface/tools && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/manwe/workspace/SI/src/view/interface/tools/Scene.cpp > CMakeFiles/Scene.dir/Scene.cpp.i

src/view/interface/tools/CMakeFiles/Scene.dir/Scene.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Scene.dir/Scene.cpp.s"
	cd /home/manwe/workspace/SI/build/src/view/interface/tools && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/manwe/workspace/SI/src/view/interface/tools/Scene.cpp -o CMakeFiles/Scene.dir/Scene.cpp.s

src/view/interface/tools/CMakeFiles/Scene.dir/Scene.cpp.o.requires:
.PHONY : src/view/interface/tools/CMakeFiles/Scene.dir/Scene.cpp.o.requires

src/view/interface/tools/CMakeFiles/Scene.dir/Scene.cpp.o.provides: src/view/interface/tools/CMakeFiles/Scene.dir/Scene.cpp.o.requires
	$(MAKE) -f src/view/interface/tools/CMakeFiles/Scene.dir/build.make src/view/interface/tools/CMakeFiles/Scene.dir/Scene.cpp.o.provides.build
.PHONY : src/view/interface/tools/CMakeFiles/Scene.dir/Scene.cpp.o.provides

src/view/interface/tools/CMakeFiles/Scene.dir/Scene.cpp.o.provides.build: src/view/interface/tools/CMakeFiles/Scene.dir/Scene.cpp.o

# Object files for target Scene
Scene_OBJECTS = \
"CMakeFiles/Scene.dir/Scene.cpp.o"

# External object files for target Scene
Scene_EXTERNAL_OBJECTS =

src/view/interface/tools/libScene.a: src/view/interface/tools/CMakeFiles/Scene.dir/Scene.cpp.o
src/view/interface/tools/libScene.a: src/view/interface/tools/CMakeFiles/Scene.dir/build.make
src/view/interface/tools/libScene.a: src/view/interface/tools/CMakeFiles/Scene.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libScene.a"
	cd /home/manwe/workspace/SI/build/src/view/interface/tools && $(CMAKE_COMMAND) -P CMakeFiles/Scene.dir/cmake_clean_target.cmake
	cd /home/manwe/workspace/SI/build/src/view/interface/tools && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Scene.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/view/interface/tools/CMakeFiles/Scene.dir/build: src/view/interface/tools/libScene.a
.PHONY : src/view/interface/tools/CMakeFiles/Scene.dir/build

src/view/interface/tools/CMakeFiles/Scene.dir/requires: src/view/interface/tools/CMakeFiles/Scene.dir/Scene.cpp.o.requires
.PHONY : src/view/interface/tools/CMakeFiles/Scene.dir/requires

src/view/interface/tools/CMakeFiles/Scene.dir/clean:
	cd /home/manwe/workspace/SI/build/src/view/interface/tools && $(CMAKE_COMMAND) -P CMakeFiles/Scene.dir/cmake_clean.cmake
.PHONY : src/view/interface/tools/CMakeFiles/Scene.dir/clean

src/view/interface/tools/CMakeFiles/Scene.dir/depend:
	cd /home/manwe/workspace/SI/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/manwe/workspace/SI /home/manwe/workspace/SI/src/view/interface/tools /home/manwe/workspace/SI/build /home/manwe/workspace/SI/build/src/view/interface/tools /home/manwe/workspace/SI/build/src/view/interface/tools/CMakeFiles/Scene.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/view/interface/tools/CMakeFiles/Scene.dir/depend

