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
include Test/CMakeFiles/Test_cube_try_data_display.dir/depend.make

# Include the progress variables for this target.
include Test/CMakeFiles/Test_cube_try_data_display.dir/progress.make

# Include the compile flags for this target's objects.
include Test/CMakeFiles/Test_cube_try_data_display.dir/flags.make

Test/CMakeFiles/Test_cube_try_data_display.dir/cube_try_data_display.cpp.o: Test/CMakeFiles/Test_cube_try_data_display.dir/flags.make
Test/CMakeFiles/Test_cube_try_data_display.dir/cube_try_data_display.cpp.o: /home/louisa/IMAC2/POO/World_IMaker/code/Test/cube_try_data_display.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/louisa/IMAC2/POO/World_IMaker/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Test/CMakeFiles/Test_cube_try_data_display.dir/cube_try_data_display.cpp.o"
	cd /home/louisa/IMAC2/POO/World_IMaker/build/Test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Test_cube_try_data_display.dir/cube_try_data_display.cpp.o -c /home/louisa/IMAC2/POO/World_IMaker/code/Test/cube_try_data_display.cpp

Test/CMakeFiles/Test_cube_try_data_display.dir/cube_try_data_display.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Test_cube_try_data_display.dir/cube_try_data_display.cpp.i"
	cd /home/louisa/IMAC2/POO/World_IMaker/build/Test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/louisa/IMAC2/POO/World_IMaker/code/Test/cube_try_data_display.cpp > CMakeFiles/Test_cube_try_data_display.dir/cube_try_data_display.cpp.i

Test/CMakeFiles/Test_cube_try_data_display.dir/cube_try_data_display.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Test_cube_try_data_display.dir/cube_try_data_display.cpp.s"
	cd /home/louisa/IMAC2/POO/World_IMaker/build/Test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/louisa/IMAC2/POO/World_IMaker/code/Test/cube_try_data_display.cpp -o CMakeFiles/Test_cube_try_data_display.dir/cube_try_data_display.cpp.s

Test/CMakeFiles/Test_cube_try_data_display.dir/cube_try_data_display.cpp.o.requires:

.PHONY : Test/CMakeFiles/Test_cube_try_data_display.dir/cube_try_data_display.cpp.o.requires

Test/CMakeFiles/Test_cube_try_data_display.dir/cube_try_data_display.cpp.o.provides: Test/CMakeFiles/Test_cube_try_data_display.dir/cube_try_data_display.cpp.o.requires
	$(MAKE) -f Test/CMakeFiles/Test_cube_try_data_display.dir/build.make Test/CMakeFiles/Test_cube_try_data_display.dir/cube_try_data_display.cpp.o.provides.build
.PHONY : Test/CMakeFiles/Test_cube_try_data_display.dir/cube_try_data_display.cpp.o.provides

Test/CMakeFiles/Test_cube_try_data_display.dir/cube_try_data_display.cpp.o.provides.build: Test/CMakeFiles/Test_cube_try_data_display.dir/cube_try_data_display.cpp.o


# Object files for target Test_cube_try_data_display
Test_cube_try_data_display_OBJECTS = \
"CMakeFiles/Test_cube_try_data_display.dir/cube_try_data_display.cpp.o"

# External object files for target Test_cube_try_data_display
Test_cube_try_data_display_EXTERNAL_OBJECTS =

Test/Test_cube_try_data_display: Test/CMakeFiles/Test_cube_try_data_display.dir/cube_try_data_display.cpp.o
Test/Test_cube_try_data_display: Test/CMakeFiles/Test_cube_try_data_display.dir/build.make
Test/Test_cube_try_data_display: glimac/libglimac.a
Test/Test_cube_try_data_display: /usr/lib/x86_64-linux-gnu/libGL.so
Test/Test_cube_try_data_display: /usr/lib/x86_64-linux-gnu/libGLU.so
Test/Test_cube_try_data_display: /usr/lib/x86_64-linux-gnu/libGLEW.so
Test/Test_cube_try_data_display: Test/CMakeFiles/Test_cube_try_data_display.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/louisa/IMAC2/POO/World_IMaker/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Test_cube_try_data_display"
	cd /home/louisa/IMAC2/POO/World_IMaker/build/Test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Test_cube_try_data_display.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Test/CMakeFiles/Test_cube_try_data_display.dir/build: Test/Test_cube_try_data_display

.PHONY : Test/CMakeFiles/Test_cube_try_data_display.dir/build

Test/CMakeFiles/Test_cube_try_data_display.dir/requires: Test/CMakeFiles/Test_cube_try_data_display.dir/cube_try_data_display.cpp.o.requires

.PHONY : Test/CMakeFiles/Test_cube_try_data_display.dir/requires

Test/CMakeFiles/Test_cube_try_data_display.dir/clean:
	cd /home/louisa/IMAC2/POO/World_IMaker/build/Test && $(CMAKE_COMMAND) -P CMakeFiles/Test_cube_try_data_display.dir/cmake_clean.cmake
.PHONY : Test/CMakeFiles/Test_cube_try_data_display.dir/clean

Test/CMakeFiles/Test_cube_try_data_display.dir/depend:
	cd /home/louisa/IMAC2/POO/World_IMaker/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/louisa/IMAC2/POO/World_IMaker/code /home/louisa/IMAC2/POO/World_IMaker/code/Test /home/louisa/IMAC2/POO/World_IMaker/build /home/louisa/IMAC2/POO/World_IMaker/build/Test /home/louisa/IMAC2/POO/World_IMaker/build/Test/CMakeFiles/Test_cube_try_data_display.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Test/CMakeFiles/Test_cube_try_data_display.dir/depend

