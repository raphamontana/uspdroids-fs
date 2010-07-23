# -------------------------------------------------
# Project created by USPDroids
# -------------------------------------------------
QT += core
QT += network
QT += gui
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
    strategiesmanager.cpp \
    launcher.cpp \
    front-end/janelaprincipal.cpp
HEADERS += simulator.h \
    gamemanager.h \
    worldmodel.h \
    strategyconnection.h \
    viewersmanager.h \
    strategiesmanager.h \
    launcher.h \
    physics/team.h \
    physics/robot.h \
    physics/field.h \
    physics/ball.h \
    front-end/janelaprincipal.h
LIBS += -lode_double
QMAKE_CXXFLAGS += -Wall \
    -Wextra
RESOURCES += icons.qrc
FORMS += front-end/janelaprincipal.ui
