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
include test/counter12N/CMakeFiles/test_monitorcnt12n.dir/depend.make

# Include the progress variables for this target.
include test/counter12N/CMakeFiles/test_monitorcnt12n.dir/progress.make

# Include the compile flags for this target's objects.
include test/counter12N/CMakeFiles/test_monitorcnt12n.dir/flags.make

test/counter12N/CMakeFiles/test_monitorcnt12n.dir/TestMonitorCnt.cpp.o: test/counter12N/CMakeFiles/test_monitorcnt12n.dir/flags.make
test/counter12N/CMakeFiles/test_monitorcnt12n.dir/TestMonitorCnt.cpp.o: test/counter12N/TestMonitorCnt.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zf/workspace_cpp/test_5/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object test/counter12N/CMakeFiles/test_monitorcnt12n.dir/TestMonitorCnt.cpp.o"
	cd /home/zf/workspace_cpp/test_5/test/counter12N && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/test_monitorcnt12n.dir/TestMonitorCnt.cpp.o -c /home/zf/workspace_cpp/test_5/test/counter12N/TestMonitorCnt.cpp

test/counter12N/CMakeFiles/test_monitorcnt12n.dir/TestMonitorCnt.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_monitorcnt12n.dir/TestMonitorCnt.cpp.i"
	cd /home/zf/workspace_cpp/test_5/test/counter12N && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zf/workspace_cpp/test_5/test/counter12N/TestMonitorCnt.cpp > CMakeFiles/test_monitorcnt12n.dir/TestMonitorCnt.cpp.i

test/counter12N/CMakeFiles/test_monitorcnt12n.dir/TestMonitorCnt.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_monitorcnt12n.dir/TestMonitorCnt.cpp.s"
	cd /home/zf/workspace_cpp/test_5/test/counter12N && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zf/workspace_cpp/test_5/test/counter12N/TestMonitorCnt.cpp -o CMakeFiles/test_monitorcnt12n.dir/TestMonitorCnt.cpp.s

test/counter12N/CMakeFiles/test_monitorcnt12n.dir/TestMonitorCnt.cpp.o.requires:
.PHONY : test/counter12N/CMakeFiles/test_monitorcnt12n.dir/TestMonitorCnt.cpp.o.requires

test/counter12N/CMakeFiles/test_monitorcnt12n.dir/TestMonitorCnt.cpp.o.provides: test/counter12N/CMakeFiles/test_monitorcnt12n.dir/TestMonitorCnt.cpp.o.requires
	$(MAKE) -f test/counter12N/CMakeFiles/test_monitorcnt12n.dir/build.make test/counter12N/CMakeFiles/test_monitorcnt12n.dir/TestMonitorCnt.cpp.o.provides.build
.PHONY : test/counter12N/CMakeFiles/test_monitorcnt12n.dir/TestMonitorCnt.cpp.o.provides

test/counter12N/CMakeFiles/test_monitorcnt12n.dir/TestMonitorCnt.cpp.o.provides.build: test/counter12N/CMakeFiles/test_monitorcnt12n.dir/TestMonitorCnt.cpp.o

# Object files for target test_monitorcnt12n
test_monitorcnt12n_OBJECTS = \
"CMakeFiles/test_monitorcnt12n.dir/TestMonitorCnt.cpp.o"

# External object files for target test_monitorcnt12n
test_monitorcnt12n_EXTERNAL_OBJECTS =

bin/test_monitorcnt12n: test/counter12N/CMakeFiles/test_monitorcnt12n.dir/TestMonitorCnt.cpp.o
bin/test_monitorcnt12n: test/counter12N/CMakeFiles/test_monitorcnt12n.dir/build.make
bin/test_monitorcnt12n: lib/libtest_4.so
bin/test_monitorcnt12n: lib/libtestcommon.a
bin/test_monitorcnt12n: test/counter12N/CMakeFiles/test_monitorcnt12n.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../bin/test_monitorcnt12n"
	cd /home/zf/workspace_cpp/test_5/test/counter12N && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_monitorcnt12n.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/counter12N/CMakeFiles/test_monitorcnt12n.dir/build: bin/test_monitorcnt12n
.PHONY : test/counter12N/CMakeFiles/test_monitorcnt12n.dir/build

test/counter12N/CMakeFiles/test_monitorcnt12n.dir/requires: test/counter12N/CMakeFiles/test_monitorcnt12n.dir/TestMonitorCnt.cpp.o.requires
.PHONY : test/counter12N/CMakeFiles/test_monitorcnt12n.dir/requires

test/counter12N/CMakeFiles/test_monitorcnt12n.dir/clean:
	cd /home/zf/workspace_cpp/test_5/test/counter12N && $(CMAKE_COMMAND) -P CMakeFiles/test_monitorcnt12n.dir/cmake_clean.cmake
.PHONY : test/counter12N/CMakeFiles/test_monitorcnt12n.dir/clean

test/counter12N/CMakeFiles/test_monitorcnt12n.dir/depend:
	cd /home/zf/workspace_cpp/test_5 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zf/workspace_cpp/test_5 /home/zf/workspace_cpp/test_5/test/counter12N /home/zf/workspace_cpp/test_5 /home/zf/workspace_cpp/test_5/test/counter12N /home/zf/workspace_cpp/test_5/test/counter12N/CMakeFiles/test_monitorcnt12n.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/counter12N/CMakeFiles/test_monitorcnt12n.dir/depend

