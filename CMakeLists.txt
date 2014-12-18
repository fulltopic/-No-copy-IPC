cmake_minimum_required(VERSION 2.6)

project(test_5)

set (HOME /home/zf/workspace_cpp/)
set (PROJ_HOME ${HOME}/test_5)
set (PROJ_IDIR ${HOME}/test_5)

set (comm.DIR ${PROJ_HOME}/comm)
set (comm.IDIR ${PROJ_HOME}/comm)
set (freelist.DIR ${PROJ_HOME}/freelist)
set (freelist.IDIR ${PROJ_HOME}/freelist)
set (monitor.DIR ${PROJ_HOME}/monitor)
set (monitor.IDIR ${PROJ_HOME}/monitor)
set (proxy.DIR ${PROJ_HOME}/proxy)
set (proxy.IDIR ${PROJ_HOME}/proxy)
set (shm.DIR ${PROJ_HOME}/shm)
set (shm.IDIR ${PROJ_HOME}/shm)
set (utils.DIR ${PROJ_HOME}/utils)
set (utils.IDIR ${PROJ_HOME}/utils)

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJ_HOME}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJ_HOME}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJ_HOME}/bin)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

set(CMAKE_CXX_FLAGS "-std=c++0x -ggdb -fsigned-char -freg-struct-return -fPIC -Wall -W -Wshadow -Wpointer-arith -Wcast-qual -Winline -DGNUPC")

set(CMAKE_SHARED_LINKER_FLAGS "-std=c++0x -ggdb -fsigned-char -freg-struct-return -fPIC -Wall -W -Wshadow -Wpointer-arith -Wcast-qual -Winline -Wreorder -D__LINUX_GPP__ -DGNUPC")

include_directories(BEFORE
					${PROJ_IDIR}
					${comm.IDIR}
					${freelist.IDIR}
					${monitor.IDIR}
					${proxy.IDIR}
					${shm.IDIR}
					${utils.IDIR}
)

			
add_subdirectory(comm)
add_subdirectory(freelist)
add_subdirectory(monitor)
add_subdirectory(proxy)
add_subdirectory(shm)
add_subdirectory(utils)

#link_directories(stubs fap_dpdk)				
add_library(test_4 SHARED GlobalConfig.cpp
							$<TARGET_OBJECTS:comm>
							$<TARGET_OBJECTS:freelist>
							$<TARGET_OBJECTS:monitor>
							$<TARGET_OBJECTS:proxy>
							$<TARGET_OBJECTS:shm>
							$<TARGET_OBJECTS:utils>
)

set (shared_libs rt pthread)
target_link_libraries(test_4 ${shared_libs})	


add_subdirectory(test)
add_subdirectory(debug)