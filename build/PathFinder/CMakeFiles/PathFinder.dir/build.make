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
CMAKE_COMMAND = /snap/cmake/846/bin/cmake

# The command to remove a file.
RM = /snap/cmake/846/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/build

# Include any dependencies generated for this target.
include PathFinder/CMakeFiles/PathFinder.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include PathFinder/CMakeFiles/PathFinder.dir/compiler_depend.make

# Include the progress variables for this target.
include PathFinder/CMakeFiles/PathFinder.dir/progress.make

# Include the compile flags for this target's objects.
include PathFinder/CMakeFiles/PathFinder.dir/flags.make

PathFinder/CMakeFiles/PathFinder.dir/mNode.cpp.o: PathFinder/CMakeFiles/PathFinder.dir/flags.make
PathFinder/CMakeFiles/PathFinder.dir/mNode.cpp.o: /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/src/PathFinder/mNode.cpp
PathFinder/CMakeFiles/PathFinder.dir/mNode.cpp.o: PathFinder/CMakeFiles/PathFinder.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object PathFinder/CMakeFiles/PathFinder.dir/mNode.cpp.o"
	cd /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/build/PathFinder && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT PathFinder/CMakeFiles/PathFinder.dir/mNode.cpp.o -MF CMakeFiles/PathFinder.dir/mNode.cpp.o.d -o CMakeFiles/PathFinder.dir/mNode.cpp.o -c /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/src/PathFinder/mNode.cpp

PathFinder/CMakeFiles/PathFinder.dir/mNode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PathFinder.dir/mNode.cpp.i"
	cd /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/build/PathFinder && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/src/PathFinder/mNode.cpp > CMakeFiles/PathFinder.dir/mNode.cpp.i

PathFinder/CMakeFiles/PathFinder.dir/mNode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PathFinder.dir/mNode.cpp.s"
	cd /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/build/PathFinder && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/src/PathFinder/mNode.cpp -o CMakeFiles/PathFinder.dir/mNode.cpp.s

PathFinder/CMakeFiles/PathFinder.dir/mGrid.cpp.o: PathFinder/CMakeFiles/PathFinder.dir/flags.make
PathFinder/CMakeFiles/PathFinder.dir/mGrid.cpp.o: /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/src/PathFinder/mGrid.cpp
PathFinder/CMakeFiles/PathFinder.dir/mGrid.cpp.o: PathFinder/CMakeFiles/PathFinder.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object PathFinder/CMakeFiles/PathFinder.dir/mGrid.cpp.o"
	cd /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/build/PathFinder && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT PathFinder/CMakeFiles/PathFinder.dir/mGrid.cpp.o -MF CMakeFiles/PathFinder.dir/mGrid.cpp.o.d -o CMakeFiles/PathFinder.dir/mGrid.cpp.o -c /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/src/PathFinder/mGrid.cpp

PathFinder/CMakeFiles/PathFinder.dir/mGrid.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PathFinder.dir/mGrid.cpp.i"
	cd /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/build/PathFinder && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/src/PathFinder/mGrid.cpp > CMakeFiles/PathFinder.dir/mGrid.cpp.i

PathFinder/CMakeFiles/PathFinder.dir/mGrid.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PathFinder.dir/mGrid.cpp.s"
	cd /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/build/PathFinder && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/src/PathFinder/mGrid.cpp -o CMakeFiles/PathFinder.dir/mGrid.cpp.s

PathFinder/CMakeFiles/PathFinder.dir/Canvas.cpp.o: PathFinder/CMakeFiles/PathFinder.dir/flags.make
PathFinder/CMakeFiles/PathFinder.dir/Canvas.cpp.o: /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/src/PathFinder/Canvas.cpp
PathFinder/CMakeFiles/PathFinder.dir/Canvas.cpp.o: PathFinder/CMakeFiles/PathFinder.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object PathFinder/CMakeFiles/PathFinder.dir/Canvas.cpp.o"
	cd /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/build/PathFinder && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT PathFinder/CMakeFiles/PathFinder.dir/Canvas.cpp.o -MF CMakeFiles/PathFinder.dir/Canvas.cpp.o.d -o CMakeFiles/PathFinder.dir/Canvas.cpp.o -c /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/src/PathFinder/Canvas.cpp

PathFinder/CMakeFiles/PathFinder.dir/Canvas.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PathFinder.dir/Canvas.cpp.i"
	cd /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/build/PathFinder && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/src/PathFinder/Canvas.cpp > CMakeFiles/PathFinder.dir/Canvas.cpp.i

PathFinder/CMakeFiles/PathFinder.dir/Canvas.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PathFinder.dir/Canvas.cpp.s"
	cd /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/build/PathFinder && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/src/PathFinder/Canvas.cpp -o CMakeFiles/PathFinder.dir/Canvas.cpp.s

PathFinder/CMakeFiles/PathFinder.dir/AStar.cpp.o: PathFinder/CMakeFiles/PathFinder.dir/flags.make
PathFinder/CMakeFiles/PathFinder.dir/AStar.cpp.o: /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/src/PathFinder/AStar.cpp
PathFinder/CMakeFiles/PathFinder.dir/AStar.cpp.o: PathFinder/CMakeFiles/PathFinder.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object PathFinder/CMakeFiles/PathFinder.dir/AStar.cpp.o"
	cd /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/build/PathFinder && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT PathFinder/CMakeFiles/PathFinder.dir/AStar.cpp.o -MF CMakeFiles/PathFinder.dir/AStar.cpp.o.d -o CMakeFiles/PathFinder.dir/AStar.cpp.o -c /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/src/PathFinder/AStar.cpp

PathFinder/CMakeFiles/PathFinder.dir/AStar.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PathFinder.dir/AStar.cpp.i"
	cd /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/build/PathFinder && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/src/PathFinder/AStar.cpp > CMakeFiles/PathFinder.dir/AStar.cpp.i

PathFinder/CMakeFiles/PathFinder.dir/AStar.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PathFinder.dir/AStar.cpp.s"
	cd /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/build/PathFinder && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/src/PathFinder/AStar.cpp -o CMakeFiles/PathFinder.dir/AStar.cpp.s

# Object files for target PathFinder
PathFinder_OBJECTS = \
"CMakeFiles/PathFinder.dir/mNode.cpp.o" \
"CMakeFiles/PathFinder.dir/mGrid.cpp.o" \
"CMakeFiles/PathFinder.dir/Canvas.cpp.o" \
"CMakeFiles/PathFinder.dir/AStar.cpp.o"

# External object files for target PathFinder
PathFinder_EXTERNAL_OBJECTS =

PathFinder/libPathFinder.a: PathFinder/CMakeFiles/PathFinder.dir/mNode.cpp.o
PathFinder/libPathFinder.a: PathFinder/CMakeFiles/PathFinder.dir/mGrid.cpp.o
PathFinder/libPathFinder.a: PathFinder/CMakeFiles/PathFinder.dir/Canvas.cpp.o
PathFinder/libPathFinder.a: PathFinder/CMakeFiles/PathFinder.dir/AStar.cpp.o
PathFinder/libPathFinder.a: PathFinder/CMakeFiles/PathFinder.dir/build.make
PathFinder/libPathFinder.a: PathFinder/CMakeFiles/PathFinder.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library libPathFinder.a"
	cd /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/build/PathFinder && $(CMAKE_COMMAND) -P CMakeFiles/PathFinder.dir/cmake_clean_target.cmake
	cd /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/build/PathFinder && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PathFinder.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
PathFinder/CMakeFiles/PathFinder.dir/build: PathFinder/libPathFinder.a
.PHONY : PathFinder/CMakeFiles/PathFinder.dir/build

PathFinder/CMakeFiles/PathFinder.dir/clean:
	cd /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/build/PathFinder && $(CMAKE_COMMAND) -P CMakeFiles/PathFinder.dir/cmake_clean.cmake
.PHONY : PathFinder/CMakeFiles/PathFinder.dir/clean

PathFinder/CMakeFiles/PathFinder.dir/depend:
	cd /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/src /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/src/PathFinder /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/build /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/build/PathFinder /home/matheus/Documentos/doutorado_ic/tese/NMR/AstarPathfinder/build/PathFinder/CMakeFiles/PathFinder.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : PathFinder/CMakeFiles/PathFinder.dir/depend
