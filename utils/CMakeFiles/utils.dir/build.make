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
include utils/CMakeFiles/utils.dir/depend.make

# Include the progress variables for this target.
include utils/CMakeFiles/utils.dir/progress.make

# Include the compile flags for this target's objects.
include utils/CMakeFiles/utils.dir/flags.make

utils/CMakeFiles/utils.dir/ShmStore.cpp.o: utils/CMakeFiles/utils.dir/flags.make
utils/CMakeFiles/utils.dir/ShmStore.cpp.o: utils/ShmStore.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zf/workspace_cpp/test5/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object utils/CMakeFiles/utils.dir/ShmStore.cpp.o"
	cd /home/zf/workspace_cpp/test5/utils && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/utils.dir/ShmStore.cpp.o -c /home/zf/workspace_cpp/test5/utils/ShmStore.cpp

utils/CMakeFiles/utils.dir/ShmStore.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utils.dir/ShmStore.cpp.i"
	cd /home/zf/workspace_cpp/test5/utils && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zf/workspace_cpp/test5/utils/ShmStore.cpp > CMakeFiles/utils.dir/ShmStore.cpp.i

utils/CMakeFiles/utils.dir/ShmStore.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utils.dir/ShmStore.cpp.s"
	cd /home/zf/workspace_cpp/test5/utils && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zf/workspace_cpp/test5/utils/ShmStore.cpp -o CMakeFiles/utils.dir/ShmStore.cpp.s

utils/CMakeFiles/utils.dir/ShmStore.cpp.o.requires:
.PHONY : utils/CMakeFiles/utils.dir/ShmStore.cpp.o.requires

utils/CMakeFiles/utils.dir/ShmStore.cpp.o.provides: utils/CMakeFiles/utils.dir/ShmStore.cpp.o.requires
	$(MAKE) -f utils/CMakeFiles/utils.dir/build.make utils/CMakeFiles/utils.dir/ShmStore.cpp.o.provides.build
.PHONY : utils/CMakeFiles/utils.dir/ShmStore.cpp.o.provides

utils/CMakeFiles/utils.dir/ShmStore.cpp.o.provides.build: utils/CMakeFiles/utils.dir/ShmStore.cpp.o

utils/CMakeFiles/utils.dir/Trace.cpp.o: utils/CMakeFiles/utils.dir/flags.make
utils/CMakeFiles/utils.dir/Trace.cpp.o: utils/Trace.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zf/workspace_cpp/test5/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object utils/CMakeFiles/utils.dir/Trace.cpp.o"
	cd /home/zf/workspace_cpp/test5/utils && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/utils.dir/Trace.cpp.o -c /home/zf/workspace_cpp/test5/utils/Trace.cpp

utils/CMakeFiles/utils.dir/Trace.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utils.dir/Trace.cpp.i"
	cd /home/zf/workspace_cpp/test5/utils && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zf/workspace_cpp/test5/utils/Trace.cpp > CMakeFiles/utils.dir/Trace.cpp.i

utils/CMakeFiles/utils.dir/Trace.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utils.dir/Trace.cpp.s"
	cd /home/zf/workspace_cpp/test5/utils && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zf/workspace_cpp/test5/utils/Trace.cpp -o CMakeFiles/utils.dir/Trace.cpp.s

utils/CMakeFiles/utils.dir/Trace.cpp.o.requires:
.PHONY : utils/CMakeFiles/utils.dir/Trace.cpp.o.requires

utils/CMakeFiles/utils.dir/Trace.cpp.o.provides: utils/CMakeFiles/utils.dir/Trace.cpp.o.requires
	$(MAKE) -f utils/CMakeFiles/utils.dir/build.make utils/CMakeFiles/utils.dir/Trace.cpp.o.provides.build
.PHONY : utils/CMakeFiles/utils.dir/Trace.cpp.o.provides

utils/CMakeFiles/utils.dir/Trace.cpp.o.provides.build: utils/CMakeFiles/utils.dir/Trace.cpp.o

utils: utils/CMakeFiles/utils.dir/ShmStore.cpp.o
utils: utils/CMakeFiles/utils.dir/Trace.cpp.o
utils: utils/CMakeFiles/utils.dir/build.make
.PHONY : utils

# Rule to build all files generated by this target.
utils/CMakeFiles/utils.dir/build: utils
.PHONY : utils/CMakeFiles/utils.dir/build

utils/CMakeFiles/utils.dir/requires: utils/CMakeFiles/utils.dir/ShmStore.cpp.o.requires
utils/CMakeFiles/utils.dir/requires: utils/CMakeFiles/utils.dir/Trace.cpp.o.requires
.PHONY : utils/CMakeFiles/utils.dir/requires

utils/CMakeFiles/utils.dir/clean:
	cd /home/zf/workspace_cpp/test5/utils && $(CMAKE_COMMAND) -P CMakeFiles/utils.dir/cmake_clean.cmake
.PHONY : utils/CMakeFiles/utils.dir/clean

utils/CMakeFiles/utils.dir/depend:
	cd /home/zf/workspace_cpp/test5 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zf/workspace_cpp/test5 /home/zf/workspace_cpp/test5/utils /home/zf/workspace_cpp/test5 /home/zf/workspace_cpp/test5/utils /home/zf/workspace_cpp/test5/utils/CMakeFiles/utils.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : utils/CMakeFiles/utils.dir/depend

