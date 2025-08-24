set(TARGET_NAME ${PROJECT_NAME})

################################################################################

include_directories(.)

################################################################################

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
)

################################################################################

add_executable(${TARGET_NAME} ${SOURCES})

set(LIBS
    ${LIBXML2_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${OPENSCENEGRAPH_LIBRARIES}
)

target_link_libraries(${TARGET_NAME}
    $<TARGET_OBJECTS:mc-mass-cgi>
    $<TARGET_OBJECTS:mc-mass-gui>
    $<TARGET_OBJECTS:mc-mass-utils>
    ${LIBS}
)

qt5_use_modules(${TARGET_NAME} Core Widgets OpenGL)
