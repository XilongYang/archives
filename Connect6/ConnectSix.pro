#-------------------------------------------------
#
# Project created by QtCreator 2016-12-22T10:50:43
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ConnectSix
TEMPLATE = app


SOURCES += main.cpp\
    ai.cpp \
    gamemodel.cpp \
    gamewidget.cpp \
        mainwindow.cpp

HEADERS  += mainwindow.h \
    ai.h \
    gamemodel.h \
    gamewidget.h

RESOURCES += \
    resource.qrc
