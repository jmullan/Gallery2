CLASSDIR ?= ..
TOOLDIR ?= ../../../../lib/tools
TMPDIR ?= tmp
RXP ?= $(shell which rxp 2>/dev/null)
XMLLINT ?= $(shell which xmllint 2>/dev/null)
XMLFILES = $(wildcard xml-src/*.xml)

all: validate tmp dbxml sql

tmp:
	@if [ ! -d tmp ]; then mkdir tmp; fi
	@if [ ! -d tmp/classxml ]; then mkdir tmp/classxml; fi
	@if [ ! -d tmp/dbxml ]; then mkdir tmp/dbxml; fi

dbxml:
	perl $(TOOLDIR)/bin/extractClassXml.pl --dtd=$(TOOLDIR)/dtd/GalleryClass2.0.dtd --quiet --out-dir=tmp/classxml $(CLASSDIR)/*.class
	@if [ "x" != "$(XMLFILES)x" ]; then cp xml-src/*.xml tmp/dbxml; fi
	php -f $(TOOLDIR)/bin/generate-dbxml.php

sql:
	php -f $(TOOLDIR)/bin/generate-sql.php

clean:
	rm -rf tmp

validate:
	@if [ "x" != "$(XMLFILES)x" ]; then \
		if [ -x "$(XMLLINT)" ]; then \
			xmllint --valid --noout $(XMLFILES); \
		elif [ -x "$(RXP)" ]; then \
			for xmlfile in $(XMLFILES); do \
				rxp -sV $$xmlfile; \
			done \
		else \
			echo "No available XML validators (need xmllint or rxp)"; \
		fi \
	fi
