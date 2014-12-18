
ADD_EXECUTABLE(test_monitorcntnn 
				TestMonitorCnt.cpp
)
TARGET_LINK_LIBRARIES(test_monitorcntnn 
						${exelibs}
)

ADD_EXECUTABLE(test_rcvcntnn 
				TestRcvCnt.cpp
)
TARGET_LINK_LIBRARIES(test_rcvcntnn 
						${exelibs}
)

ADD_EXECUTABLE(test_sndcntnn 
	TestSndCnt.cpp
)
TARGET_LINK_LIBRARIES(test_sndcntnn 
						${exelibs}
)