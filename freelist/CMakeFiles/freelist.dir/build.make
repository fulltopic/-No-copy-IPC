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
include freelist/CMakeFiles/freelist.dir/depend.make

# Include the progress variables for this target.
include freelist/CMakeFiles/freelist.dir/progress.make

# Include the compile flags for this target's objects.
include freelist/CMakeFiles/freelist.dir/flags.make

freelist/CMakeFiles/freelist.dir/CellBlock.cpp.o: freelist/CMakeFiles/freelist.dir/flags.make
freelist/CMakeFiles/freelist.dir/CellBlock.cpp.o: freelist/CellBlock.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zf/workspace_cpp/test5/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object freelist/CMakeFiles/freelist.dir/CellBlock.cpp.o"
	cd /home/zf/workspace_cpp/test5/freelist && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/freelist.dir/CellBlock.cpp.o -c /home/zf/workspace_cpp/test5/freelist/CellBlock.cpp

freelist/CMakeFiles/freelist.dir/CellBlock.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/freelist.dir/CellBlock.cpp.i"
	cd /home/zf/workspace_cpp/test5/freelist && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zf/workspace_cpp/test5/freelist/CellBlock.cpp > CMakeFiles/freelist.dir/CellBlock.cpp.i

freelist/CMakeFiles/freelist.dir/CellBlock.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/freelist.dir/CellBlock.cpp.s"
	cd /home/zf/workspace_cpp/test5/freelist && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zf/workspace_cpp/test5/freelist/CellBlock.cpp -o CMakeFiles/freelist.dir/CellBlock.cpp.s

freelist/CMakeFiles/freelist.dir/CellBlock.cpp.o.requires:
.PHONY : freelist/CMakeFiles/freelist.dir/CellBlock.cpp.o.requires

freelist/CMakeFiles/freelist.dir/CellBlock.cpp.o.provides: freelist/CMakeFiles/freelist.dir/CellBlock.cpp.o.requires
	$(MAKE) -f freelist/CMakeFiles/freelist.dir/build.make freelist/CMakeFiles/freelist.dir/CellBlock.cpp.o.provides.build
.PHONY : freelist/CMakeFiles/freelist.dir/CellBlock.cpp.o.provides

freelist/CMakeFiles/freelist.dir/CellBlock.cpp.o.provides.build: freelist/CMakeFiles/freelist.dir/CellBlock.cpp.o

freelist/CMakeFiles/freelist.dir/GlobalFreeList.cpp.o: freelist/CMakeFiles/freelist.dir/flags.make
freelist/CMakeFiles/freelist.dir/GlobalFreeList.cpp.o: freelist/GlobalFreeList.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zf/workspace_cpp/test5/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object freelist/CMakeFiles/freelist.dir/GlobalFreeList.cpp.o"
	cd /home/zf/workspace_cpp/test5/freelist && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/freelist.dir/GlobalFreeList.cpp.o -c /home/zf/workspace_cpp/test5/freelist/GlobalFreeList.cpp

freelist/CMakeFiles/freelist.dir/GlobalFreeList.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/freelist.dir/GlobalFreeList.cpp.i"
	cd /home/zf/workspace_cpp/test5/freelist && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zf/workspace_cpp/test5/freelist/GlobalFreeList.cpp > CMakeFiles/freelist.dir/GlobalFreeList.cpp.i

freelist/CMakeFiles/freelist.dir/GlobalFreeList.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/freelist.dir/GlobalFreeList.cpp.s"
	cd /home/zf/workspace_cpp/test5/freelist && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zf/workspace_cpp/test5/freelist/GlobalFreeList.cpp -o CMakeFiles/freelist.dir/GlobalFreeList.cpp.s

freelist/CMakeFiles/freelist.dir/GlobalFreeList.cpp.o.requires:
.PHONY : freelist/CMakeFiles/freelist.dir/GlobalFreeList.cpp.o.requires

freelist/CMakeFiles/freelist.dir/GlobalFreeList.cpp.o.provides: freelist/CMakeFiles/freelist.dir/GlobalFreeList.cpp.o.requires
	$(MAKE) -f freelist/CMakeFiles/freelist.dir/build.make freelist/CMakeFiles/freelist.dir/GlobalFreeList.cpp.o.provides.build
.PHONY : freelist/CMakeFiles/freelist.dir/GlobalFreeList.cpp.o.provides

freelist/CMakeFiles/freelist.dir/GlobalFreeList.cpp.o.provides.build: freelist/CMakeFiles/freelist.dir/GlobalFreeList.cpp.o

freelist/CMakeFiles/freelist.dir/LocalFreeList.cpp.o: freelist/CMakeFiles/freelist.dir/flags.make
freelist/CMakeFiles/freelist.dir/LocalFreeList.cpp.o: freelist/LocalFreeList.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zf/workspace_cpp/test5/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object freelist/CMakeFiles/freelist.dir/LocalFreeList.cpp.o"
	cd /home/zf/workspace_cpp/test5/freelist && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/freelist.dir/LocalFreeList.cpp.o -c /home/zf/workspace_cpp/test5/freelist/LocalFreeList.cpp

freelist/CMakeFiles/freelist.dir/LocalFreeList.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/freelist.dir/LocalFreeList.cpp.i"
	cd /home/zf/workspace_cpp/test5/freelist && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zf/workspace_cpp/test5/freelist/LocalFreeList.cpp > CMakeFiles/freelist.dir/LocalFreeList.cpp.i

freelist/CMakeFiles/freelist.dir/LocalFreeList.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/freelist.dir/LocalFreeList.cpp.s"
	cd /home/zf/workspace_cpp/test5/freelist && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zf/workspace_cpp/test5/freelist/LocalFreeList.cpp -o CMakeFiles/freelist.dir/LocalFreeList.cpp.s

freelist/CMakeFiles/freelist.dir/LocalFreeList.cpp.o.requires:
.PHONY : freelist/CMakeFiles/freelist.dir/LocalFreeList.cpp.o.requires

freelist/CMakeFiles/freelist.dir/LocalFreeList.cpp.o.provides: freelist/CMakeFiles/freelist.dir/LocalFreeList.cpp.o.requires
	$(MAKE) -f freelist/CMakeFiles/freelist.dir/build.make freelist/CMakeFiles/freelist.dir/LocalFreeList.cpp.o.provides.build
.PHONY : freelist/CMakeFiles/freelist.dir/LocalFreeList.cpp.o.provides

freelist/CMakeFiles/freelist.dir/LocalFreeList.cpp.o.provides.build: freelist/CMakeFiles/freelist.dir/LocalFreeList.cpp.o

freelist: freelist/CMakeFiles/freelist.dir/CellBlock.cpp.o
freelist: freelist/CMakeFiles/freelist.dir/GlobalFreeList.cpp.o
freelist: freelist/CMakeFiles/freelist.dir/LocalFreeList.cpp.o
freelist: freelist/CMakeFiles/freelist.dir/build.make
.PHONY : freelist

# Rule to build all files generated by this target.
freelist/CMakeFiles/freelist.dir/build: freelist
.PHONY : freelist/CMakeFiles/freelist.dir/build

freelist/CMakeFiles/freelist.dir/requires: freelist/CMakeFiles/freelist.dir/CellBlock.cpp.o.requires
freelist/CMakeFiles/freelist.dir/requires: freelist/CMakeFiles/freelist.dir/GlobalFreeList.cpp.o.requires
freelist/CMakeFiles/freelist.dir/requires: freelist/CMakeFiles/freelist.dir/LocalFreeList.cpp.o.requires
.PHONY : freelist/CMakeFiles/freelist.dir/requires

freelist/CMakeFiles/freelist.dir/clean:
	cd /home/zf/workspace_cpp/test5/freelist && $(CMAKE_COMMAND) -P CMakeFiles/freelist.dir/cmake_clean.cmake
.PHONY : freelist/CMakeFiles/freelist.dir/clean

freelist/CMakeFiles/freelist.dir/depend:
	cd /home/zf/workspace_cpp/test5 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zf/workspace_cpp/test5 /home/zf/workspace_cpp/test5/freelist /home/zf/workspace_cpp/test5 /home/zf/workspace_cpp/test5/freelist /home/zf/workspace_cpp/test5/freelist/CMakeFiles/freelist.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : freelist/CMakeFiles/freelist.dir/depend

