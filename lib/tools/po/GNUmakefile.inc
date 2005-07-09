#
# Gallery .mo files makefile
#
# This makefile is based on the one provided with the Horde project
# http://www.horde.org/.  As such, it inherits the license from the
# original version.  You can find that license here:
#
# http://cvs.horde.org/co.php/horde/COPYING?r=2.1
#
# I'm not exactly sure what the license restrictions are in this case,
# but I want to give full credit to the original authors:
#
# Copyright 2000-2002 Joris Braakman <jbraakman@yahoo.com>
# Copyright 2001-2002 Chuck Hagenbuch <chuck@horde.org>
# Copyright 2001-2002 Jan Schneider <jan@horde.org>
#
# $Id$
#
MODULE_DIR = $(shell dirname `pwd`)
TYPE_DIR = $(shell dirname $(MODULE_DIR))
APPLICATION = $(shell basename $(TYPE_DIR))_$(shell basename $(MODULE_DIR))

ifdef QUIET
MSGFMT_FLAGS =
else
MSGFMT_FLAGS = -v
endif

MSGFMT = msgfmt $(MSGFMT_FLAGS) -c -o
MSGFMTSOL = msgfmt $(MSGFMT_FLAGS) -o

all: update install

all-remove-obsolete: update remove-obsolete install

messages.po:
	@php -f $(TOOLDIR)/po/extract.php $(MODULE_DIR) $(EXTRA_DIR) > strings.raw
	@xgettext --keyword=_ -C --no-location strings.raw
	@perl -ne 'print if $$. > 4' < messages.po > messages.tmp
	@cat $(TOOLDIR)/po/header.txt messages.tmp > messages.po
	@$(RM) messages.tmp

%.po: messages.po
	@perl $(TOOLDIR)/po/premerge-messages.pl $@ messages.po > messages.tmp
	@-msgmerge --quiet --update $@ messages.tmp  # ignore errors here, we'll catch them on the msgfmt command
	@$(RM) messages.tmp

clean:
	@$(RM) messages.po

update: *.po

install:
	@if test "${OSTYPE}" = "solaris"; then \
		echo "You'll probably get some warnings on Solaris. This is normal."; \
	fi; \
	FAIL=0; \
	for LOCALE in `ls *.po | sed 's/\.[^.]*$$//g'`; do \
		if test $${LOCALE}.po = "messages.po"; then \
			continue; \
		fi; \
		if test -z "$${QUIET}"; then echo $${LOCALE}; fi; \
		if $(TOOLDIR)/po/shtool mkdir -p ../locale/$${LOCALE}/LC_MESSAGES; then \
			if test "${OSTYPE}" = "solaris"; then \
				if {MSGFMTSOL} ../locale/$${LOCALE}/LC_MESSAGES/${APPLICATION}.mo $${LOCALE}.po; then \
					if test ! -z "$${QUIET}"; then \
						echo -n '.'; \
					fi \
				else \
					echo -n "Fail: $${LOCALE}"; \
					FAIL=1; \
				fi \
			else \
				if ${MSGFMT} ../locale/$${LOCALE}/LC_MESSAGES/${APPLICATION}.mo $${LOCALE}.po; then \
					if test ! -z "$${QUIET}"; then \
						echo -n '.'; \
					fi \
				else \
					echo -n "Fail: $${LOCALE}"; \
					FAIL=1; \
				fi \
			fi; \
		else \
			echo "Could not create locale directory for $${LOCALE}."; \
		fi; \
		if test -z "$${QUIET}"; then echo; fi; \
	done; \
	if test $${FAIL} -gt 0; then exit 1; fi;
	@echo '';

remove-obsolete:
	@for LOCALE in `ls *.po | egrep -v messages.po | sed 's/\.[^.]*$$//g'`; do \
		msgattrib --no-obsolete --output-file=$${LOCALE}.po $${LOCALE}; \
	done;
