# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/louisa/IMAC2/POO/World_IMaker/code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/louisa/IMAC2/POO/World_IMaker/build

# Include any dependencies generated for this target.
include src/CMakeFiles/src_sphere.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/src_sphere.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/src_sphere.dir/flags.make

src/CMakeFiles/src_sphere.dir/sphere.cpp.o: src/CMakeFiles/src_sphere.dir/flags.make
src/CMakeFiles/src_sphere.dir/sphere.cpp.o: /home/louisa/IMAC2/POO/World_IMaker/code/src/sphere.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/louisa/IMAC2/POO/World_IMaker/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/src_sphere.dir/sphere.cpp.o"
	cd /home/louisa/IMAC2/POO/World_IMaker/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src_sphere.dir/sphere.cpp.o -c /home/louisa/IMAC2/POO/World_IMaker/code/src/sphere.cpp

src/CMakeFiles/src_sphere.dir/sphere.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src_sphere.dir/sphere.cpp.i"
	cd /home/louisa/IMAC2/POO/World_IMaker/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/louisa/IMAC2/POO/World_IMaker/code/src/sphere.cpp > CMakeFiles/src_sphere.dir/sphere.cpp.i

src/CMakeFiles/src_sphere.dir/sphere.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src_sphere.dir/sphere.cpp.s"
	cd /home/louisa/IMAC2/POO/World_IMaker/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/louisa/IMAC2/POO/World_IMaker/code/src/sphere.cpp -o CMakeFiles/src_sphere.dir/sphere.cpp.s

src/CMakeFiles/src_sphere.dir/sphere.cpp.o.requires:

.PHONY : src/CMakeFiles/src_sphere.dir/sphere.cpp.o.requires

src/CMakeFiles/src_sphere.dir/sphere.cpp.o.provides: src/CMakeFiles/src_sphere.dir/sphere.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/src_sphere.dir/build.make src/CMakeFiles/src_sphere.dir/sphere.cpp.o.provides.build
.PHONY : src/CMakeFiles/src_sphere.dir/sphere.cpp.o.provides

src/CMakeFiles/src_sphere.dir/sphere.cpp.o.provides.build: src/CMakeFiles/src_sphere.dir/sphere.cpp.o


# Object files for target src_sphere
src_sphere_OBJECTS = \
"CMakeFiles/src_sphere.dir/sphere.cpp.o"

# External object files for target src_sphere
src_sphere_EXTERNAL_OBJECTS =

src/src_sphere: src/CMakeFiles/src_sphere.dir/sphere.cpp.o
src/src_sphere: src/CMakeFiles/src_sphere.dir/build.make
src/src_sphere: glimac/libglimac.a
src/src_sphere: /usr/lib/x86_64-linux-gnu/libGL.so
src/src_sphere: /usr/lib/x86_64-linux-gnu/libGLU.so
src/src_sphere: /usr/lib/x86_64-linux-gnu/libGLEW.so
src/src_sphere: src/CMakeFiles/src_sphere.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/louisa/IMAC2/POO/World_IMaker/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable src_sphere"
	cd /home/louisa/IMAC2/POO/World_IMaker/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/src_sphere.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/src_sphere.dir/build: src/src_sphere

.PHONY : src/CMakeFiles/src_sphere.dir/build

src/CMakeFiles/src_sphere.dir/requires: src/CMakeFiles/src_sphere.dir/sphere.cpp.o.requires

.PHONY : src/CMakeFiles/src_sphere.dir/requires

src/CMakeFiles/src_sphere.dir/clean:
	cd /home/louisa/IMAC2/POO/World_IMaker/build/src && $(CMAKE_COMMAND) -P CMakeFiles/src_sphere.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/src_sphere.dir/clean

src/CMakeFiles/src_sphere.dir/depend:
	cd /home/louisa/IMAC2/POO/World_IMaker/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/louisa/IMAC2/POO/World_IMaker/code /home/louisa/IMAC2/POO/World_IMaker/code/src /home/louisa/IMAC2/POO/World_IMaker/build /home/louisa/IMAC2/POO/World_IMaker/build/src /home/louisa/IMAC2/POO/World_IMaker/build/src/CMakeFiles/src_sphere.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/src_sphere.dir/depend

