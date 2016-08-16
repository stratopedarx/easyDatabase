QT += core
QT -= gui

CONFIG += c++11

TARGET = DataBase
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    cmdclient.cpp \
    request.cpp \
    server.cpp

HEADERS += \
    cmdclient.h \
    request.h \
    answer.h \
    server.h
