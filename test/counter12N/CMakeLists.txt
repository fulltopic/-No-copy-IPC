
ADD_EXECUTABLE(test_monitorcnt12n 
				TestMonitorCnt.cpp
)
TARGET_LINK_LIBRARIES(test_monitorcnt12n 
						${exelibs}
)

ADD_EXECUTABLE(test_rcvcnt12n 
				TestRcvCnt.cpp
)
TARGET_LINK_LIBRARIES(test_rcvcnt12n 
						${exelibs}
)

ADD_EXECUTABLE(test_sndcnt12n
	TestSndCnt.cpp
)
TARGET_LINK_LIBRARIES(test_sndcnt12n 
						${exelibs}
)