# -------------------------------------------------
# Project created by USPDroids
# -------------------------------------------------
QT += core
QT += network
QT += gui
TARGET = Simulator
TEMPLATE = app
SOURCES += main.cpp \
    simulator.cpp \
    worldmodel.cpp \
    gamemanager.cpp \
    strategyconnection.cpp \
    viewersmanager.cpp \
    strategiesmanager.cpp \
    launcher.cpp \
    physics/team.cpp \
    physics/robot.cpp \
    physics/field.cpp \
    physics/ball.cpp \
    gui/frontend.cpp
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
    gui/frontend.h
LIBS += -lode
QMAKE_CXXFLAGS += -Wall \
    -Wextra
RESOURCES += icons.qrc
