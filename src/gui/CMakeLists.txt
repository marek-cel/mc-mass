set(MODULE_NAME mc-mass-gui)

################################################################################

set(MOC_FILES
    MainWindow.h
    RecentFileAction.h
)

set(UIC_FILES
    MainWindow.ui
)

set(SOURCES
    ${MOC_FILES}
    ${UIC_FILES}
    MainWindow.cpp
    RecentFileAction.cpp
)

################################################################################

add_library(${MODULE_NAME} OBJECT ${SOURCES})

qt5_use_modules(${MODULE_NAME} Core Widgets OpenGL)
