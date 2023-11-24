QT += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

################################################################################

DESTDIR = $$PWD/../bin
TARGET = mc-mass

################################################################################

CONFIG += c++17

################################################################################

win32: RC_FILE = src/mc-mass.rc

################################################################################

win32: CONFIG(release, debug|release): QMAKE_CXXFLAGS += -O2
unix:  CONFIG(release, debug|release): QMAKE_CXXFLAGS += -O2

#win32: QMAKE_CXXFLAGS += /Zc:wchar_t

win32: QMAKE_LFLAGS += /INCREMENTAL:NO

################################################################################

DEFINES += QT_DEPRECATED_WARNINGS

DEFINES +=

greaterThan(QT_MAJOR_VERSION, 4):win32: DEFINES += USE_QT5

win32: DEFINES += \
    NOMINMAX \
    WIN32 \
    _WINDOWS \
    _CRT_SECURE_NO_DEPRECATE \
    _SCL_SECURE_NO_WARNINGS \
    _USE_MATH_DEFINES

win32: CONFIG(release, debug|release): DEFINES += NDEBUG
win32: CONFIG(debug, debug|release):   DEFINES += _DEBUG

#CONFIG(release, debug|release): DEFINES += QT_NO_DEBUG_OUTPUT
#DEFINES += QT_NO_DEBUG_OUTPUT

unix: DEFINES += _LINUX_

################################################################################

INCLUDEPATH += ./src

unix: INCLUDEPATH += \
    /usr/local/include \
    /usr/local/include/mcutils

################################################################################

LIBS += \
    -lmcutils

win32: CONFIG(release, debug|release): LIBS += \

win32: CONFIG(debug, debug|release): LIBS += \

unix: LIBS += \
    -L/lib \
    -L/usr/lib \
    -L/usr/local/lib

################################################################################

HEADERS += \
    $$PWD/defs.h \
    $$PWD/Aircraft.h \
    $$PWD/AircraftData.h \
    $$PWD/DataFile.h

SOURCES += \
    $$PWD/main.cpp \
    $$PWD/Aircraft.cpp \
    $$PWD/DataFile.cpp

RESOURCES += \
    $$PWD/mc-mass.qrc

################################################################################

include($$PWD/components/components.pri)
include($$PWD/gui/gui.pri)
include($$PWD/utils/utils.pri)
