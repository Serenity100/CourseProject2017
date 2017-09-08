TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    avltree.cpp \
    treenode.cpp \
    fileparser.cpp

HEADERS += \
    avltree.h \
    treenode.h \
    fileparser.h
