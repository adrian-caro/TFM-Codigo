TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Node.cpp \
    Tunnel.cpp \
    Graph.cpp \
    Segment.cpp \
    OOI.cpp \
    Dijkstra.cpp \
    Exploration.cpp

HEADERS += \
    Node.h \
    Tunnel.h \
    Graph.h \
    Segment.h \
    OOI.h \
    Dijkstra.h \
    Exploration.h

DISTFILES += \
    data.txt
