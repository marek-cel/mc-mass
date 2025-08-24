set(MODULE_NAME mc-mass-cgi)

################################################################################

set(SOURCES
    Builder.cpp
    CGI.cpp
    Component.cpp
    Grid.cpp
    Highlight.cpp
    HUD.cpp
    Manager.cpp
    ManipulatorOrtho.cpp
    Model.cpp
    ViewGizmo.cpp
)

################################################################################

add_library(${MODULE_NAME} OBJECT ${SOURCES})
