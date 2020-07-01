TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Node.cpp \
    Room.cpp \
    Tunnel.cpp \
    Graph.cpp \
    Segment.cpp \
    OOI.cpp \
    Dijkstra.cpp

HEADERS += \
    Node.h \
    Room.h \
    Tunnel.h \
    Graph.h \
    Segment.h \
    OOI.h \
    Dijkstra.h

DISTFILES += \
    data.txt \
    exploration.txt
