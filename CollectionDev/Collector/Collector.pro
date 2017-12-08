TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

wind32:{
SOURCES += main.c \
           sqlite3.c \

HEADERS += sqlite3.h

INCLUDEPATH += "C:/Program Files/Phidgets/Phidget22"
LIBS += -L "C:/Program Files/Phidgets/Phidget22/x86" -lphidget22
}

# macOS
unix:{
SOURCES += main.c \

LIBS += -l sqlite3

INCLUDEPATH += "/Library/Frameworks/Phidget22.framework/Headers"
QMAKE_LFLAGS += -F-F /Library/Frameworks
LIBS += -framework Phidget22
}
