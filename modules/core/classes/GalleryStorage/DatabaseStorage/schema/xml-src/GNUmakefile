GALLERYDIR ?= ../../../../../../..
TOOLDIR ?= $(GALLERYDIR)/lib/tools
CLASSDIR ?= ../../../..
XSLFILE ?= $(GALLERYDIR)/modules/core/classes/GalleryStorage/DatabaseStorage/schema/xml-src/DbXml.xsl
TMPDIR ?= tmp
EXTRAXML ?= $(wildcard *.xml)
OUTDIR ?= ../xml-out

include $(TOOLDIR)/GNUmakefile.inc

CLASSFILES  = $(wildcard $(CLASSDIR)/*.class)
XMLFILES = $(patsubst $(CLASSDIR)/%.class,$(OUTDIR)/%.xml,$(CLASSFILES))

xml: $(TMPDIR) $(OUTDIR) $(XMLFILES)
ifneq ($(EXTRAXML),)
	cp $(EXTRAXML) $(OUTDIR)
endif

$(TMPDIR):
	mkdir $(TMPDIR)

$(OUTDIR):
	mkdir $(OUTDIR)

$(OUTDIR)/%.xml: $(TMPDIR)/%.xml $(XSLFILE)
	if [ -f $< ]; then \
		$(SAXON) $< $(XSLFILE) > $@; \
		$(VALIDATOR) $@; \
	fi

$(TMPDIR)/%.xml: $(CLASSDIR)/%.class
	perl $(TOOLDIR)/extractClassXml.pl \
		--dtd=../$(TOOLDIR)/dtd/GalleryClass2.0.dtd $^ \
		--out=$@
	if [ -f $@ ]; then $(VALIDATOR) $@; fi

scrub: clean

clean:
	rm -rf $(TMPDIR)
	rm -rf $(OUTDIR)

# Gmake will automatically delete $(TMPDIR)/.xml files after creating .xml files
# because it thinks that they're intermediate files.  But, we want to save
# them (for now), so mark them as PRECIOUS.
#
.PRECIOUS: $(TMPDIR)/%.xml
