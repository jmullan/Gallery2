GALLERYDIR ?= ../../../..
TOOLDIR ?= $(GALLERYDIR)/lib/tools
CLASSDIR ?= ..
XSLFILE ?= $(GALLERYDIR)/modules/core/classes/interfaces/ClassCode.xsl
PACKAGE ?= GalleryCore
TMPDIR ?= tmp

include $(TOOLDIR)/GNUmakefile.inc

CLASSFILES  = $(wildcard $(CLASSDIR)/*.class)
XMLFILES    = $(patsubst $(CLASSDIR)/%.class,%.xml,$(CLASSFILES))
INCFILES    = $(patsubst %.xml,%.inc,$(XMLFILES))

inc: $(TMPDIR) $(INCFILES)

$(TMPDIR):
	mkdir $(TMPDIR)

%.inc: $(TMPDIR)/%.xml $(XSLFILE)
	if [ -f $< ]; then $(SAXON) $< $(XSLFILE) \
		| perl -pe 's/\@\@package\@\@/$(PACKAGE)/' \
		> $@; fi

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
