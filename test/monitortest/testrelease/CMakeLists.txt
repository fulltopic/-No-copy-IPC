
ADD_EXECUTABLE(test_monitorrelease 
				TestMonitorCnt.cpp
)
TARGET_LINK_LIBRARIES(test_monitorrelease 
						${exelibs}
)

ADD_EXECUTABLE(test_rcvrelease 
				TestRcvCnt.cpp
)
TARGET_LINK_LIBRARIES(test_rcvrelease 
						${exelibs}
)

ADD_EXECUTABLE(test_sndrelease 
	TestSndCnt.cpp
)
TARGET_LINK_LIBRARIES(test_sndrelease 
						${exelibs}
)