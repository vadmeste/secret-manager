AM_CPPFLAGS = -DDATADIR=\"$(datadir)\" -DLOCALEDIR=\"$(localedir)\"

bin_PROGRAMS = sm

sm_SOURCES = main.c str-replace.c opts.c

noinst_HEADERS = str-replace.h

AM_LDFLAGS="-lkeyutils"
AM_CFLAGS = -Wall -g

CLEANFILES = *~
