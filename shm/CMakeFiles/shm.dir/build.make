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
include shm/CMakeFiles/shm.dir/depend.make

# Include the progress variables for this target.
include shm/CMakeFiles/shm.dir/progress.make

# Include the compile flags for this target's objects.
include shm/CMakeFiles/shm.dir/flags.make

shm/CMakeFiles/shm.dir/Cell.cpp.o: shm/CMakeFiles/shm.dir/flags.make
shm/CMakeFiles/shm.dir/Cell.cpp.o: shm/Cell.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zf/workspace_cpp/test5/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object shm/CMakeFiles/shm.dir/Cell.cpp.o"
	cd /home/zf/workspace_cpp/test5/shm && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/shm.dir/Cell.cpp.o -c /home/zf/workspace_cpp/test5/shm/Cell.cpp

shm/CMakeFiles/shm.dir/Cell.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shm.dir/Cell.cpp.i"
	cd /home/zf/workspace_cpp/test5/shm && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zf/workspace_cpp/test5/shm/Cell.cpp > CMakeFiles/shm.dir/Cell.cpp.i

shm/CMakeFiles/shm.dir/Cell.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shm.dir/Cell.cpp.s"
	cd /home/zf/workspace_cpp/test5/shm && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zf/workspace_cpp/test5/shm/Cell.cpp -o CMakeFiles/shm.dir/Cell.cpp.s

shm/CMakeFiles/shm.dir/Cell.cpp.o.requires:
.PHONY : shm/CMakeFiles/shm.dir/Cell.cpp.o.requires

shm/CMakeFiles/shm.dir/Cell.cpp.o.provides: shm/CMakeFiles/shm.dir/Cell.cpp.o.requires
	$(MAKE) -f shm/CMakeFiles/shm.dir/build.make shm/CMakeFiles/shm.dir/Cell.cpp.o.provides.build
.PHONY : shm/CMakeFiles/shm.dir/Cell.cpp.o.provides

shm/CMakeFiles/shm.dir/Cell.cpp.o.provides.build: shm/CMakeFiles/shm.dir/Cell.cpp.o

shm/CMakeFiles/shm.dir/CmmQAlocException.cpp.o: shm/CMakeFiles/shm.dir/flags.make
shm/CMakeFiles/shm.dir/CmmQAlocException.cpp.o: shm/CmmQAlocException.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zf/workspace_cpp/test5/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object shm/CMakeFiles/shm.dir/CmmQAlocException.cpp.o"
	cd /home/zf/workspace_cpp/test5/shm && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/shm.dir/CmmQAlocException.cpp.o -c /home/zf/workspace_cpp/test5/shm/CmmQAlocException.cpp

shm/CMakeFiles/shm.dir/CmmQAlocException.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shm.dir/CmmQAlocException.cpp.i"
	cd /home/zf/workspace_cpp/test5/shm && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zf/workspace_cpp/test5/shm/CmmQAlocException.cpp > CMakeFiles/shm.dir/CmmQAlocException.cpp.i

shm/CMakeFiles/shm.dir/CmmQAlocException.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shm.dir/CmmQAlocException.cpp.s"
	cd /home/zf/workspace_cpp/test5/shm && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zf/workspace_cpp/test5/shm/CmmQAlocException.cpp -o CMakeFiles/shm.dir/CmmQAlocException.cpp.s

shm/CMakeFiles/shm.dir/CmmQAlocException.cpp.o.requires:
.PHONY : shm/CMakeFiles/shm.dir/CmmQAlocException.cpp.o.requires

shm/CMakeFiles/shm.dir/CmmQAlocException.cpp.o.provides: shm/CMakeFiles/shm.dir/CmmQAlocException.cpp.o.requires
	$(MAKE) -f shm/CMakeFiles/shm.dir/build.make shm/CMakeFiles/shm.dir/CmmQAlocException.cpp.o.provides.build
.PHONY : shm/CMakeFiles/shm.dir/CmmQAlocException.cpp.o.provides

shm/CMakeFiles/shm.dir/CmmQAlocException.cpp.o.provides.build: shm/CMakeFiles/shm.dir/CmmQAlocException.cpp.o

shm/CMakeFiles/shm.dir/MemInitException.cpp.o: shm/CMakeFiles/shm.dir/flags.make
shm/CMakeFiles/shm.dir/MemInitException.cpp.o: shm/MemInitException.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zf/workspace_cpp/test5/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object shm/CMakeFiles/shm.dir/MemInitException.cpp.o"
	cd /home/zf/workspace_cpp/test5/shm && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/shm.dir/MemInitException.cpp.o -c /home/zf/workspace_cpp/test5/shm/MemInitException.cpp

shm/CMakeFiles/shm.dir/MemInitException.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shm.dir/MemInitException.cpp.i"
	cd /home/zf/workspace_cpp/test5/shm && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zf/workspace_cpp/test5/shm/MemInitException.cpp > CMakeFiles/shm.dir/MemInitException.cpp.i

shm/CMakeFiles/shm.dir/MemInitException.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shm.dir/MemInitException.cpp.s"
	cd /home/zf/workspace_cpp/test5/shm && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zf/workspace_cpp/test5/shm/MemInitException.cpp -o CMakeFiles/shm.dir/MemInitException.cpp.s

shm/CMakeFiles/shm.dir/MemInitException.cpp.o.requires:
.PHONY : shm/CMakeFiles/shm.dir/MemInitException.cpp.o.requires

shm/CMakeFiles/shm.dir/MemInitException.cpp.o.provides: shm/CMakeFiles/shm.dir/MemInitException.cpp.o.requires
	$(MAKE) -f shm/CMakeFiles/shm.dir/build.make shm/CMakeFiles/shm.dir/MemInitException.cpp.o.provides.build
.PHONY : shm/CMakeFiles/shm.dir/MemInitException.cpp.o.provides

shm/CMakeFiles/shm.dir/MemInitException.cpp.o.provides.build: shm/CMakeFiles/shm.dir/MemInitException.cpp.o

shm/CMakeFiles/shm.dir/MemStorage.cpp.o: shm/CMakeFiles/shm.dir/flags.make
shm/CMakeFiles/shm.dir/MemStorage.cpp.o: shm/MemStorage.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zf/workspace_cpp/test5/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object shm/CMakeFiles/shm.dir/MemStorage.cpp.o"
	cd /home/zf/workspace_cpp/test5/shm && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/shm.dir/MemStorage.cpp.o -c /home/zf/workspace_cpp/test5/shm/MemStorage.cpp

shm/CMakeFiles/shm.dir/MemStorage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shm.dir/MemStorage.cpp.i"
	cd /home/zf/workspace_cpp/test5/shm && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zf/workspace_cpp/test5/shm/MemStorage.cpp > CMakeFiles/shm.dir/MemStorage.cpp.i

shm/CMakeFiles/shm.dir/MemStorage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shm.dir/MemStorage.cpp.s"
	cd /home/zf/workspace_cpp/test5/shm && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zf/workspace_cpp/test5/shm/MemStorage.cpp -o CMakeFiles/shm.dir/MemStorage.cpp.s

shm/CMakeFiles/shm.dir/MemStorage.cpp.o.requires:
.PHONY : shm/CMakeFiles/shm.dir/MemStorage.cpp.o.requires

shm/CMakeFiles/shm.dir/MemStorage.cpp.o.provides: shm/CMakeFiles/shm.dir/MemStorage.cpp.o.requires
	$(MAKE) -f shm/CMakeFiles/shm.dir/build.make shm/CMakeFiles/shm.dir/MemStorage.cpp.o.provides.build
.PHONY : shm/CMakeFiles/shm.dir/MemStorage.cpp.o.provides

shm/CMakeFiles/shm.dir/MemStorage.cpp.o.provides.build: shm/CMakeFiles/shm.dir/MemStorage.cpp.o

shm/CMakeFiles/shm.dir/TransitDataAllocException.cpp.o: shm/CMakeFiles/shm.dir/flags.make
shm/CMakeFiles/shm.dir/TransitDataAllocException.cpp.o: shm/TransitDataAllocException.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zf/workspace_cpp/test5/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object shm/CMakeFiles/shm.dir/TransitDataAllocException.cpp.o"
	cd /home/zf/workspace_cpp/test5/shm && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/shm.dir/TransitDataAllocException.cpp.o -c /home/zf/workspace_cpp/test5/shm/TransitDataAllocException.cpp

shm/CMakeFiles/shm.dir/TransitDataAllocException.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shm.dir/TransitDataAllocException.cpp.i"
	cd /home/zf/workspace_cpp/test5/shm && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zf/workspace_cpp/test5/shm/TransitDataAllocException.cpp > CMakeFiles/shm.dir/TransitDataAllocException.cpp.i

shm/CMakeFiles/shm.dir/TransitDataAllocException.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shm.dir/TransitDataAllocException.cpp.s"
	cd /home/zf/workspace_cpp/test5/shm && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zf/workspace_cpp/test5/shm/TransitDataAllocException.cpp -o CMakeFiles/shm.dir/TransitDataAllocException.cpp.s

shm/CMakeFiles/shm.dir/TransitDataAllocException.cpp.o.requires:
.PHONY : shm/CMakeFiles/shm.dir/TransitDataAllocException.cpp.o.requires

shm/CMakeFiles/shm.dir/TransitDataAllocException.cpp.o.provides: shm/CMakeFiles/shm.dir/TransitDataAllocException.cpp.o.requires
	$(MAKE) -f shm/CMakeFiles/shm.dir/build.make shm/CMakeFiles/shm.dir/TransitDataAllocException.cpp.o.provides.build
.PHONY : shm/CMakeFiles/shm.dir/TransitDataAllocException.cpp.o.provides

shm/CMakeFiles/shm.dir/TransitDataAllocException.cpp.o.provides.build: shm/CMakeFiles/shm.dir/TransitDataAllocException.cpp.o

shm: shm/CMakeFiles/shm.dir/Cell.cpp.o
shm: shm/CMakeFiles/shm.dir/CmmQAlocException.cpp.o
shm: shm/CMakeFiles/shm.dir/MemInitException.cpp.o
shm: shm/CMakeFiles/shm.dir/MemStorage.cpp.o
shm: shm/CMakeFiles/shm.dir/TransitDataAllocException.cpp.o
shm: shm/CMakeFiles/shm.dir/build.make
.PHONY : shm

# Rule to build all files generated by this target.
shm/CMakeFiles/shm.dir/build: shm
.PHONY : shm/CMakeFiles/shm.dir/build

shm/CMakeFiles/shm.dir/requires: shm/CMakeFiles/shm.dir/Cell.cpp.o.requires
shm/CMakeFiles/shm.dir/requires: shm/CMakeFiles/shm.dir/CmmQAlocException.cpp.o.requires
shm/CMakeFiles/shm.dir/requires: shm/CMakeFiles/shm.dir/MemInitException.cpp.o.requires
shm/CMakeFiles/shm.dir/requires: shm/CMakeFiles/shm.dir/MemStorage.cpp.o.requires
shm/CMakeFiles/shm.dir/requires: shm/CMakeFiles/shm.dir/TransitDataAllocException.cpp.o.requires
.PHONY : shm/CMakeFiles/shm.dir/requires

shm/CMakeFiles/shm.dir/clean:
	cd /home/zf/workspace_cpp/test5/shm && $(CMAKE_COMMAND) -P CMakeFiles/shm.dir/cmake_clean.cmake
.PHONY : shm/CMakeFiles/shm.dir/clean

shm/CMakeFiles/shm.dir/depend:
	cd /home/zf/workspace_cpp/test5 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zf/workspace_cpp/test5 /home/zf/workspace_cpp/test5/shm /home/zf/workspace_cpp/test5 /home/zf/workspace_cpp/test5/shm /home/zf/workspace_cpp/test5/shm/CMakeFiles/shm.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : shm/CMakeFiles/shm.dir/depend

