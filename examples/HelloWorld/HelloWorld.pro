GLAZED_CAKE_BASE = ../..

TEMPLATE = app
TARGET = HelloWorld

SOURCES += \
    HelloWorld.cpp

INCLUDEPATH += \
    $$GLAZED_CAKE_BASE/include

QT += core

DEPENDENCY_LIBRARIES = GlazedCake

include($$GLAZED_CAKE_BASE/config.pri)