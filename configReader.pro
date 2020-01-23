TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    cjsonreader.cpp \
    cjson.c

HEADERS += \
    configreader.h \
    cjsonreader.h \
    cjson.h
