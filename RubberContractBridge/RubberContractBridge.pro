# The required libraries are added such as core and gui.
QT       += core gui qml
QT += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += no_testcase_installs

#All sources classes of the project is addded below.
SOURCES += \
    logger/logger.cpp \
    main.cpp \
    unit-tests/logger/testlogger.cpp

#All header files of the project is addded below.
HEADERS += \
     \
    logger/logger.h \
    unit-tests/logger/testlogger.h

#All UI windows are shown below.
FORMS += \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
