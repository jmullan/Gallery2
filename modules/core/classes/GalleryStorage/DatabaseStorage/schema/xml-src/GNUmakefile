TOOLDIR     = ../../../../tools
CLASSDIR    = ../../..
TMPDIR      = tmp
OUTDIR      = ../xml-out

include $(TOOLDIR)/GNUmakefile.inc

CLASSFILES  = $(wildcard $(CLASSDIR)/*.class)
XMLFILES = $(patsubst $(CLASSDIR)/%.class,$(OUTDIR)/%.xml,$(CLASSFILES))

xml: $(TMPDIR) $(OUTDIR) $(XMLFILES)
	cp *.xml $(OUTDIR)

$(TMPDIR):
	mkdir $(TMPDIR)

$(OUTDIR):
	mkdir $(OUTDIR)

$(OUTDIR)/%.xml: $(TMPDIR)/%.xml DbXml.xsl
	if [ -f $< ]; then \
		$(SAXON) $< DbXml.xsl > $@; \
		$(VALIDATOR) $@; \
	fi

$(TMPDIR)/%.xml: $(CLASSDIR)/%.class
	perl $(TOOLDIR)/extractClassXml.pl \
		--dtd=../$(TOOLDIR)/dtd/GalleryClass2.0.dtd $^ \
		--out=$@
	if [ -f $@ ]; then $(VALIDATOR) $@; fi

scrub: clean
	rm -rf $(TMPDIR)
	rm -rf $(OUTDIR)/*.xml

clean:
	rm -f $(TMPDIR)/*.xml

# Gmake will automatically delete $(TMPDIR)/.xml files after creating .xml files
# because it thinks that they're intermediate files.  But, we want to save
# them (for now), so mark them as PRECIOUS.
#
.PRECIOUS: $(TMPDIR)/%.xml
