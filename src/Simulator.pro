# -------------------------------------------------
# Project created by USPDroids
# -------------------------------------------------
QT += core
QT += network
QT += gui
TARGET = Simulator
TEMPLATE = app
RESOURCES += icons.qrc
SOURCES += main.cpp \
    simulator.cpp \
    worldmodel.cpp \
    gamemanager.cpp \
    viewersmanager.cpp \
    strategiesmanager.cpp \
    physics/team.cpp \
    physics/robot.cpp \
    physics/field.cpp \
    physics/ball.cpp \
    gui/frontend.cpp \
    physics/engine.cpp \
    connection/radio.cpp \
    connection/vision.cpp \
    connection/strategyconnection.cpp
HEADERS += simulator.h \
    gamemanager.h \
    strategiesmanager.h \
    viewersmanager.h \
    worldmodel.h \
    physics/team.h \
    physics/robot.h \
    physics/field.h \
    physics/ball.h \
    gui/frontend.h \
    physics/engine.h \
    connection/radio.h \
    connection/vision.h \
    connection/strategyconnection.h
QMAKE_CXXFLAGS += -Wall \
    -Wextra
win32:LIBS += -lode_double
unix:LIBS += -lode
