TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    oneSensorMain.c \
    main_copy.c \


#INCLUDEPATH += "C:/Program Files/Phidgets/Phidget22"
INCLUDEPATH += "/Library/Frameworks/Phidget22.framework/Versions/A/Headers"
#LIBS += -F "C:/Program Files/Phidgets/Phidget22/x86" -lphidget22

LIBS += -l sqlite3

