GLAZED_CAKE_BASE = ../..

TARGET = WriteToFile

TEMPLATE = app

SOURCES += \
    WriteToFile.cpp

INCLUDEPATH += \
    $$GLAZED_CAKE_BASE/include

QT += core

DEPENDENCY_LIBRARIES = GlazedCake

include($$GLAZED_CAKE_BASE/config.pri)