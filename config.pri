OBJECTS_DIR = $$GLAZED_CAKE_BASE/lib
MOC_DIR = $$GLAZED_CAKE_BASE/lib
DESTDIR = $$GLAZED_CAKE_BASE/build

CONFIG(debug, debug|release) {
    win32: TARGET = $$join(TARGET,,,d)
}

for (dep, DEPENDENCY_LIBRARIES) {
    win32 {
        CONFIG(debug, debug|release) {
            LIBS += $${DESTDIR}/$${dep}d.lib
        }
        CONFIG(release, release|debug) {
            LIBS += $${DESTDIR}/$${dep}.lib
        }
    } else {
        LIBS += $${DESTDIR}/lib$${dep}.so
    }
}