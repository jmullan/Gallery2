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
APPLICATION ?= $(shell basename $(TYPE_DIR))_$(shell basename $(MODULE_DIR))

ifdef QUIET
    MSGFMT_FLAGS =
else
    MSGFMT_FLAGS = -v
endif

MSGFMT = msgfmt $(MSGFMT_FLAGS) -c -o
MSGFMTSOL = msgfmt $(MSGFMT_FLAGS) -o

PO ?= *
LANGPO = $(shell echo $@ | perl -ne 'chomp; print if (s/^(..)_..\.po/$$1.po/ and -s)')
COMPENDIUM = $(shell echo $@ | perl -ne 'chomp; print if (s/^(..)_..\.po/-C $$1.po/ and -s)')

all: update install

all-remove-obsolete: update remove-obsolete install

messages.po:
	@php -f $(TOOLDIR)/po/extract.php $(MODULE_DIR) > strings.raw.tmp
	@# Don't extract right to strings.raw because extract.php tries to preserve
	@# some old data from strings.raw and the > redirect blanks it out.
	@mv strings.raw.tmp strings.raw
	@xgettext --keyword=_ -C --no-location strings.raw
	@sed '1,4 d' < messages.po > messages.tmp
	@cat $(TOOLDIR)/po/header.txt messages.tmp > messages.po
	@$(RM) messages.tmp

%.po: messages.po
	@perl $(TOOLDIR)/po/premerge-messages.pl $@ messages.po > messages.tmp
	@# ignore errors from msgmerge, we'll catch them on the msgfmt command:
	@-if [ -s messages.tmp ]; then \
	    msgmerge --quiet --width=95 $(COMPENDIUM) --update $@ messages.tmp; \
	  elif [ -z "$(NOCREATE)" ]; then \
	    if [ -n "$(LANGPO)" ]; then \
	      perl $(TOOLDIR)/po/premerge-messages.pl -2 messages.po $(LANGPO) > $@; \
	    else cp messages.po $@; fi; \
	  fi
	@$(RM) messages.tmp

clean:
	@$(RM) messages.po

update: $(PO).po

install:
	@if test "${OSTYPE}" = "solaris"; then \
		echo "You'll probably get some warnings on Solaris. This is normal."; \
	fi; \
	FAIL=0; \
	echo "Updating ${PO}"; \
	for LOCALE in `ls ${PO}.po | sed 's/\.[^.]*$$//g'`; do \
		if test $${LOCALE}.po = "messages.po"; then \
			continue; \
		fi; \
		if test -z "$${QUIET}"; then echo $${LOCALE}; fi; \
		if $(TOOLDIR)/po/shtool mkdir -p ../locale/$${LOCALE}/LC_MESSAGES; then \
			php -f $(TOOLDIR)/po/trim-po.php $${LOCALE}.po > tmp.po; \
			if test "${OSTYPE}" = "solaris"; then \
				if {MSGFMTSOL} ../locale/$${LOCALE}/LC_MESSAGES/${APPLICATION}.mo \
						tmp.po; then \
					if test -n "$${QUIET}"; then \
						echo -n '.'; \
					fi \
				else \
					echo -n "Fail: $${LOCALE}"; \
					FAIL=1; \
				fi \
			else \
				if ${MSGFMT} ../locale/$${LOCALE}/LC_MESSAGES/${APPLICATION}.mo \
						tmp.po; then \
					if test -n "$${QUIET}"; then \
						echo -n '.'; \
					fi \
				else \
					echo -n "Fail: $${LOCALE}"; \
					FAIL=1; \
				fi \
			fi; \
			$(RM) tmp.po; \
		else \
			echo "Could not create locale directory for $${LOCALE}."; \
			FAIL=1; \
		fi; \
		if test -z "$${QUIET}"; then echo; fi; \
	done; \
	if test $${FAIL} -gt 0; then exit 1; fi;
	@echo '';

remove-obsolete:
	@for LOCALE in `ls *.po | egrep -v messages.po | sed 's/\.[^.]*$$//g'`; do \
		msgattrib --no-obsolete --output-file=$${LOCALE}.po $${LOCALE}; \
	done;
