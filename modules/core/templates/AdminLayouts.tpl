{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Gallery Layouts"}
    {/g->title}
  {/g->banner}

  {g->box style="admin"}
    {g->description}
      {g->text text="Gallery has layouts that can change the way that you navigate around your albums.  You can download and install new layouts, or you can disable layouts if you don't want to use them.  By default, new layouts are disabled.  They must be enabled before you can use them."}
    {/g->description}

    {g->table style="admin_listing" evenodd="true"}
      {g->row}
	{g->column header="true"} {g->text text="Layout Name"} {/g->column}
	{g->column header="true"} {g->text text="Version"} {/g->column}
	{g->column header="true"} {g->text text="Description"} {/g->column}
	{g->column header="true"} {g->text text="Actions"} {/g->column}
      {/g->row}

      {foreach from=$AdminLayouts.layouts item=layout}
	{g->row}
	  {g->column}
	    {$layout.name}
	  {/g->column}
	  {g->column width="10%" align="center" }
	    {$layout.version}
	  {/g->column}
	  {g->column}
	    {g->text text=$layout.description l10Domain=$layout.l10Domain}
	  {/g->column}	
	  {g->column}
	    {if (!empty($layout.action))}
	      {if (empty($layout.action.controller)) }
		{g->link url_return="true" url_view='core:SiteAdmin' url_subView=$layout.action.view}
		  {$layout.action.text}
		{/g->link}
	      {else}
		{g->link url_controller=$layout.action.controller url_layoutName=$layout.action.layoutName url_action=$layout.action.action}
		  {$layout.action.text}
		{/g->link}
	      {/if}
	    {else}
	      &nbsp;
	    {/if}
	  {/g->column}	
	{/g->row}
      {/foreach}
    {/g->table}
  {/g->box}
{/g->pagebox}
