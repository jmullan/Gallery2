{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Gallery Modules"}
    {/g->title}
  {/g->banner}

  {if isset($status)}
    {g->success}
      {if isset($status.installed)}
	{g->text text="Successfully installed module %s" arg1=$status.installed}
      {/if}
      {if isset($status.activated)}
	{g->text text="Successfully activated module %s" arg1=$status.activated}
      {/if}
      {if isset($status.deactivated)}
	{g->text text="Successfully deactivated module %s" arg1=$status.deactivated}
      {/if}
    {/g->success}
  {/if}

  {g->box style="admin"}
    {g->description}
      {g->text text="Gallery features come as separate modules.  You can download and install modules to add more features to your Gallery, or you can disable features if you don't want to use them.  In order to use a feature, you must install, configure (if necessary) and activate it.  If you don't wish to use a feature, you can deactivate it."}
    {/g->description}

    {g->table style="admin_listing" evenodd="true"}
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
	    {g->text text=$module.description l10Domain=$module.l10Domain}
	  {/g->column}	
	  {g->column}
	    {if (!empty($module.action))}
	      {if (empty($module.action.controller)) }
		{g->link arg1="return=true" arg2="view=core:SiteAdmin" arg3="subView=`$module.action.view`"}
		  {$module.action.text}
		{/g->link}
	      {else}
		{g->link arg1="controller=`$module.action.controller`" arg2="moduleId=`$module.action.moduleId`" arg3="action=`$module.action.action`"}
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
