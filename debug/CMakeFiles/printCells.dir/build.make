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
CMAKE_SOURCE_DIR = /home/zf/workspace_cpp/test_5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zf/workspace_cpp/test_5

# Include any dependencies generated for this target.
include debug/CMakeFiles/printCells.dir/depend.make

# Include the progress variables for this target.
include debug/CMakeFiles/printCells.dir/progress.make

# Include the compile flags for this target's objects.
include debug/CMakeFiles/printCells.dir/flags.make

debug/CMakeFiles/printCells.dir/ShowCells.cpp.o: debug/CMakeFiles/printCells.dir/flags.make
debug/CMakeFiles/printCells.dir/ShowCells.cpp.o: debug/ShowCells.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zf/workspace_cpp/test_5/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object debug/CMakeFiles/printCells.dir/ShowCells.cpp.o"
	cd /home/zf/workspace_cpp/test_5/debug && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/printCells.dir/ShowCells.cpp.o -c /home/zf/workspace_cpp/test_5/debug/ShowCells.cpp

debug/CMakeFiles/printCells.dir/ShowCells.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/printCells.dir/ShowCells.cpp.i"
	cd /home/zf/workspace_cpp/test_5/debug && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zf/workspace_cpp/test_5/debug/ShowCells.cpp > CMakeFiles/printCells.dir/ShowCells.cpp.i

debug/CMakeFiles/printCells.dir/ShowCells.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/printCells.dir/ShowCells.cpp.s"
	cd /home/zf/workspace_cpp/test_5/debug && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zf/workspace_cpp/test_5/debug/ShowCells.cpp -o CMakeFiles/printCells.dir/ShowCells.cpp.s

debug/CMakeFiles/printCells.dir/ShowCells.cpp.o.requires:
.PHONY : debug/CMakeFiles/printCells.dir/ShowCells.cpp.o.requires

debug/CMakeFiles/printCells.dir/ShowCells.cpp.o.provides: debug/CMakeFiles/printCells.dir/ShowCells.cpp.o.requires
	$(MAKE) -f debug/CMakeFiles/printCells.dir/build.make debug/CMakeFiles/printCells.dir/ShowCells.cpp.o.provides.build
.PHONY : debug/CMakeFiles/printCells.dir/ShowCells.cpp.o.provides

debug/CMakeFiles/printCells.dir/ShowCells.cpp.o.provides.build: debug/CMakeFiles/printCells.dir/ShowCells.cpp.o

# Object files for target printCells
printCells_OBJECTS = \
"CMakeFiles/printCells.dir/ShowCells.cpp.o"

# External object files for target printCells
printCells_EXTERNAL_OBJECTS =

bin/printCells: debug/CMakeFiles/printCells.dir/ShowCells.cpp.o
bin/printCells: debug/CMakeFiles/printCells.dir/build.make
bin/printCells: lib/libtest_4.so
bin/printCells: debug/CMakeFiles/printCells.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../bin/printCells"
	cd /home/zf/workspace_cpp/test_5/debug && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/printCells.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
debug/CMakeFiles/printCells.dir/build: bin/printCells
.PHONY : debug/CMakeFiles/printCells.dir/build

debug/CMakeFiles/printCells.dir/requires: debug/CMakeFiles/printCells.dir/ShowCells.cpp.o.requires
.PHONY : debug/CMakeFiles/printCells.dir/requires

debug/CMakeFiles/printCells.dir/clean:
	cd /home/zf/workspace_cpp/test_5/debug && $(CMAKE_COMMAND) -P CMakeFiles/printCells.dir/cmake_clean.cmake
.PHONY : debug/CMakeFiles/printCells.dir/clean

debug/CMakeFiles/printCells.dir/depend:
	cd /home/zf/workspace_cpp/test_5 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zf/workspace_cpp/test_5 /home/zf/workspace_cpp/test_5/debug /home/zf/workspace_cpp/test_5 /home/zf/workspace_cpp/test_5/debug /home/zf/workspace_cpp/test_5/debug/CMakeFiles/printCells.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : debug/CMakeFiles/printCells.dir/depend

