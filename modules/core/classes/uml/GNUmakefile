GALLERYDIR ?= ../../../..
TOOLDIR ?= $(GALLERYDIR)/lib/tools
CLASSDIR ?= ..
XSLFILE ?= $(GALLERYDIR)/modules/core/classes/uml/JavaClasses.xsl
PACKAGE ?= GalleryCore
TMPDIR ?= tmp

include $(TOOLDIR)/GNUmakefile.inc

CLASSFILES  = $(wildcard $(CLASSDIR)/*.class)
XMLFILES    = $(patsubst $(CLASSDIR)/%.class,%.xml,$(CLASSFILES))
JAVAFILES   = $(patsubst %.xml,%.java,$(XMLFILES))

java: $(TMPDIR) $(JAVAFILES)

$(TMPDIR):
	mkdir $(TMPDIR)

%.java: $(TMPDIR)/%.xml $(XSLFILE)
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
	rm -f *.java

# Gmake will automatically delete $(TMPDIR)/*.xml files after creating .java files
# because it thinks that they're intermediate files.  But, we want to save
# them (for now), so mark them as PRECIOUS.
#
.PRECIOUS: $(TMPDIR)/%.xml
