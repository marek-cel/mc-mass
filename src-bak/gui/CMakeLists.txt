set(MODULE_NAME gui)

################################################################################

set(CPP_FILES
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
    DialogEdit.cpp
    DockWidgetComponents.cpp
    DockWidgetParams.cpp
    DockWidgetResults.cpp
    GraphicsWindowQt.cpp
    KeyMap.cpp
    MainWindow.cpp
    RecentFileAction.cpp
    WidgetCGI.cpp
    WidgetOSG.cpp
)

set(MOC_SRC_FILES
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
    DialogEdit.h
    DockWidgetComponents.h
    DockWidgetParams.h
    DockWidgetResults.h
    MainWindow.h
    RecentFileAction.h
    WidgetCGI.h
    WidgetOSG.h
)

set(UIC_SRC_FILES
    DialogEdit.ui
    DockWidgetComponents.ui
    DockWidgetParams.ui
    DockWidgetResults.ui
    MainWindow.ui
)

################################################################################

add_library(${MODULE_NAME} STATIC ${CPP_FILES} ${MOC_SRC_FILES} ${UIC_SRC_FILES})

################################################################################

qt5_use_modules(${MODULE_NAME} Widgets OpenGL Xml)
