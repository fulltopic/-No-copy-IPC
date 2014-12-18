set (debug.IDIR ${PROJ_HOME}/debug)

include_directories(AFTER
					${debug.IDIR}
)

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

set(sharedlibs  rt test_4)


ADD_EXECUTABLE(printCells ShowCells.cpp
)
TARGET_LINK_LIBRARIES(printCells ${sharedlibs})

