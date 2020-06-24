#-------------------------------------------------
#
# Project created by QtCreator 2020-05-30T17:42:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = towerDefense
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    bigtower.cpp \
    defendtower.cpp \
    firetower.cpp \
    greentower.cpp \
    lighttower.cpp \
        main.cpp \
    selectbox.cpp \
    tower.cpp \
        widget.cpp \
    game.cpp \
    monster.cpp

HEADERS += \
    bigtower.h \
    defendtower.h \
    firetower.h \
    greentower.h \
    lighttower.h \
    selectbox.h \
    tower.h \
        widget.h \
    game.h \
    monster.h \
    global.h

FORMS += \
        widget.ui

RESOURCES += \
    image.qrc


