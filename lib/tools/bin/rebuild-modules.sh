#!/bin/sh
CURDIR=`pwd`

MAKE=`(which gmake || which make) 2>/dev/null`

cd ../../../modules
cvs update -kk `find . -name '*.inc' | egrep 'classes/interfaces'`
cvs update -kk `find . -name '*.sql'`

makefiles=`find . -name GNUmakefile | egrep 'classes/GNUmakefile'`
for makefile in $makefiles; do
    (cd `dirname $makefile` && $MAKE scrub && $MAKE && $MAKE clean)
done

cd $CURDIR
