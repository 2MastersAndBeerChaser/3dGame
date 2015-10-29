#-------------------------------------------------
#
# Project created by QtCreator 2015-10-23T09:22:49
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KPACUBO
TEMPLATE = app


SOURCES += main.cpp\
    cavegenerator.cpp \
    roomgenerator.cpp

HEADERS  += \
    cavegenerator.h \
    roomgenerator.h

FORMS    += mainwindow.ui
