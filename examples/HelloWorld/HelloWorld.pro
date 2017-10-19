GLAZED_CAKE_BASE = ../../

TARGET = HelloWorld
TEMPLATE = app

SOURCES += \
    HelloWorld.cpp

INCLUDEPATH += \
    $$GLAZED_CAKE_BASE/include

LIBS += \
	-lglazedcake

QT += core

OBJECTS_DIR = $$GLAZED_CAKE_BASE/build
MOC_DIR = $$GLAZED_CAKE_BASE/build
DESTDIR = $$GLAZED_CAKE_BASE/lib