GLAZED_CAKE_BASE = ..

TARGET = GlazedCake
TEMPLATE = lib

HEADERS += \
    $$GLAZED_CAKE_BASE/include/public/Levels.hpp \
    $$GLAZED_CAKE_BASE/include/public/Context.hpp \
    $$GLAZED_CAKE_BASE/include/GlazedCake.hpp

SOURCES += \
    GlazedCake.cpp \
    Context.cpp

INCLUDEPATH += \
    $$GLAZED_CAKE_BASE/include

QT += core

OBJECTS_DIR = $$GLAZED_CAKE_BASE/build
MOC_DIR = $$GLAZED_CAKE_BASE/build
DESTDIR = $$GLAZED_CAKE_BASE/lib
