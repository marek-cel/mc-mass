set(TARGET_NAME tests)

################################################################################

find_package(GTest REQUIRED)
#find_package(Threads REQUIRED)

################################################################################

include_directories(.)

################################################################################

set(SOURCES
    main.cpp
)

################################################################################

add_executable(${TARGET_NAME} ${SOURCES})

set(LIBS
    GTest::gtest
    GTest::gtest_main
)

target_link_libraries(${TARGET_NAME} ${LIBS})

################################################################################

gtest_discover_tests(${TARGET_NAME}
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
