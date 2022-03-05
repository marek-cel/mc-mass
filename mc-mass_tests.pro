QT -= gui
QT += xml

TEMPLATE = app

################################################################################

DESTDIR = $$PWD/bin
TARGET = tests

################################################################################

CONFIG += c++17

################################################################################

QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage

################################################################################

DEFINES += QT_DEPRECATED_WARNINGS

win32: DEFINES += \
    NOMINMAX \
    WIN32 \
    _WINDOWS \
    _CRT_SECURE_NO_DEPRECATE \
    _SCL_SECURE_NO_WARNINGS \
    _USE_MATH_DEFINES

win32: CONFIG(release, debug|release): DEFINES += NDEBUG
win32: CONFIG(debug, debug|release):   DEFINES += _DEBUG

unix:  DEFINES += _LINUX_
win32: DEFINES += WIN32

################################################################################

INCLUDEPATH += ./src ./tests

################################################################################

win32: LIBS += \

unix: LIBS += \
    -L/lib \
    -L/usr/lib \
    -L/usr/local/lib

################################################################################

LIBS += \
    -lgcov --coverage \
    -lgtest \
    -lgtest_main \
    -pthread

################################################################################

include($$PWD/src/components/components.pri)
include($$PWD/src/utils/utils.pri)
include($$PWD/mc-mass_tests.pri)
