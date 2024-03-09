add_subdirectory(cgi)
add_subdirectory(gui)
add_subdirectory(mass)
add_subdirectory(utils)

################################################################################

set(CPP_FILES
    main.cpp
    Aircraft.cpp
    AircraftFile.cpp
)

#set(MOC_SRC_FILES)

set(RCC_SRC_FILES
    mc-mass.qrc
)

set(SOURCES ${CPP_FILES} ${MOC_SRC_FILES} ${RCC_SRC_FILES})

################################################################################

if(WIN32)
    ENABLE_LANGUAGE(RC)
    set(SOURCES mc-mass.rc ${SOURCES})
endif()

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

set(LIBS
    ${OPENSCENEGRAPH_LIBRARIES}
    ${QT_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME} 
    -Wl,--start-group
    cgi
    gui
    mass
    utils
    ${LIBS}
    -Wl,--end-group
)

