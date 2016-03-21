include_directories(${GTEST_INCLUDE})

add_executable(RaspiHelloWorld_basic_tests
        basic_check.cpp
        )

target_link_libraries(RaspiHelloWorld_basic_tests
        ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY}
        )
