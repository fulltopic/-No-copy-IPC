

include_directories(AFTER
					${PROJ_HOME}
)


ADD_EXECUTABLE(freelistchecker 
				FreeListChecker.cpp
)
TARGET_LINK_LIBRARIES(freelistchecker 
						${exelibs}
)