TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../DMS/dms.cpp \
    ../DMS/table.cpp

LIBS += -l sqlite3

HEADERS += \
    ../DMS/dms.h \
    ../DMS/table.h
