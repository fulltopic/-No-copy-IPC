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
include test/monitortest/monitorchecker/CMakeFiles/freelistchecker.dir/depend.make

# Include the progress variables for this target.
include test/monitortest/monitorchecker/CMakeFiles/freelistchecker.dir/progress.make

# Include the compile flags for this target's objects.
include test/monitortest/monitorchecker/CMakeFiles/freelistchecker.dir/flags.make

test/monitortest/monitorchecker/CMakeFiles/freelistchecker.dir/FreeListChecker.cpp.o: test/monitortest/monitorchecker/CMakeFiles/freelistchecker.dir/flags.make
test/monitortest/monitorchecker/CMakeFiles/freelistchecker.dir/FreeListChecker.cpp.o: test/monitortest/monitorchecker/FreeListChecker.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zf/workspace_cpp/test_5/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object test/monitortest/monitorchecker/CMakeFiles/freelistchecker.dir/FreeListChecker.cpp.o"
	cd /home/zf/workspace_cpp/test_5/test/monitortest/monitorchecker && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/freelistchecker.dir/FreeListChecker.cpp.o -c /home/zf/workspace_cpp/test_5/test/monitortest/monitorchecker/FreeListChecker.cpp

test/monitortest/monitorchecker/CMakeFiles/freelistchecker.dir/FreeListChecker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/freelistchecker.dir/FreeListChecker.cpp.i"
	cd /home/zf/workspace_cpp/test_5/test/monitortest/monitorchecker && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zf/workspace_cpp/test_5/test/monitortest/monitorchecker/FreeListChecker.cpp > CMakeFiles/freelistchecker.dir/FreeListChecker.cpp.i

test/monitortest/monitorchecker/CMakeFiles/freelistchecker.dir/FreeListChecker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/freelistchecker.dir/FreeListChecker.cpp.s"
	cd /home/zf/workspace_cpp/test_5/test/monitortest/monitorchecker && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zf/workspace_cpp/test_5/test/monitortest/monitorchecker/FreeListChecker.cpp -o CMakeFiles/freelistchecker.dir/FreeListChecker.cpp.s

test/monitortest/monitorchecker/CMakeFiles/freelistchecker.dir/FreeListChecker.cpp.o.requires:
.PHONY : test/monitortest/monitorchecker/CMakeFiles/freelistchecker.dir/FreeListChecker.cpp.o.requires

test/monitortest/monitorchecker/CMakeFiles/freelistchecker.dir/FreeListChecker.cpp.o.provides: test/monitortest/monitorchecker/CMakeFiles/freelistchecker.dir/FreeListChecker.cpp.o.requires
	$(MAKE) -f test/monitortest/monitorchecker/CMakeFiles/freelistchecker.dir/build.make test/monitortest/monitorchecker/CMakeFiles/freelistchecker.dir/FreeListChecker.cpp.o.provides.build
.PHONY : test/monitortest/monitorchecker/CMakeFiles/freelistchecker.dir/FreeListChecker.cpp.o.provides

test/monitortest/monitorchecker/CMakeFiles/freelistchecker.dir/FreeListChecker.cpp.o.provides.build: test/monitortest/monitorchecker/CMakeFiles/freelistchecker.dir/FreeListChecker.cpp.o

# Object files for target freelistchecker
freelistchecker_OBJECTS = \
"CMakeFiles/freelistchecker.dir/FreeListChecker.cpp.o"

# External object files for target freelistchecker
freelistchecker_EXTERNAL_OBJECTS =

bin/freelistchecker: test/monitortest/monitorchecker/CMakeFiles/freelistchecker.dir/FreeListChecker.cpp.o
bin/freelistchecker: test/monitortest/monitorchecker/CMakeFiles/freelistchecker.dir/build.make
bin/freelistchecker: lib/libtest_4.so
bin/freelistchecker: lib/libtestcommon.a
bin/freelistchecker: test/monitortest/monitorchecker/CMakeFiles/freelistchecker.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../../bin/freelistchecker"
	cd /home/zf/workspace_cpp/test_5/test/monitortest/monitorchecker && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/freelistchecker.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/monitortest/monitorchecker/CMakeFiles/freelistchecker.dir/build: bin/freelistchecker
.PHONY : test/monitortest/monitorchecker/CMakeFiles/freelistchecker.dir/build

test/monitortest/monitorchecker/CMakeFiles/freelistchecker.dir/requires: test/monitortest/monitorchecker/CMakeFiles/freelistchecker.dir/FreeListChecker.cpp.o.requires
.PHONY : test/monitortest/monitorchecker/CMakeFiles/freelistchecker.dir/requires

test/monitortest/monitorchecker/CMakeFiles/freelistchecker.dir/clean:
	cd /home/zf/workspace_cpp/test_5/test/monitortest/monitorchecker && $(CMAKE_COMMAND) -P CMakeFiles/freelistchecker.dir/cmake_clean.cmake
.PHONY : test/monitortest/monitorchecker/CMakeFiles/freelistchecker.dir/clean

test/monitortest/monitorchecker/CMakeFiles/freelistchecker.dir/depend:
	cd /home/zf/workspace_cpp/test_5 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zf/workspace_cpp/test_5 /home/zf/workspace_cpp/test_5/test/monitortest/monitorchecker /home/zf/workspace_cpp/test_5 /home/zf/workspace_cpp/test_5/test/monitortest/monitorchecker /home/zf/workspace_cpp/test_5/test/monitortest/monitorchecker/CMakeFiles/freelistchecker.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/monitortest/monitorchecker/CMakeFiles/freelistchecker.dir/depend

