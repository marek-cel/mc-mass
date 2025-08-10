add_subdirectory(cgi)
add_subdirectory(gui)
add_subdirectory(utils)

################################################################################

set(RCC_FILES
    mc-mass.qrc
)

set(SOURCES
    ${RCC_FILES}
    main.cpp
    Document.cpp
    Log.cpp
    Vehicle.cpp
)

################################################################################

if(WIN32)
    ENABLE_LANGUAGE(RC)
    set(SOURCES mc-mass.rc ${SOURCES})
endif()

################################################################################

add_executable(${PROJECT_NAME} ${SOURCES})

set(LIBS
    ${OPENSCENEGRAPH_LIBRARIES}
    ${LIBXML2_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME}
    $<TARGET_OBJECTS:mc-mass-cgi>
    $<TARGET_OBJECTS:mc-mass-gui>
    $<TARGET_OBJECTS:mc-mass-utils>
    ${LIBS}
)

qt5_use_modules(${PROJECT_NAME} Core Widgets OpenGL)