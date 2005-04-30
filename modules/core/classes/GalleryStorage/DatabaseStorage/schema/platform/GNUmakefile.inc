TOOLDIR     = ../../../../../../../../lib/tools
SRCDIR      = ../../xml-out
XMLFILES    = $(wildcard $(SRCDIR)/*.xml)

include $(TOOLDIR)/GNUmakefile.inc

SQLFILES = $(patsubst $(SRCDIR)/%.xml,%.sql,$(XMLFILES))

sql: $(SQLFILES)
	mv InstallerTest.sql InstallerTest_sql

%.sql: $(SRCDIR)/%.xml $(XSLFILE)
	if [ -f $< ]; then \
		$(SAXON) $< $(XSLFILE) > $@; \
	fi

scrub: clean
	rm -rf *.sql

clean:
