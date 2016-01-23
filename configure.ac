dnl Copyright 2016 Secret Manager Team

dnl Process this file with autoconf to produce a configure script

AC_INIT([secret-manager], [0.1.0], [https://github.com/vadmeste/sm/issues])
AM_INIT_AUTOMAKE

AC_PREREQ([2.57])

m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES(yes)])

if make --help 2>&1 | grep -q no-print-directory; then
   AM_MAKEFLAGS="$AM_MAKEFLAGS --no-print-directory";
fi

if make --help 2>&1 | grep -q quiet; then
   AM_MAKEFLAGS="$AM_MAKEFLAGS --quiet"
fi

if libtool --help 2>&1 | grep -q quiet; then
   AM_LIBTOOLFLAGS="--quiet";
fi

AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([Makefile
                src/Makefile
                ])

AC_PROG_MAKE_SET
AC_PROG_CC


AC_CHECK_PROG([PKGCONFIG], [pkg-config], [yes], [no])
if test "x$PKGCONFIG" = "xno"; then
  AC_MSG_ERROR([pkg-config not found])
fi

# PKG_CHECK_MODULES([KEYUTILS], [keyutils-1.5], [HAVE_KEYUTILS="yes"], [HAVE_KEYUTILS="no"])
# if test "x$HAVE_KEYUTILS" == "xno"; then
#   AC_MSG_ERROR([ERROR! keyutils-1.5 not found...])
# fi
 
AC_CHECK_HEADERS([libintl.h])
AC_CHECK_HEADERS([keyutils.h])

AC_OUTPUT
