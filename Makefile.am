## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src \
	data

oiuidocdir = ${prefix}/doc/oiui
oiuidoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS


EXTRA_DIST = $(oiuidoc_DATA)

ACLOCAL_AMFLAGS=-I m4

# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(oiuidocdir)
