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
include test/countercommon/CMakeFiles/readCounter.dir/depend.make

# Include the progress variables for this target.
include test/countercommon/CMakeFiles/readCounter.dir/progress.make

# Include the compile flags for this target's objects.
include test/countercommon/CMakeFiles/readCounter.dir/flags.make

test/countercommon/CMakeFiles/readCounter.dir/ReadCounter.cpp.o: test/countercommon/CMakeFiles/readCounter.dir/flags.make
test/countercommon/CMakeFiles/readCounter.dir/ReadCounter.cpp.o: test/countercommon/ReadCounter.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zf/workspace_cpp/test_5/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object test/countercommon/CMakeFiles/readCounter.dir/ReadCounter.cpp.o"
	cd /home/zf/workspace_cpp/test_5/test/countercommon && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/readCounter.dir/ReadCounter.cpp.o -c /home/zf/workspace_cpp/test_5/test/countercommon/ReadCounter.cpp

test/countercommon/CMakeFiles/readCounter.dir/ReadCounter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/readCounter.dir/ReadCounter.cpp.i"
	cd /home/zf/workspace_cpp/test_5/test/countercommon && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zf/workspace_cpp/test_5/test/countercommon/ReadCounter.cpp > CMakeFiles/readCounter.dir/ReadCounter.cpp.i

test/countercommon/CMakeFiles/readCounter.dir/ReadCounter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/readCounter.dir/ReadCounter.cpp.s"
	cd /home/zf/workspace_cpp/test_5/test/countercommon && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zf/workspace_cpp/test_5/test/countercommon/ReadCounter.cpp -o CMakeFiles/readCounter.dir/ReadCounter.cpp.s

test/countercommon/CMakeFiles/readCounter.dir/ReadCounter.cpp.o.requires:
.PHONY : test/countercommon/CMakeFiles/readCounter.dir/ReadCounter.cpp.o.requires

test/countercommon/CMakeFiles/readCounter.dir/ReadCounter.cpp.o.provides: test/countercommon/CMakeFiles/readCounter.dir/ReadCounter.cpp.o.requires
	$(MAKE) -f test/countercommon/CMakeFiles/readCounter.dir/build.make test/countercommon/CMakeFiles/readCounter.dir/ReadCounter.cpp.o.provides.build
.PHONY : test/countercommon/CMakeFiles/readCounter.dir/ReadCounter.cpp.o.provides

test/countercommon/CMakeFiles/readCounter.dir/ReadCounter.cpp.o.provides.build: test/countercommon/CMakeFiles/readCounter.dir/ReadCounter.cpp.o

# Object files for target readCounter
readCounter_OBJECTS = \
"CMakeFiles/readCounter.dir/ReadCounter.cpp.o"

# External object files for target readCounter
readCounter_EXTERNAL_OBJECTS =

bin/readCounter: test/countercommon/CMakeFiles/readCounter.dir/ReadCounter.cpp.o
bin/readCounter: test/countercommon/CMakeFiles/readCounter.dir/build.make
bin/readCounter: lib/libtest_4.so
bin/readCounter: lib/libtestcommon.a
bin/readCounter: test/countercommon/CMakeFiles/readCounter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../bin/readCounter"
	cd /home/zf/workspace_cpp/test_5/test/countercommon && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/readCounter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/countercommon/CMakeFiles/readCounter.dir/build: bin/readCounter
.PHONY : test/countercommon/CMakeFiles/readCounter.dir/build

test/countercommon/CMakeFiles/readCounter.dir/requires: test/countercommon/CMakeFiles/readCounter.dir/ReadCounter.cpp.o.requires
.PHONY : test/countercommon/CMakeFiles/readCounter.dir/requires

test/countercommon/CMakeFiles/readCounter.dir/clean:
	cd /home/zf/workspace_cpp/test_5/test/countercommon && $(CMAKE_COMMAND) -P CMakeFiles/readCounter.dir/cmake_clean.cmake
.PHONY : test/countercommon/CMakeFiles/readCounter.dir/clean

test/countercommon/CMakeFiles/readCounter.dir/depend:
	cd /home/zf/workspace_cpp/test_5 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zf/workspace_cpp/test_5 /home/zf/workspace_cpp/test_5/test/countercommon /home/zf/workspace_cpp/test_5 /home/zf/workspace_cpp/test_5/test/countercommon /home/zf/workspace_cpp/test_5/test/countercommon/CMakeFiles/readCounter.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/countercommon/CMakeFiles/readCounter.dir/depend

