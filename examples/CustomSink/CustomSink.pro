GLAZED_CAKE_BASE = ../..

TARGET = CustomSink

TEMPLATE = app

SOURCES += \
    CustomSink.cpp

INCLUDEPATH += \
    $$GLAZED_CAKE_BASE/include

QT += \
    core \
    widgets

DEPENDENCY_LIBRARIES = GlazedCake

include($$GLAZED_CAKE_BASE/config.pri)