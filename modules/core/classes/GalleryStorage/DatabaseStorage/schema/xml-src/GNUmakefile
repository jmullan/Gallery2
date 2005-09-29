TOOLDIR ?= ../../../../../../../lib/tools
CLASSDIR ?= ../../../..
G2_TMPDIR ?= tmp
OUTDIR ?= ../xml-out

xml:
	@if [ ! -d $(G2_TMPDIR) ]; then mkdir $(G2_TMPDIR); fi
	@if [ ! -d $(OUTDIR) ]; then mkdir $(OUTDIR); fi
	perl $(TOOLDIR)/bin/extractClassXml.pl --dtd=../$(TOOLDIR)/dtd/GalleryClass2.0.dtd --quiet --out-dir=$(G2_TMPDIR) $(CLASSDIR)/*.class
	find . -name '*.xml' -exec cp {} ../xml-out \;
	php -f $(TOOLDIR)/bin/generate-dbxml.php

scrub: clean

clean:
	rm -rf $(G2_TMPDIR)
	rm -rf $(OUTDIR)

# Gmake will automatically delete $(G2_TMPDIR)/.xml files after creating .xml files
# because it thinks that they're intermediate files.  But, we want to save
# them (for now), so mark them as PRECIOUS.
#
.PRECIOUS: $(G2_TMPDIR)/%.xml
