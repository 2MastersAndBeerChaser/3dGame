#-------------------------------------------------
#
# Project created by QtCreator 2015-10-23T09:22:49
#
#-------------------------------------------------
LIBS += -lopengl32 -lSDL2 -lSDL_image
QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KPACUBO
TEMPLATE = app


SOURCES += main.cpp\
    Generators/cavegenerator.cpp \
    Generators/roomgenerator.cpp \
    gameapplication.cpp \
    UI/window3d.cpp \
    Nodes/cavewall.cpp \
    GL/basescene.cpp \
    GL/glhelper.cpp \
    GL/scenecamera.cpp \
    GL/scenenode.cpp \
    Generators/objectsgenerator.cpp \
    Nodes/playernode.cpp \
    Nodes/exitnode.cpp \
    Handlers/collisionhandler.cpp \
    Nodes/skybox.cpp

HEADERS  += \
    Generators/cavegenerator.h \
    Generators/roomgenerator.h \
    gameapplication.h \
    UI/window3d.h \
    Nodes/cavewall.h \
    GL/basescene.h \
    GL/glhelper.h \
    GL/scenecamera.h \
    GL/scenenode.h \
    Generators/generators.h \
    Generators/objectsgenerator.h \
    Nodes/playernode.h \
    globals.h \
    Nodes/exitnode.h \
    Handlers/collisionhandler.h \
    Nodes/skybox.h

FORMS    +=
