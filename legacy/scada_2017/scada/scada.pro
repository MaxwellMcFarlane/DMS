TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../DMS/dms.cpp \
    ../DMS/table.cpp \
    ControlSubSystem/branch.cpp \
    ControlSubSystem/state.cpp \
    ../tools/baseclass.cpp \
    ../tools/log.cpp \
    ControlSubSystem/modemanager.cpp \
    scada.cpp \
    ../DMS/dmswd.cpp \
    ControlSubSystem/calibration.cpp

LIBS += -l sqlite3

HEADERS += \
    ../DMS/dms.h \
    ../DMS/table.h \
    ControlSubSystem/branch.h \
    ControlSubSystem/state.h \
    ../tools/baseclass.h \
    ../tools/log.h \
    ../tools/macros.h \
    ControlSubSystem/modemanager.h \
    scada.h \
    ../DMS/dmswd.h \
    ControlSubSystem/calibration.h
