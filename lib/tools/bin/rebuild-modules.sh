#!/bin/sh
CURDIR=`pwd`

MAKE=`(which gmake || which make) 2>/dev/null`

makefiles=`find . -name GNUmakefile | egrep 'classes/GNUmakefile'`
for makefile in $makefiles; do
    echo -n "Building "
    dirname `dirname $makefile`
    (cd `dirname $makefile` && $MAKE -s clean && $MAKE -s && $MAKE -s clean)
done

cd $CURDIR
