{g->pagebox}
  {g->banner}
    {g->title}
      Gallery Modules
    {/g->title}
  {/g->banner}

  {g->box style="admin"}
    {g->description}
      {g->text text="Gallery features come as separate modules.  You can download and install modules to add more features to your Gallery, or you can disable features if you don't want to use them.  In order to use a feature, you must install, configure (if necessary) and activate it.  If you don't wish to use a feature, you can deactivate it."}
    {/g->description}

    {g->table style="admin_listing"}
      {g->row}
	{g->column header="true"} {g->text text="Module Name"} {/g->column}
	{g->column header="true"} {g->text text="Version"} {/g->column}
	{g->column header="true"} {g->text text="Description"} {/g->column}
	{g->column header="true"} {g->text text="Actions"} {/g->column}
      {/g->row}

      {foreach from=$AdminModules.modules item=module}
	{g->row}
	  {g->column}
	    {$module.name}
	  {/g->column}
	  {g->column width="10%" align="center" }
	    {$module.version}
	  {/g->column}
	  {g->column}
	    {$module.description}
	  {/g->column}	
	  {g->column}
	    {if (!empty($module.action))}
	      {if (empty($module.action.controller)) }
		{g->link url_return="true" url_view='core:SiteAdmin' url_subView=$module.action.view}
		  {$module.action.text}
		{/g->link}
	      {else}
		{g->link url_controller=$module.action.controller url_moduleName=$module.action.moduleName url_action=$module.action.action}
		  {$module.action.text}
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
