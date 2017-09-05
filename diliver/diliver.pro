#-------------------------------------------------
#
# Project created by QtCreator 2017-06-16T15:48:19
#
#-------------------------------------------------

QT       += core gui
QT       += sql
RC_FILE   =   ico.rc
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = diliver
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sqlopen.cpp \
    dialog.cpp \
    about.cpp

HEADERS  += mainwindow.h \
    sqlopen.h \
    dialog.h \
    about.h

FORMS    += mainwindow.ui \
    dialog.ui \
    about.ui

RESOURCES += \
    rec.qrc
