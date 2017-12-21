for (dep, DEPENDENCY_LIBRARIES) {
    win32 {
    	LIBS += $${DESTDIR}/$${dep}.lib
    	PRE_TARGETDEPS += $${DESTDIR}/$${dep}.lib
    } else {
	    LIBS += $${DESTDIR}/lib$${dep}.so
    	PRE_TARGETDEPS += $${DESTDIR}/lib$${dep}.so
    }   
}