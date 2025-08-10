set(MODULE_NAME mc-mass-cgi)

################################################################################

set(CPP_FILES
    Builder.cpp
    CGI.cpp
    Component.cpp
    Geometry.cpp
    Grid.cpp
    Highlight.cpp
    HUD.cpp
    Manager.cpp
    ManipulatorOrbit.cpp
    ManipulatorTrack.cpp
    Model.cpp
    ViewGizmo.cpp
)

################################################################################

add_library(${MODULE_NAME} STATIC ${CPP_FILES})
