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
include test/basic/CMakeFiles/test_rcv.dir/depend.make

# Include the progress variables for this target.
include test/basic/CMakeFiles/test_rcv.dir/progress.make

# Include the compile flags for this target's objects.
include test/basic/CMakeFiles/test_rcv.dir/flags.make

test/basic/CMakeFiles/test_rcv.dir/TestRcver.cpp.o: test/basic/CMakeFiles/test_rcv.dir/flags.make
test/basic/CMakeFiles/test_rcv.dir/TestRcver.cpp.o: test/basic/TestRcver.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zf/workspace_cpp/test_5/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object test/basic/CMakeFiles/test_rcv.dir/TestRcver.cpp.o"
	cd /home/zf/workspace_cpp/test_5/test/basic && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/test_rcv.dir/TestRcver.cpp.o -c /home/zf/workspace_cpp/test_5/test/basic/TestRcver.cpp

test/basic/CMakeFiles/test_rcv.dir/TestRcver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_rcv.dir/TestRcver.cpp.i"
	cd /home/zf/workspace_cpp/test_5/test/basic && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zf/workspace_cpp/test_5/test/basic/TestRcver.cpp > CMakeFiles/test_rcv.dir/TestRcver.cpp.i

test/basic/CMakeFiles/test_rcv.dir/TestRcver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_rcv.dir/TestRcver.cpp.s"
	cd /home/zf/workspace_cpp/test_5/test/basic && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zf/workspace_cpp/test_5/test/basic/TestRcver.cpp -o CMakeFiles/test_rcv.dir/TestRcver.cpp.s

test/basic/CMakeFiles/test_rcv.dir/TestRcver.cpp.o.requires:
.PHONY : test/basic/CMakeFiles/test_rcv.dir/TestRcver.cpp.o.requires

test/basic/CMakeFiles/test_rcv.dir/TestRcver.cpp.o.provides: test/basic/CMakeFiles/test_rcv.dir/TestRcver.cpp.o.requires
	$(MAKE) -f test/basic/CMakeFiles/test_rcv.dir/build.make test/basic/CMakeFiles/test_rcv.dir/TestRcver.cpp.o.provides.build
.PHONY : test/basic/CMakeFiles/test_rcv.dir/TestRcver.cpp.o.provides

test/basic/CMakeFiles/test_rcv.dir/TestRcver.cpp.o.provides.build: test/basic/CMakeFiles/test_rcv.dir/TestRcver.cpp.o

# Object files for target test_rcv
test_rcv_OBJECTS = \
"CMakeFiles/test_rcv.dir/TestRcver.cpp.o"

# External object files for target test_rcv
test_rcv_EXTERNAL_OBJECTS =

bin/test_rcv: test/basic/CMakeFiles/test_rcv.dir/TestRcver.cpp.o
bin/test_rcv: test/basic/CMakeFiles/test_rcv.dir/build.make
bin/test_rcv: lib/libtest_4.so
bin/test_rcv: lib/libtestcommon.a
bin/test_rcv: test/basic/CMakeFiles/test_rcv.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../bin/test_rcv"
	cd /home/zf/workspace_cpp/test_5/test/basic && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_rcv.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/basic/CMakeFiles/test_rcv.dir/build: bin/test_rcv
.PHONY : test/basic/CMakeFiles/test_rcv.dir/build

test/basic/CMakeFiles/test_rcv.dir/requires: test/basic/CMakeFiles/test_rcv.dir/TestRcver.cpp.o.requires
.PHONY : test/basic/CMakeFiles/test_rcv.dir/requires

test/basic/CMakeFiles/test_rcv.dir/clean:
	cd /home/zf/workspace_cpp/test_5/test/basic && $(CMAKE_COMMAND) -P CMakeFiles/test_rcv.dir/cmake_clean.cmake
.PHONY : test/basic/CMakeFiles/test_rcv.dir/clean

test/basic/CMakeFiles/test_rcv.dir/depend:
	cd /home/zf/workspace_cpp/test_5 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zf/workspace_cpp/test_5 /home/zf/workspace_cpp/test_5/test/basic /home/zf/workspace_cpp/test_5 /home/zf/workspace_cpp/test_5/test/basic /home/zf/workspace_cpp/test_5/test/basic/CMakeFiles/test_rcv.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/basic/CMakeFiles/test_rcv.dir/depend

