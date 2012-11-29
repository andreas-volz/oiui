MAINTAINERCLEANFILES = Makefile.in
SUBDIRS = images fonts

NAME = screens

EDJE_CC = @edje_cc@
EDJE_FLAGS = \
	-v \
	-id $(top_srcdir)/data/sm/$(NAME)/images \
	-fd $(top_srcdir)/data/sm/$(NAME)/fonts \
	@EDJE_DEF@

filesdir = $(pkgdatadir)/themes
files_DATA = oiui_$(NAME).edj

EXTRA_DIST = icons.edc \
	     images.edc \
	     main.edc \
	     MediaMainView.edc \
	     MenuMainView.edc \
	     NavInfoView.edc \
	     NavMainView.edc \
	     NavRouteCalcView.edc \
	     NavRouteListView.edc

oiui_$(NAME).edj: Makefile main.edc
	$(EDJE_CC) $(EDJE_FLAGS) \
	$(top_srcdir)/data/sm/$(NAME)/main.edc \
	$(top_builddir)/data/sm/$(NAME)/oiui_$(NAME).edj

clean-local:
	rm -f *.edj

