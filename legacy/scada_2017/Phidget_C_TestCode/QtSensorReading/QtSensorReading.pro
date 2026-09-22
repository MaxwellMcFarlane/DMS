TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c

INCLUDEPATH += "C:/Program Files/Phidgets/Phidget22"
LIBS += -L "C:/Program Files/Phidgets/Phidget22/x86" -lphidget22
