# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/clion/163/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/163/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/katrin/CLionProjects/geometry

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/katrin/CLionProjects/geometry/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/hull.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/hull.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hull.dir/flags.make

CMakeFiles/hull.dir/hull.cpp.o: CMakeFiles/hull.dir/flags.make
CMakeFiles/hull.dir/hull.cpp.o: ../hull.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/katrin/CLionProjects/geometry/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/hull.dir/hull.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hull.dir/hull.cpp.o -c /home/katrin/CLionProjects/geometry/hull.cpp

CMakeFiles/hull.dir/hull.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hull.dir/hull.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/katrin/CLionProjects/geometry/hull.cpp > CMakeFiles/hull.dir/hull.cpp.i

CMakeFiles/hull.dir/hull.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hull.dir/hull.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/katrin/CLionProjects/geometry/hull.cpp -o CMakeFiles/hull.dir/hull.cpp.s

# Object files for target hull
hull_OBJECTS = \
"CMakeFiles/hull.dir/hull.cpp.o"

# External object files for target hull
hull_EXTERNAL_OBJECTS =

hull: CMakeFiles/hull.dir/hull.cpp.o
hull: CMakeFiles/hull.dir/build.make
hull: CMakeFiles/hull.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/katrin/CLionProjects/geometry/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable hull"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hull.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hull.dir/build: hull
.PHONY : CMakeFiles/hull.dir/build

CMakeFiles/hull.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hull.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hull.dir/clean

CMakeFiles/hull.dir/depend:
	cd /home/katrin/CLionProjects/geometry/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/katrin/CLionProjects/geometry /home/katrin/CLionProjects/geometry /home/katrin/CLionProjects/geometry/cmake-build-debug /home/katrin/CLionProjects/geometry/cmake-build-debug /home/katrin/CLionProjects/geometry/cmake-build-debug/CMakeFiles/hull.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hull.dir/depend
