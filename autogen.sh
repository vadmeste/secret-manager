#!/bin/sh

## Do the autogeneration
aclocal
autoheader
autoconf
automake --add-missing --copy --foreign

# Instruct user on next steps
echo
echo "Please proceed with configuring, compiling, and installing."
