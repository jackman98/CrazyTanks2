TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    tank.cpp \
    bullet.cpp \
    cell.cpp \
    input.cpp \
    render.cpp \
    world.cpp \
    bulletaction.cpp \
    logic.cpp \
    ai.cpp \
    timer.cpp \
    gameprocesspart.cpp

HEADERS += \
    tank.h \
    bullet.h \
    cell.h \
    gamemanager.h \
    input.h \
    render.h \
    world.h \
    bulletaction.h \
    logic.h \
    ai.h \
    constants.h \
    timer.h \
    gameprocesspart.h
