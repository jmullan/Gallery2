{gallery->form action_controller="$controller"}
  {gallery->input type="hidden" name="form.formName"}{$form.formName}{/gallery->input}

  {gallery->main}
    {gallery->pathbar}
      {gallery->item}
	{gallery->text text="Site Administration"}
      {/gallery->item}
    {/gallery->pathbar}

    {gallery->sidebar}
      {gallery->component}
	{gallery->simplebox}
	  {gallery->body}
	    {gallery->listingbox}
	      {gallery->title}
		{gallery->text text="Admin Options"}
	      {/gallery->title}
	      {foreach from=$SiteAdmin.subViewChoices item=choice}
		{if ($SiteAdmin.subViewName == $choice.view)}
		  {gallery->item selected="true"}
		    {$choice.name}
		  {/gallery->item}
		{else}
		  {gallery->item}
		    {gallery->link url_view='core:SiteAdmin' url_subView=$choice.view}
		      {$choice.name}
		    {/gallery->link}
		  {/gallery->item}
		{/if}
	      {/foreach}
	    {/gallery->listingbox}
	  {/gallery->body}
	{/gallery->simplebox}
	
	{gallery->simplebox}
	  {gallery->body}
	    {gallery->listingbox}
	      {gallery->title}
		{gallery->text text="Navigation"}
	      {/gallery->title}
	      {gallery->item}
		{gallery->link}
		  {gallery->text text="Browse Gallery"}
		{/gallery->link}
	      {/gallery->item}
	    {/gallery->listingbox}
	  {/gallery->body}
	{/gallery->simplebox}
      {/gallery->component}
    {/gallery->sidebar}

    {gallery->component}
      {include file=$SiteAdmin.viewBodyFile l10Domain=$SiteAdmin.viewL10Domain}
    {/gallery->component}
  {/gallery->main}
{/gallery->form}