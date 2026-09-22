#-------------------------------------------------
#
# Project created by QtCreator 2017-11-29T17:52:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = scadagui
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp\
    ../src/dms.cpp \
    ../src/table.cpp \
    ../libs/log.cpp \
    exportwindow.cpp \
    tableeditwindow.cpp \
    ../src/control/branch.cpp \
    ../src/control/modemanager.cpp \
    ../src/control/state.cpp \
    configurationeditwindow.cpp \
    ../src/sqlite3.c

#LIBS += -l sqlite3

HEADERS += \
        mainwindow.h\
    ../src/dms.h \
    ../src/table.h \
    ../libs/log.h \
    exportwindow.h \
    tableeditwindow.h \
    ../src/control/branch.h \
    ../src/control/modemanager.h \
    ../src/control/state.h \
    configurationeditwindow.h \
    ../src/sqlite3.h

FORMS += \
        mainwindow.ui \
    exportwindow.ui \
    tableeditwindow.ui \
    configurationeditwindow.ui \
    calibrationwindow.ui
