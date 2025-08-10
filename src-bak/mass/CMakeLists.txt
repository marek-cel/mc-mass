set(MODULE_NAME mass)

################################################################################

set(CPP_FILES
    AllElse.cpp
    Component.cpp
    Engine.cpp
    Fuselage.cpp
    GearMain.cpp
    GearNose.cpp
    RotorDrive.cpp
    RotorHub.cpp
    RotorMain.cpp
    RotorTail.cpp
    TailHor.cpp
    TailVer.cpp
    Wing.cpp
)

################################################################################

add_library(${MODULE_NAME} STATIC ${CPP_FILES})

qt5_use_modules(${MODULE_NAME} Core Xml)