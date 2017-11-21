#-------------------------------------------------
#
# Project created by QtCreator 2017-03-17T08:45:32
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += xml

TARGET = agv
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    xsserial.cpp \
    getnavigation.cpp \
    controlcenter.cpp \
    pidcalculate.cpp \
    ccontrolbyte.cpp \
    owntimer.cpp \
    pathrfid.cpp \
    condition.cpp \
    work.cpp \
    gpio.cpp \
    control.cpp \
    madacontrol.cpp \
    readpath.cpp \
    speedpulse.cpp \
    ludp.cpp \
    netcommand.cpp \
    drivestauts.cpp

HEADERS  += mainwindow.h \
    xsserial.h \
    getnavigation.h \
    controlcenter.h \
    pidcalculate.h \
    ccontrolbyte.h \
    owntimer.h \
    pathrfid.h \
    condition.h \
    work.h \
    gpio.h \
    control.h \
    madacontrol.h \
    readpath.h \
    speedpulse.h \
    ludp.h \
    netcommand.h \
    drivestauts.h

FORMS    += mainwindow.ui
