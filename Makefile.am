SUBDIRS = $(ARGP_STANDALONE_DIR) src

PACKAGE = @PACKAGE@
VERSION = @VERSION@

EXTRA_DIST = autogen.sh 

CLEANFILES = *~

gitclean: distclean
	find . -name Makefile.in -exec rm -f {} \;
	find . -name Makefile -exec rm -f {} \;
	rm -fr autom4te.cache m4
	rm -f missing aclocal.m4 config.h.in config.guess
	rm -f config.sub ltmain.sh install-sh configure depcomp
	rm -f config.rpath INSTALL
	rm -f compile
