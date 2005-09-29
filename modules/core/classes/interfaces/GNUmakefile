TOOLDIR ?= ../../../../lib/tools
CLASSDIR ?= ..
PACKAGE ?= GalleryCore
G2_TMPDIR ?= tmp

inc: $(XMLFILES)
	@if [ ! -d $(G2_TMPDIR) ]; then mkdir $(G2_TMPDIR); fi
	perl $(TOOLDIR)/bin/extractClassXml.pl --dtd=../$(TOOLDIR)/dtd/GalleryClass2.0.dtd --stub-ok --quiet --out-dir=$(G2_TMPDIR) $(CLASSDIR)/*.class
	php $(TOOLDIR)/bin/generate-interfaces.php $(PACKAGE)

clean:
	rm -rf $(G2_TMPDIR)

scrub: clean
	rm -f *.inc

# Gmake will automatically delete $(G2_TMPDIR)/*.xml files after creating .inc files
# because it thinks that they're intermediate files.  But, we want to save
# them (for now), so mark them as PRECIOUS.
#
.PRECIOUS: $(G2_TMPDIR)/%.xml
