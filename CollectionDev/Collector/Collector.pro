TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \

LIBS += -l sqlite3

INCLUDEPATH += "/Library/Frameworks/Phidget22.framework/Headers"
QMAKE_LFLAGS += -F "/Library/Frameworks"
LIBS += -framework Phidget22
