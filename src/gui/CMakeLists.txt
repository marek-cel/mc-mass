set(MODULE_NAME mc-mass-gui)

################################################################################

set(MOC_FILES
    ComboUnits.h
    ComboUnitsAltitude.h
    ComboUnitsAngle.h
    ComboUnitsArea.h
    ComboUnitsInertia.h
    ComboUnitsLength.h
    ComboUnitsMass.h
    ComboUnitsPower.h
    ComboUnitsSpeed.h
    ComboUnitsVelocity.h
    ComboUnitsVolume.h
    MainWindow.h
    RecentFileAction.h
    WidgetCGI.h
    WidgetOSG.h
)

set(UIC_FILES
    MainWindow.ui
)

set(SOURCES
    ${MOC_FILES}
    ${UIC_FILES}
    ComboUnits.cpp
    ComboUnitsAltitude.cpp
    ComboUnitsAngle.cpp
    ComboUnitsArea.cpp
    ComboUnitsInertia.cpp
    ComboUnitsLength.cpp
    ComboUnitsMass.cpp
    ComboUnitsPower.cpp
    ComboUnitsSpeed.cpp
    ComboUnitsVelocity.cpp
    ComboUnitsVolume.cpp
    GraphicsWindowQt.cpp
    KeyMap.cpp
    MainWindow.cpp
    RecentFileAction.cpp
    WidgetCGI.cpp
    WidgetOSG.cpp
)

################################################################################

add_library(${MODULE_NAME} OBJECT ${SOURCES})

qt5_use_modules(${MODULE_NAME} Core Widgets OpenGL)
