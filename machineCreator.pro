#-------------------------------------------------
#
# Project created by QtCreator 2016-09-14T13:00:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = machineCreator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    util/AutoEnumerate.cpp \
    util/Utils.cpp

HEADERS  += mainwindow.h \
    util/Patch.h \
    util/AutoEnumerate.h \
    util/Utils.h \
    graph/Edge.h \
    graph/Flow.h \
    graph/FlowPtrComparator.h \
    graph/Graph.h \
    graph/Node.h

FORMS    += mainwindow.ui

INCLUDEPATH += X:/boost_1_61_0
INCLUDEPATH += X:/machineCreator/lib

DISTFILES += \
    configuration/log.ini

