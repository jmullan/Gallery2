TOOLDIR=../../tools
CLASSDIR=..
TMPDIR=tmp

include $(TOOLDIR)/GNUmakefile.inc

CLASSFILES  = $(wildcard $(CLASSDIR)/*.class)
XMLFILES    = $(patsubst $(CLASSDIR)/%.class,%.xml,$(CLASSFILES))
INCFILES    = $(patsubst %.xml,%.inc,$(XMLFILES))

inc: $(TMPDIR) $(INCFILES)

$(TMPDIR):
	mkdir $(TMPDIR)

%.inc: $(TMPDIR)/%.xml ClassCode.xsl
	if [ -f $< ]; then $(SAXON) $< ClassCode.xsl > $@; fi

$(TMPDIR)/%.xml: $(CLASSDIR)/%.class
	perl $(TOOLDIR)/extractClassXml.pl \
		--dtd=../$(TOOLDIR)/dtd/GalleryClass2.0.dtd \
		--stub-ok \
		--out $@ \
		$^ 
	if [ -f $@ ]; then $(VALIDATOR) $@; fi

clean:
	rm -rf $(TMPDIR)

scrub: clean
	rm -f *.inc

# Gmake will automatically delete $(TMPDIR)/*.xml files after creating .inc files
# because it thinks that they're intermediate files.  But, we want to save
# them (for now), so mark them as PRECIOUS.
#
.PRECIOUS: $(TMPDIR)/%.xml
