{g->form action_controller="$controller"}
  {g->input type="hidden" name="form[formName]"}{$form.formName}{/g->input}

  {g->main}
    {g->breadcrumb}
      {g->item}
	{g->title}
	  {g->text text="Site Administration"}
	{/g->title}
      {/g->item}
    {/g->breadcrumb}

    {g->sidebar}
      {g->box style="sidebar"}
	{g->title}
	  {g->text text="Admin Options"}
	{/g->title}

	{g->listing}
	  {foreach from=$SiteAdmin.subViewChoices item=choice}
	    {if ($SiteAdmin.subViewName == $choice.view)}
	      {g->item selected="true"}
		{g->title}
		  {$choice.name}
		{/g->title}
	      {/g->item}
	    {else}
	      {g->item}
		{g->title}
		  {g->link url_view='core:SiteAdmin' url_subView=$choice.view}
		    {$choice.name}
		  {/g->link}
		{/g->title}
	      {/g->item}
	    {/if}
	  {/foreach}
	{/g->listing}
      {/g->box}
	
      {g->box style="sidebar"}
	{g->title}
	  {g->text text="Navigation"}
	{/g->title}

	{g->listing}
	  {g->item}
	    {g->title}
	      {g->link}
		{g->text text="Browse Gallery"}
	      {/g->link}
	    {/g->title}
	  {/g->item}
	{/g->listing}
      {/g->box}
    {/g->sidebar}

    {include file=$SiteAdmin.viewBodyFile l10Domain=$SiteAdmin.viewL10Domain}

  {/g->main}
{/g->form}