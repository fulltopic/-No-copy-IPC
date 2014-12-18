ADD_EXECUTABLE(readCounter ReadCounter.cpp
)
TARGET_LINK_LIBRARIES(readCounter 
						${sharedlibs}
						testcommon
)