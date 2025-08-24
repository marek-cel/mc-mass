set(TARGET_NAME mc-mass-tests)

################################################################################

find_package(GTest REQUIRED)

################################################################################

include_directories(. ../src)

################################################################################

add_subdirectory(utils)

################################################################################

set(SOURCES
    main.cpp
    CsvFileReader.cpp
)

################################################################################

add_executable(${TARGET_NAME} ${SOURCES})

set(LIBS
    GTest::gtest
    GTest::gtest_main
    ${LIBXML2_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${OPENSCENEGRAPH_LIBRARIES}
)

if (UNIX)
    set(LIBS ${LIBS} gcov ${GTK3_LIBRARIES})
endif()

target_link_libraries(${TARGET_NAME}
    $<TARGET_OBJECTS:mc-mass-utils>
    $<TARGET_OBJECTS:mc-mass-tests-utils>
    ${LIBS}
)

set_target_properties(${TARGET_NAME} PROPERTIES EXCLUDE_FROM_ALL True)

################################################################################

gtest_discover_tests(${TARGET_NAME}
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
