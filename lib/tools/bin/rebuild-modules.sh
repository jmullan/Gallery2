#!/bin/sh
CURDIR=`pwd`

cd ../../../modules
cvs update -kk `find . -name '*.inc' | egrep 'classes/interfaces'`
cvs update -kk `find . -name '*.sql'`

makefiles=`find . -name GNUmakefile | egrep 'classes/GNUmakefile'`
for makefile in $makefiles; do
    (cd `dirname $makefile` && gmake scrub && gmake && gmake clean)
done

cd $CURDIR