GLAZED_CAKE_BASE = ../..

TARGET = HelloWorld
TEMPLATE = app

SOURCES += \
    HelloWorld.cpp

INCLUDEPATH += \
    $$GLAZED_CAKE_BASE/include

QT += core

OBJECTS_DIR = $$GLAZED_CAKE_BASE/build
MOC_DIR = $$GLAZED_CAKE_BASE/build
DESTDIR = $$GLAZED_CAKE_BASE/lib

DEPENDENCY_LIBRARIES = GlazedCake

include($$GLAZED_CAKE_BASE/dependencies.pri)