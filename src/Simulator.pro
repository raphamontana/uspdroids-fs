# -------------------------------------------------
# Project created by USPDroids
# -------------------------------------------------
QT += core
QT += network
QT -= gui
TARGET = Simulator
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    simulator.cpp \
    worldmodel.cpp \
    gamemanager.cpp \
    strategyconnection.cpp \
    viewersmanager.cpp \
    strategiesmanager.cpp
HEADERS += simulator.h \
    gamemanager.h \
    worldmodel.h \
    strategyconnection.h \
    viewersmanager.h \
    strategiesmanager.h
LIBS += 
QMAKE_CXXFLAGS += -Wall \
    -Wextra
