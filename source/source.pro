GLAZED_CAKE_BASE = ..

TEMPLATE = lib
CONFIG += staticlib

TARGET = GlazedCake

HEADERS += \
    $$GLAZED_CAKE_BASE/include/public/sinks/SinkDebugOutput.hpp \
    $$GLAZED_CAKE_BASE/include/public/sinks/SinkFile.hpp \
    $$GLAZED_CAKE_BASE/include/public/Base.hpp \
    $$GLAZED_CAKE_BASE/include/public/Context.hpp \
    $$GLAZED_CAKE_BASE/include/public/Levels.hpp \
    $$GLAZED_CAKE_BASE/include/public/Sink.hpp \
    $$GLAZED_CAKE_BASE/include/GlazedCake.hpp

SOURCES += \
    sinks/SinkDebugOutput.cpp \
    sinks/SinkFile.cpp \
    GlazedCake.cpp \
    Context.cpp

INCLUDEPATH += \
    $$GLAZED_CAKE_BASE/include

QT += core

win32 {
    LIBS += -lkernel32
}

OBJECTS_DIR = $$GLAZED_CAKE_BASE/lib
MOC_DIR = $$GLAZED_CAKE_BASE/lib
DESTDIR = $$GLAZED_CAKE_BASE/build