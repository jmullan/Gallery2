GALLERYDIR ?= ../../../..
TOOLDIR ?= $(GALLERYDIR)/lib/tools
CLASSDIR ?= ..
PACKAGE ?= GalleryCore
G2_TMPDIR ?= tmp

include $(TOOLDIR)/GNUmakefile.inc

PWD	    = $(pwd)
CLASSFILES  = $(wildcard $(CLASSDIR)/*.class)
XMLFILES    = $(patsubst $(CLASSDIR)/%.class,$(G2_TMPDIR)/%.xml,$(CLASSFILES))
INCFILES    = $(patsubst %.xml,%.inc,$(XMLFILES))

all: $(G2_TMPDIR) inc

inc: $(XMLFILES)
	php $(TOOLDIR)/bin/generate-interfaces.php $(PACKAGE)

$(G2_TMPDIR):
	mkdir $(G2_TMPDIR)

$(G2_TMPDIR)/%.xml: $(CLASSDIR)/%.class
	perl $(TOOLDIR)/bin/extractClassXml.pl \
		--dtd=../$(TOOLDIR)/dtd/GalleryClass2.0.dtd \
		--stub-ok \
	        --quiet \
		--out $@ \
		$^
	if [ -f $@ ]; then $(VALIDATOR) $@; fi

clean:
	rm -rf $(G2_TMPDIR)

scrub: clean
	rm -f *.inc

# Gmake will automatically delete $(G2_TMPDIR)/*.xml files after creating .inc files
# because it thinks that they're intermediate files.  But, we want to save
# them (for now), so mark them as PRECIOUS.
#
.PRECIOUS: $(G2_TMPDIR)/%.xml
