## -*- mode: makefile; tab-width: 4 -*-

include $(top_srcdir)/Makefile.incl

SUFFIXES =
EXTRA_DIST = stdwx.h
BUILT_SOURCES =
CLEANFILES =

if SUPPORTED_PRECOMPILED_HEADER 

SUFFIXES += .gch
BUILT_SOURCES += stdwx.gch
CLEANFILES += \
	*.gch \
	*.gcda \
	*.gcno \
	*.gcov

stdwx.gch: $(srcdir)/stdwx.h
	$(CXX) -c $(srcdir)/stdwx.h -o stdwx.h.gch $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CXXFLAGS) $(CXXFLAGS) $(WX_CXXFLAGS)  

endif

