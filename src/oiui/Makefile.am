AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = \
	oiui

FRAMEWORK = \
	../framework/ControlListenerImpl.cpp\
	../framework/ControlListenerImpl.h\
	../framework/EventHandler.cpp\
	../framework/EventHandler.h\
	../framework/FileNotFoundException.cpp\
	../framework/FileNotFoundException.h\
	../framework/MathUtil.h\
	../framework/searchFile.cpp\
	../framework/searchFile.h\
	../framework/util.h\
        ../Logger.h

NAVIGATION = \
	../navigation/Navigation.cpp\
	../navigation/Navigation.h\
	../navigation/NavigationListenerImpl.cpp\
	../navigation/NavigationListenerImpl.h

MEDIA = \
	../media/Media.cpp\
	../media/Media.h\
	../media/MediaListenerImpl.cpp\
	../media/MediaListenerImpl.h\
	../media/MediaListWidgetRenderer.cpp\
	../media/MediaListWidgetRenderer.h

oiui_SOURCES = \
	${FRAMEWORK}\
	${NAVIGATION}\
	${MEDIA}\
	Main.cpp\
	Main.h	

oiui_LDADD = \
	$(DBUSMM_LIBS) \
	$(STATEVAL_LIBS) \
	$(OICF_LIBS) \
	$(GLIBMM_LIBS) \
	$(SIGC_LIBS) \
	$(EFL_LIBS) \
	$(LOG4CXX_LIBS)

oiui_CPPFLAGS = \
	$(DBUSMM_CFLAGS) \
	$(STATEVAL_CFLAGS) \
	$(OICF_CFLAGS) \
	$(GLIBMM_CFLAGS) \
	$(SIGC_CFLAGS) \
	$(EFL_CFLAGS) \
	$(LOG4CXX_CFLAGS)

## File created by the gnome-build tools

