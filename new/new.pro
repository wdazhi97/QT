#-------------------------------------------------
#
# Project created by QtCreator 2017-03-30T09:09:32
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
QT       +=serialport
RC_FILE   =   ico.rc
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = new
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gamemodel.cpp

HEADERS  += mainwindow.h \
    gamemodel.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc
