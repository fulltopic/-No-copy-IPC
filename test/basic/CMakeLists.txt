
ADD_EXECUTABLE(test_monitor 
				TestMonitor.cpp
)
TARGET_LINK_LIBRARIES(test_monitor 
						${exelibs}
)

ADD_EXECUTABLE(test_rcv 
				TestRcver.cpp
)
TARGET_LINK_LIBRARIES(test_rcv 
						${exelibs}
)

ADD_EXECUTABLE(test_snd TestSnder.cpp
							TestSnder.cpp
)
TARGET_LINK_LIBRARIES(test_snd 
						${exelibs}
)