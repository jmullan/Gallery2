{if $makefileType == 'classes'}
all:
	cd interfaces && $(MAKE) -$(MAKEFLAGS)
	cd GalleryStorage/DatabaseStorage/schema && $(MAKE) -$(MAKEFLAGS)

%:
	cd interfaces && $(MAKE) -$(MAKEFLAGS) $@
	cd GalleryStorage/DatabaseStorage/schema && $(MAKE) -$(MAKEFLAGS) $@
{elseif $makefileType == 'interfaces'}
PACKAGE={$ucModuleId}
include ../../../../modules/core/classes/interfaces/GNUmakefile
{else}
include ../../../../../../modules/core/classes/GalleryStorage/DatabaseStorage/schema/GNUmakefile
{/if}


