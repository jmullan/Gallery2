{gallery->main}
  {gallery->component}
    {gallery->bannerbox}
      {gallery->title}
	{gallery->text text="Debug Tree"}
      {/gallery->title}
    {/gallery->bannerbox}

    {gallery->detailedbox}
      {gallery->body}
	{if ($ShowTree.parentIds)}
	  {foreach from=$ShowTree.parentIds item=parentId}
	    {gallery->listingbox}
	      {gallery->item}
		{include file="modules/debug/templates/ShowTreeEntityLink.tpl" entityId=$parentId}
		{gallery->listingbox}
		  {gallery->item}
		    {include file="modules/debug/templates/ShowTreeEntity.tpl" entityId=$ShowTree.entityId}
		  {/gallery->item}
		{/gallery->listingbox}
	      {/gallery->item}
	    {/gallery->listingbox}
	  {/foreach}
	{else}
	  {gallery->listingbox}
	    {gallery->item}
	      {include file="modules/debug/templates/ShowTreeEntity.tpl" entityId=$ShowTree.entityId}
	    {/gallery->item}
	  {/gallery->listingbox}
        {/if}
      {/gallery->body}
    {/gallery->detailedbox}
  {/gallery->component}
{/gallery->main}
