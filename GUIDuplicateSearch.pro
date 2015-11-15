#-------------------------------------------------
#
# Project created by QtCreator 2015-10-21T18:58:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUIDuplicateSearch
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -pedantic
CONFIG += -std=c++11

SOURCES += main.cpp \
    dupsearchmainwindow.cpp \
    leftwidget.cpp \
    filesystemtraverserthread.cpp \
    filesinfoholder.cpp \
    fileinfo.cpp \
    samesizewidget.cpp \
    samesizeholderbuild_thread.cpp \
    samesizeholder.cpp

HEADERS  += \
    dupsearchmainwindow.h \
    leftwidget.h \
    filesystemtraverserthread.h \
    filesinfoholder.h \
    fileinfo.h \
    samesizewidget.h \
    samesizeholderbuild_thread.h \
    samesizeholder.h
