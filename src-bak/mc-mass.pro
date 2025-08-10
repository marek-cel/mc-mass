QT += core gui opengl xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

################################################################################

DESTDIR = $$PWD/../bin
TARGET = mc-mass

################################################################################

CONFIG += c++17 object_parallel_to_source

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
    /usr/local/include

################################################################################

win32: LIBS += \
    -L$(OSG_ROOT)/lib \
    -lopengl32

win32: CONFIG(release, debug|release): LIBS += \
    -lOpenThreads \
    -losg \
    -losgDB \
    -losgGA \
    -losgText \
    -losgUtil \
    -losgViewer \
    -losgWidget

win32: CONFIG(debug, debug|release): LIBS += \
    -lOpenThreadsd \
    -losgd \
    -losgDBd \
    -losgGAd \
    -losgTextd \
    -losgUtild \
    -losgViewerd \
    -losgWidgetd

unix: LIBS += \
    -L/lib

unix: LIBS += \
    -lOpenThreads \
    -losg \
    -losgDB \
    -losgGA \
    -losgText \
    -losgUtil \
    -losgViewer \
    -losgWidget

################################################################################

HEADERS += \
    $$PWD/defs.h \
    $$PWD/Aircraft.h \
    $$PWD/AircraftData.h \
    $$PWD/AircraftFile.h

SOURCES += \
    $$PWD/main.cpp \
    $$PWD/Aircraft.cpp \
    $$PWD/AircraftFile.cpp

RESOURCES += \
    $$PWD/mc-mass.qrc

################################################################################

include($$PWD/cgi/cgi.pri)
include($$PWD/gui/gui.pri)
include($$PWD/mass/mass.pri)
include($$PWD/utils/utils.pri)
