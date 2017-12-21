GLAZED_CAKE_BASE = ../..

TEMPLATE = app
TARGET = WriteToFile

SOURCES += \
    WriteToFile.cpp

INCLUDEPATH += \
    $$GLAZED_CAKE_BASE/include

QT += core

OBJECTS_DIR = $$GLAZED_CAKE_BASE/lib
MOC_DIR = $$GLAZED_CAKE_BASE/lib
DESTDIR = $$GLAZED_CAKE_BASE/build

DEPENDENCY_LIBRARIES = GlazedCake

include($$GLAZED_CAKE_BASE/dependencies.pri)