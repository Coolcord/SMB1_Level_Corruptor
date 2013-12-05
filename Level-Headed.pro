#-------------------------------------------------
#
# Project created by QtCreator 2013-11-25T19:36:26
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Level-Headed
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    binarymanipulator.cpp \
    smb1levelgenerator.cpp

HEADERS  += mainwindow.h \
    binarymanipulator.h \
    smb1levelgenerator.h

FORMS    += mainwindow.ui
