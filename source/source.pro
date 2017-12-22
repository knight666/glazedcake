GLAZED_CAKE_BASE = ..

TARGET = GlazedCake

TEMPLATE = lib

CONFIG += staticlib

HEADERS += \
    $$GLAZED_CAKE_BASE/include/public/sinks/SinkDebugOutput.hpp \
    $$GLAZED_CAKE_BASE/include/public/sinks/SinkFile.hpp \
    $$GLAZED_CAKE_BASE/include/public/Base.hpp \
    $$GLAZED_CAKE_BASE/include/public/Channel.hpp \
    $$GLAZED_CAKE_BASE/include/public/Context.hpp \
    $$GLAZED_CAKE_BASE/include/public/Levels.hpp \
    $$GLAZED_CAKE_BASE/include/public/Printer.hpp \
    $$GLAZED_CAKE_BASE/include/public/Sink.hpp \
    $$GLAZED_CAKE_BASE/include/GlazedCake.hpp

SOURCES += \
    sinks/SinkDebugOutput.cpp \
    sinks/SinkFile.cpp \
    Context.cpp \
    Printer.cpp

INCLUDEPATH += \
    $$GLAZED_CAKE_BASE/include

QT += core

win32 {
    LIBS += -lkernel32
}

include($$GLAZED_CAKE_BASE/config.pri)