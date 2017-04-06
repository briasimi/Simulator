QT += core
QT -= gui

CONFIG += c++11

TARGET = LEC_Server
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    isocket.cpp \
    utilitis.cpp \
    mainserver.cpp

HEADERS += \
    isocket.h \
    utilitis.h \
    errors.h \
    mainserver.h
