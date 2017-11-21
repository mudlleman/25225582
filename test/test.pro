#-------------------------------------------------
#
# Project created by QtCreator 2017-03-27T13:37:01
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += xml
TARGET = test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ccontrolbyte.cpp \
    form.cpp \
    readpath.cpp \
    condition.cpp \
    control.cpp \
    work.cpp \
    udp.cpp \
    speedpulse.cpp \
    formudp.cpp

HEADERS  += mainwindow.h \
    ccontrolbyte.h \
    form.h \
    readpath.h \
    condition.h \
    control.h \
    work.h \
    udp.h \
    speedpulse.h \
    formudp.h

FORMS    += mainwindow.ui \
    form.ui \
    formudp.ui
