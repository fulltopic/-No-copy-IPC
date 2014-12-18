set (TEST_HOME ${PROJ_HOME}/test)
set (TEST_IDIR ${TEST_HOME})

set (TEST_BASIC_DIR ${TEST_HOME}/basic)
set (TEST_COMMON_DIR ${TEST_HOME}/common)
set (TEST_COUNTERCOMM_DIR ${TEST_HOME}/countercommon)
set (TEST_COUNTERN21_DIR ${TEST_HOME}/counterN21)

set (TEST_BASIC_IDIR ${TEST_HOME}/basic)
set (TEST_COMMON_IDIR ${TEST_HOME}/common)
set (TEST_COUNTERCOMM_IDIR ${TEST_HOME}/countercommon)
set (TEST_COUNTERN21_IDIR ${TEST_HOME}/counterN21)

include_directories(AFTER
					${TEST_IDIR}
					${TEST_BASIC_IDIR}
					${TEST_COMMON_IDIR}
					${TEST_COUNTERCOMM_IDIR}
					${TEST_COUNTERN21_IDIR}
)

set(sharedlibs  rt test_4)
set(exelibs ${sharedlibs} testcommon)

add_subdirectory(common)
add_subdirectory(countercommon)


add_subdirectory(basic)
add_subdirectory(counterN21)
add_subdirectory(counter12N)
add_subdirectory(counterN2N)