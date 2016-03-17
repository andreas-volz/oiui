dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(oiui, 0.1)

AM_INIT_AUTOMAKE
AM_CONFIG_HEADER(config.h)
AM_MAINTAINER_MODE
AC_CONFIG_MACRO_DIR([m4])

AC_ISC_POSIX
AC_PROG_CXX
AM_PROG_CC_STDC
AC_HEADER_STDC

AM_PROG_LIBTOOL

dnl Check for headers
ACX_PTHREAD
if test x"$acx_pthread_ok" = xyes; then
  AC_DEFINE(HAVE_PTHREAD_H, 1, [Define to enable pthread support])
  AM_CONDITIONAL(HAVE_PTHREAD, test x"$acx_pthread_ok" = xyes)
fi

dnl Check for edce_cc
EDJE_DEF=""
AC_SUBST(EDJE_DEF)
AC_ARG_WITH(edje-cc,
        AC_HELP_STRING([--with-edje-cc=PATH],[Specify a specific path to edje_cc]),
[
  v=$withval;
  edje_cc=$v
  echo "  Edje Compiler 'edje_cc' explicitly set to "$edje_cc;
],[
  edje_cc=$(pkg-config --variable=prefix edje)/bin/edje_cc
])
AC_SUBST(edje_cc)

ACX_PTHREAD(true,exit)

PKG_CHECK_MODULES(GLIBMM, glibmm-2.4 gthread-2.0)

PKG_CHECK_MODULES(SIGC, sigc++-2.0)

PKG_CHECK_MODULES(DBUSMM, dbus-c++-1 dbus-c++-ecore-1)

PKG_CHECK_MODULES(EFL, eflxx edjexx ecorexx einaxx elementaryxx)

PKG_CHECK_MODULES(OICF, OICFControl OICFNavigation OICFMedia)

## TODO: ecorexx only needed for edje_console example...
PKG_CHECK_MODULES([EFL], elementaryxx ecorexx,
     AM_CONDITIONAL(HAVE_EFL, [test 1 = 1]),
     AM_CONDITIONAL(HAVE_EFL, [test 0 = 1]),
)

dnl Check for option to enable logging
AC_MSG_CHECKING(whether to enable logging)
AC_ARG_ENABLE(logging,
        [  --enable-logging=[no/yes]        enables logging build (default=yes)],,
                 enable_logging=yes)

if [ ! test "$enable_logging" != "yes"]; then
  AC_DEFINE(HAVE_LOGGING, 1, [Define to enable logging build])
  AC_MSG_RESULT(yes)
  PKG_CHECK_MODULES([LOG4CXX], liblog4cxx,
        AC_DEFINE(HAVE_LOG4CXX, 1, [Define to enable logging build]),test 1=1
  )
else
  AC_MSG_RESULT(no)
fi

dnl Check for edce_cc
EDJE_DEF=""
AC_SUBST(EDJE_DEF)
AC_ARG_WITH(edje-cc,
        AC_HELP_STRING([--with-edje-cc=PATH],[Specify a specific path to edje_cc]),
[
  v=$withval;
  edje_cc=$v
  echo "  Enlightenment edje_cc explicitly set to "$edje_cc;
],[
  edje_cc=$(pkg-config --variable=prefix edje)/bin/edje_cc
])
AC_SUBST(edje_cc)


#dnl Set PACKAGE SOURCE DIR in config.h.
packagesrcdir=`cd $srcdir && pwd`

#dnl Set PACKAGE PREFIX
if test "x${prefix}" = "xNONE"; then
  packageprefix=${ac_default_prefix}
else
  packageprefix=${prefix}
fi

#dnl Set PACKAGE DIRS in config.h
packagedatadir=share/${PACKAGE}
packagedocdir=doc/${PACKAGE}
packagepixmapsdir=share/pixmaps/${PACKAGE}

#dnl Subst PACKAGE_DATA_DIR.
NO_PREFIX_PACKAGE_DATA_DIR="${packagedatadir}"
AC_SUBST(NO_PREFIX_PACKAGE_DATA_DIR)
PACKAGE_DATA_DIR="${packageprefix}/${packagedatadir}"
AC_SUBST(PACKAGE_DATA_DIR)

dnl Subst PACKAGE_DOC_DIR.
NO_PREFIX_PACKAGE_DOC_DIR="${packagedocdir}"
AC_SUBST(NO_PREFIX_PACKAGE_DOC_DIR)
PACKAGE_DOC_DIR="${packageprefix}/${packagedocdir}"
AC_SUBST(PACKAGE_DOC_DIR)

dnl Subst PACKAGE_PIXMAPS_DIR.
NO_PREFIX_PACKAGE_PIXMAPS_DIR="${packagepixmapsdir}"
AC_SUBST(NO_PREFIX_PACKAGE_PIXMAPS_DIR)
PACKAGE_PIXMAPS_DIR="${packageprefix}/${packagepixmapsdir}"
AC_SUBST(PACKAGE_PIXMAPS_DIR)

AC_DEFINE_UNQUOTED(PACKAGE_DATA_DIR, "${packageprefix}/${packagedatadir}","")
AC_DEFINE_UNQUOTED(SYSTEM_DATA_DIR, "${packageprefix}/${systemdatadir}","")
AC_DEFINE_UNQUOTED(PACKAGE_DOC_DIR, "${packageprefix}/${packagedocdir}","")
AC_DEFINE_UNQUOTED(PACKAGE_PIXMAPS_DIR, "${packageprefix}/${packagepixmapsdir}","")
AC_DEFINE_UNQUOTED(SYSTEM_PIXMAPS_DIR, "${packageprefix}/${systempixmapsdir}","")
AC_DEFINE_UNQUOTED(PACKAGE_SOURCE_DIR, "${packagesrcdir}","")

PKG_CHECK_MODULES(STATEVAL, stateval)
AC_OUTPUT([
Makefile
src/Makefile
src/oiui/Makefile
data/Makefile
data/sm/Makefile
data/sm/screens/Makefile
data/sm/screens/images/Makefile
data/sm/screens/fonts/Makefile
])
