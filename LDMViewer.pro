QT       += core gui serialport network serialbus printsupport

VERSION = 1.0
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

EXTRA_QMAKE_TARGET_PRODUCT =  LDM Viewer
QMAKE_TARGET_DESCRIPTION = Клиент для измерителей диаметров LDM
QMAKE_TARGET_COPYRIGHT = NurRuslan

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    centerviewer.cpp \
    connectionpanel.cpp \
    console.cpp \
    diameterlooker.cpp \
    ldmdevice.cpp \
    looker.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    statusbar.cpp

HEADERS += \
    centerviewer.h \
    connectionpanel.h \
    console.h \
    diameterlooker.h \
    ldmdevice.h \
    looker.h \
    mainwindow.h \
    qcustomplot.h \
    statusbar.h

FORMS += \
    connectionpanel.ui \
    diameterlooker.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
RC_ICONS += icon.ico


