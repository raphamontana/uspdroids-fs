QT += core \
    network
SOURCES += main.cpp
HEADERS += viewermanager.h \
    strategymanager.h \
    simulator.h \
    gamemanager.h \
    worldmodel.h \
    strategyconnection.h
LIBS += 
QMAKE_CXXFLAGS += -Wall \
    -Wextra
