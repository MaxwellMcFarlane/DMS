TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    dms.cpp \
    table.cpp
LIBS += -l sqlite3

HEADERS += \
    dms.h \
    table.h
