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
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zf/workspace_cpp/test5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zf/workspace_cpp/test5

# Include any dependencies generated for this target.
include comm/CMakeFiles/comm.dir/depend.make

# Include the progress variables for this target.
include comm/CMakeFiles/comm.dir/progress.make

# Include the compile flags for this target's objects.
include comm/CMakeFiles/comm.dir/flags.make

comm/CMakeFiles/comm.dir/CmmQueue.cpp.o: comm/CMakeFiles/comm.dir/flags.make
comm/CMakeFiles/comm.dir/CmmQueue.cpp.o: comm/CmmQueue.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zf/workspace_cpp/test5/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object comm/CMakeFiles/comm.dir/CmmQueue.cpp.o"
	cd /home/zf/workspace_cpp/test5/comm && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/comm.dir/CmmQueue.cpp.o -c /home/zf/workspace_cpp/test5/comm/CmmQueue.cpp

comm/CMakeFiles/comm.dir/CmmQueue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/comm.dir/CmmQueue.cpp.i"
	cd /home/zf/workspace_cpp/test5/comm && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zf/workspace_cpp/test5/comm/CmmQueue.cpp > CMakeFiles/comm.dir/CmmQueue.cpp.i

comm/CMakeFiles/comm.dir/CmmQueue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/comm.dir/CmmQueue.cpp.s"
	cd /home/zf/workspace_cpp/test5/comm && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zf/workspace_cpp/test5/comm/CmmQueue.cpp -o CMakeFiles/comm.dir/CmmQueue.cpp.s

comm/CMakeFiles/comm.dir/CmmQueue.cpp.o.requires:
.PHONY : comm/CMakeFiles/comm.dir/CmmQueue.cpp.o.requires

comm/CMakeFiles/comm.dir/CmmQueue.cpp.o.provides: comm/CMakeFiles/comm.dir/CmmQueue.cpp.o.requires
	$(MAKE) -f comm/CMakeFiles/comm.dir/build.make comm/CMakeFiles/comm.dir/CmmQueue.cpp.o.provides.build
.PHONY : comm/CMakeFiles/comm.dir/CmmQueue.cpp.o.provides

comm/CMakeFiles/comm.dir/CmmQueue.cpp.o.provides.build: comm/CMakeFiles/comm.dir/CmmQueue.cpp.o

comm: comm/CMakeFiles/comm.dir/CmmQueue.cpp.o
comm: comm/CMakeFiles/comm.dir/build.make
.PHONY : comm

# Rule to build all files generated by this target.
comm/CMakeFiles/comm.dir/build: comm
.PHONY : comm/CMakeFiles/comm.dir/build

comm/CMakeFiles/comm.dir/requires: comm/CMakeFiles/comm.dir/CmmQueue.cpp.o.requires
.PHONY : comm/CMakeFiles/comm.dir/requires

comm/CMakeFiles/comm.dir/clean:
	cd /home/zf/workspace_cpp/test5/comm && $(CMAKE_COMMAND) -P CMakeFiles/comm.dir/cmake_clean.cmake
.PHONY : comm/CMakeFiles/comm.dir/clean

comm/CMakeFiles/comm.dir/depend:
	cd /home/zf/workspace_cpp/test5 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zf/workspace_cpp/test5 /home/zf/workspace_cpp/test5/comm /home/zf/workspace_cpp/test5 /home/zf/workspace_cpp/test5/comm /home/zf/workspace_cpp/test5/comm/CMakeFiles/comm.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : comm/CMakeFiles/comm.dir/depend
