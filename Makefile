# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

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

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/zf/workspace_cpp/test_5/CMakeFiles /home/zf/workspace_cpp/test_5/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/zf/workspace_cpp/test_5/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named test_4

# Build rule for target.
test_4: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_4
.PHONY : test_4

# fast build rule for target.
test_4/fast:
	$(MAKE) -f CMakeFiles/test_4.dir/build.make CMakeFiles/test_4.dir/build
.PHONY : test_4/fast

#=============================================================================
# Target rules for targets named comm

# Build rule for target.
comm: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 comm
.PHONY : comm

# fast build rule for target.
comm/fast:
	$(MAKE) -f comm/CMakeFiles/comm.dir/build.make comm/CMakeFiles/comm.dir/build
.PHONY : comm/fast

#=============================================================================
# Target rules for targets named freelist

# Build rule for target.
freelist: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 freelist
.PHONY : freelist

# fast build rule for target.
freelist/fast:
	$(MAKE) -f freelist/CMakeFiles/freelist.dir/build.make freelist/CMakeFiles/freelist.dir/build
.PHONY : freelist/fast

#=============================================================================
# Target rules for targets named monitor

# Build rule for target.
monitor: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 monitor
.PHONY : monitor

# fast build rule for target.
monitor/fast:
	$(MAKE) -f monitor/CMakeFiles/monitor.dir/build.make monitor/CMakeFiles/monitor.dir/build
.PHONY : monitor/fast

#=============================================================================
# Target rules for targets named proxy

# Build rule for target.
proxy: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 proxy
.PHONY : proxy

# fast build rule for target.
proxy/fast:
	$(MAKE) -f proxy/CMakeFiles/proxy.dir/build.make proxy/CMakeFiles/proxy.dir/build
.PHONY : proxy/fast

#=============================================================================
# Target rules for targets named shm

# Build rule for target.
shm: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 shm
.PHONY : shm

# fast build rule for target.
shm/fast:
	$(MAKE) -f shm/CMakeFiles/shm.dir/build.make shm/CMakeFiles/shm.dir/build
.PHONY : shm/fast

#=============================================================================
# Target rules for targets named utils

# Build rule for target.
utils: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 utils
.PHONY : utils

# fast build rule for target.
utils/fast:
	$(MAKE) -f utils/CMakeFiles/utils.dir/build.make utils/CMakeFiles/utils.dir/build
.PHONY : utils/fast

#=============================================================================
# Target rules for targets named testcommon

# Build rule for target.
testcommon: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 testcommon
.PHONY : testcommon

# fast build rule for target.
testcommon/fast:
	$(MAKE) -f test/common/CMakeFiles/testcommon.dir/build.make test/common/CMakeFiles/testcommon.dir/build
.PHONY : testcommon/fast

#=============================================================================
# Target rules for targets named readCounter

# Build rule for target.
readCounter: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 readCounter
.PHONY : readCounter

# fast build rule for target.
readCounter/fast:
	$(MAKE) -f test/countercommon/CMakeFiles/readCounter.dir/build.make test/countercommon/CMakeFiles/readCounter.dir/build
.PHONY : readCounter/fast

#=============================================================================
# Target rules for targets named test_monitor

# Build rule for target.
test_monitor: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_monitor
.PHONY : test_monitor

# fast build rule for target.
test_monitor/fast:
	$(MAKE) -f test/basic/CMakeFiles/test_monitor.dir/build.make test/basic/CMakeFiles/test_monitor.dir/build
.PHONY : test_monitor/fast

#=============================================================================
# Target rules for targets named test_rcv

# Build rule for target.
test_rcv: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_rcv
.PHONY : test_rcv

# fast build rule for target.
test_rcv/fast:
	$(MAKE) -f test/basic/CMakeFiles/test_rcv.dir/build.make test/basic/CMakeFiles/test_rcv.dir/build
.PHONY : test_rcv/fast

#=============================================================================
# Target rules for targets named test_snd

# Build rule for target.
test_snd: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_snd
.PHONY : test_snd

# fast build rule for target.
test_snd/fast:
	$(MAKE) -f test/basic/CMakeFiles/test_snd.dir/build.make test/basic/CMakeFiles/test_snd.dir/build
.PHONY : test_snd/fast

#=============================================================================
# Target rules for targets named test_monitorcnt

# Build rule for target.
test_monitorcnt: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_monitorcnt
.PHONY : test_monitorcnt

# fast build rule for target.
test_monitorcnt/fast:
	$(MAKE) -f test/counterN21/CMakeFiles/test_monitorcnt.dir/build.make test/counterN21/CMakeFiles/test_monitorcnt.dir/build
.PHONY : test_monitorcnt/fast

#=============================================================================
# Target rules for targets named test_rcvcnt

# Build rule for target.
test_rcvcnt: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_rcvcnt
.PHONY : test_rcvcnt

# fast build rule for target.
test_rcvcnt/fast:
	$(MAKE) -f test/counterN21/CMakeFiles/test_rcvcnt.dir/build.make test/counterN21/CMakeFiles/test_rcvcnt.dir/build
.PHONY : test_rcvcnt/fast

#=============================================================================
# Target rules for targets named test_sndcnt

# Build rule for target.
test_sndcnt: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_sndcnt
.PHONY : test_sndcnt

# fast build rule for target.
test_sndcnt/fast:
	$(MAKE) -f test/counterN21/CMakeFiles/test_sndcnt.dir/build.make test/counterN21/CMakeFiles/test_sndcnt.dir/build
.PHONY : test_sndcnt/fast

#=============================================================================
# Target rules for targets named test_monitorcnt12n

# Build rule for target.
test_monitorcnt12n: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_monitorcnt12n
.PHONY : test_monitorcnt12n

# fast build rule for target.
test_monitorcnt12n/fast:
	$(MAKE) -f test/counter12N/CMakeFiles/test_monitorcnt12n.dir/build.make test/counter12N/CMakeFiles/test_monitorcnt12n.dir/build
.PHONY : test_monitorcnt12n/fast

#=============================================================================
# Target rules for targets named test_rcvcnt12n

# Build rule for target.
test_rcvcnt12n: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_rcvcnt12n
.PHONY : test_rcvcnt12n

# fast build rule for target.
test_rcvcnt12n/fast:
	$(MAKE) -f test/counter12N/CMakeFiles/test_rcvcnt12n.dir/build.make test/counter12N/CMakeFiles/test_rcvcnt12n.dir/build
.PHONY : test_rcvcnt12n/fast

#=============================================================================
# Target rules for targets named test_sndcnt12n

# Build rule for target.
test_sndcnt12n: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_sndcnt12n
.PHONY : test_sndcnt12n

# fast build rule for target.
test_sndcnt12n/fast:
	$(MAKE) -f test/counter12N/CMakeFiles/test_sndcnt12n.dir/build.make test/counter12N/CMakeFiles/test_sndcnt12n.dir/build
.PHONY : test_sndcnt12n/fast

#=============================================================================
# Target rules for targets named test_monitorcntnn

# Build rule for target.
test_monitorcntnn: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_monitorcntnn
.PHONY : test_monitorcntnn

# fast build rule for target.
test_monitorcntnn/fast:
	$(MAKE) -f test/counterN2N/CMakeFiles/test_monitorcntnn.dir/build.make test/counterN2N/CMakeFiles/test_monitorcntnn.dir/build
.PHONY : test_monitorcntnn/fast

#=============================================================================
# Target rules for targets named test_rcvcntnn

# Build rule for target.
test_rcvcntnn: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_rcvcntnn
.PHONY : test_rcvcntnn

# fast build rule for target.
test_rcvcntnn/fast:
	$(MAKE) -f test/counterN2N/CMakeFiles/test_rcvcntnn.dir/build.make test/counterN2N/CMakeFiles/test_rcvcntnn.dir/build
.PHONY : test_rcvcntnn/fast

#=============================================================================
# Target rules for targets named test_sndcntnn

# Build rule for target.
test_sndcntnn: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_sndcntnn
.PHONY : test_sndcntnn

# fast build rule for target.
test_sndcntnn/fast:
	$(MAKE) -f test/counterN2N/CMakeFiles/test_sndcntnn.dir/build.make test/counterN2N/CMakeFiles/test_sndcntnn.dir/build
.PHONY : test_sndcntnn/fast

#=============================================================================
# Target rules for targets named freelistchecker

# Build rule for target.
freelistchecker: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 freelistchecker
.PHONY : freelistchecker

# fast build rule for target.
freelistchecker/fast:
	$(MAKE) -f test/monitortest/monitorchecker/CMakeFiles/freelistchecker.dir/build.make test/monitortest/monitorchecker/CMakeFiles/freelistchecker.dir/build
.PHONY : freelistchecker/fast

#=============================================================================
# Target rules for targets named test_monitorrelease

# Build rule for target.
test_monitorrelease: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_monitorrelease
.PHONY : test_monitorrelease

# fast build rule for target.
test_monitorrelease/fast:
	$(MAKE) -f test/monitortest/testrelease/CMakeFiles/test_monitorrelease.dir/build.make test/monitortest/testrelease/CMakeFiles/test_monitorrelease.dir/build
.PHONY : test_monitorrelease/fast

#=============================================================================
# Target rules for targets named test_rcvrelease

# Build rule for target.
test_rcvrelease: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_rcvrelease
.PHONY : test_rcvrelease

# fast build rule for target.
test_rcvrelease/fast:
	$(MAKE) -f test/monitortest/testrelease/CMakeFiles/test_rcvrelease.dir/build.make test/monitortest/testrelease/CMakeFiles/test_rcvrelease.dir/build
.PHONY : test_rcvrelease/fast

#=============================================================================
# Target rules for targets named test_sndrelease

# Build rule for target.
test_sndrelease: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_sndrelease
.PHONY : test_sndrelease

# fast build rule for target.
test_sndrelease/fast:
	$(MAKE) -f test/monitortest/testrelease/CMakeFiles/test_sndrelease.dir/build.make test/monitortest/testrelease/CMakeFiles/test_sndrelease.dir/build
.PHONY : test_sndrelease/fast

#=============================================================================
# Target rules for targets named printCells

# Build rule for target.
printCells: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 printCells
.PHONY : printCells

# fast build rule for target.
printCells/fast:
	$(MAKE) -f debug/CMakeFiles/printCells.dir/build.make debug/CMakeFiles/printCells.dir/build
.PHONY : printCells/fast

CrashPoints.o: CrashPoints.cpp.o
.PHONY : CrashPoints.o

# target to build an object file
CrashPoints.cpp.o:
	$(MAKE) -f CMakeFiles/test_4.dir/build.make CMakeFiles/test_4.dir/CrashPoints.cpp.o
.PHONY : CrashPoints.cpp.o

CrashPoints.i: CrashPoints.cpp.i
.PHONY : CrashPoints.i

# target to preprocess a source file
CrashPoints.cpp.i:
	$(MAKE) -f CMakeFiles/test_4.dir/build.make CMakeFiles/test_4.dir/CrashPoints.cpp.i
.PHONY : CrashPoints.cpp.i

CrashPoints.s: CrashPoints.cpp.s
.PHONY : CrashPoints.s

# target to generate assembly for a file
CrashPoints.cpp.s:
	$(MAKE) -f CMakeFiles/test_4.dir/build.make CMakeFiles/test_4.dir/CrashPoints.cpp.s
.PHONY : CrashPoints.cpp.s

GlobalConfig.o: GlobalConfig.cpp.o
.PHONY : GlobalConfig.o

# target to build an object file
GlobalConfig.cpp.o:
	$(MAKE) -f CMakeFiles/test_4.dir/build.make CMakeFiles/test_4.dir/GlobalConfig.cpp.o
.PHONY : GlobalConfig.cpp.o

GlobalConfig.i: GlobalConfig.cpp.i
.PHONY : GlobalConfig.i

# target to preprocess a source file
GlobalConfig.cpp.i:
	$(MAKE) -f CMakeFiles/test_4.dir/build.make CMakeFiles/test_4.dir/GlobalConfig.cpp.i
.PHONY : GlobalConfig.cpp.i

GlobalConfig.s: GlobalConfig.cpp.s
.PHONY : GlobalConfig.s

# target to generate assembly for a file
GlobalConfig.cpp.s:
	$(MAKE) -f CMakeFiles/test_4.dir/build.make CMakeFiles/test_4.dir/GlobalConfig.cpp.s
.PHONY : GlobalConfig.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... test_4"
	@echo "... comm"
	@echo "... freelist"
	@echo "... monitor"
	@echo "... proxy"
	@echo "... shm"
	@echo "... utils"
	@echo "... testcommon"
	@echo "... readCounter"
	@echo "... test_monitor"
	@echo "... test_rcv"
	@echo "... test_snd"
	@echo "... test_monitorcnt"
	@echo "... test_rcvcnt"
	@echo "... test_sndcnt"
	@echo "... test_monitorcnt12n"
	@echo "... test_rcvcnt12n"
	@echo "... test_sndcnt12n"
	@echo "... test_monitorcntnn"
	@echo "... test_rcvcntnn"
	@echo "... test_sndcntnn"
	@echo "... freelistchecker"
	@echo "... test_monitorrelease"
	@echo "... test_rcvrelease"
	@echo "... test_sndrelease"
	@echo "... printCells"
	@echo "... CrashPoints.o"
	@echo "... CrashPoints.i"
	@echo "... CrashPoints.s"
	@echo "... GlobalConfig.o"
	@echo "... GlobalConfig.i"
	@echo "... GlobalConfig.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

