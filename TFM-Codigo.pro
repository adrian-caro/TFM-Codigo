TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Node.cpp \
    Room.cpp \
    Tunnel.cpp

HEADERS += \
    Node.h \
    Room.h \
    Tunnel.h

DISTFILES += \
    data.txt
