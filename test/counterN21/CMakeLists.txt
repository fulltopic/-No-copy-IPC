
ADD_EXECUTABLE(test_monitorcnt 
				TestMonitorCnt.cpp
)
TARGET_LINK_LIBRARIES(test_monitorcnt 
						${exelibs}
)

ADD_EXECUTABLE(test_rcvcnt 
				TestRcvCnt.cpp
)
TARGET_LINK_LIBRARIES(test_rcvcnt 
						${exelibs}
)

ADD_EXECUTABLE(test_sndcnt 
	TestSndCnt.cpp
)
TARGET_LINK_LIBRARIES(test_sndcnt 
						${exelibs}
)