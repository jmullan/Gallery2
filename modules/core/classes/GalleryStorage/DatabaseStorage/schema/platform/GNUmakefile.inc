TOOLDIR     = ../../../../../tools
SRCDIR      = ../../xml-out
XMLFILES    = $(wildcard $(SRCDIR)/*.xml)

include $(TOOLDIR)/GNUmakefile.inc

SQLFILES = $(patsubst $(SRCDIR)/%.xml,%.sql,$(XMLFILES))

sql: $(SQLFILES)

%.sql: $(SRCDIR)/%.xml $(XSLFILE)
	if [ -f $< ]; then \
		$(SAXON) $< $(XSLFILE) > $@; \
	fi

scrub: clean
	rm -rf *.sql

clean:
