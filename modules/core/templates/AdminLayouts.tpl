{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Gallery Layouts"}
    {/g->title}
  {/g->banner}

  {if isset($status)}
    {g->success}
      {if isset($status.activated)}
	{g->text text="Successfully activated layout %s" arg1=$status.activated}
      {/if}
      {if isset($status.deactivated)}
	{g->text text="Successfully deactivated layout %s" arg1=$status.deactivated}
      {/if}
      {if isset($status.savedLayout)}
	{g->text text="Successfully saved layout settings"}
      {/if}
      {if isset($status.restoredLayout)}
	{g->text text="Restored layout settings"}
      {/if}
    {/g->success}
  {/if}

  {g->tabbedbox}
    {g->tabset}
      {g->item}
	{g->title}
	  {if ($AdminLayouts.mode == 'config')}
	    {g->text text="All Layouts"}
	  {else}
	    {g->link arg1="view=core:SiteAdmin" arg2="subView=core:AdminLayouts" arg3="mode=config"}
	      {g->text text="All Layouts"}
	    {/g->link}
	  {/if}
	{/g->title}
      {/g->item}

      {foreach from=$AdminLayouts.layouts key=layoutId item=layout}
	{if $AdminLayouts.layouts.$layoutId.active}
	  {g->item}
	    {g->title}
	      {if ($AdminLayouts.mode == 'editLayout') && ($AdminLayouts.layoutId == $layoutId)}
		{g->text text=$layout.name l10Domain=$layout.l10Domain}
	      {else}
		{g->link arg1="view=core:SiteAdmin" arg2="subView=core:AdminLayouts" arg3="mode=editLayout" arg4="layoutId=$layoutId"}
		  {g->text text=$layout.name l10Domain=$layout.l10Domain}
		{/g->link}
	      {/if}
	    {/g->title}
	  {/g->item}
	{/if}
      {/foreach}
    {/g->tabset}

    {g->element}
      {if ($AdminLayouts.mode == 'config')}
	{g->box style="admin"}
	  {g->title}
	    {g->text text="Layout Configuration"}
	  {/g->title}
	    
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

	    {foreach from=$AdminLayouts.layouts key=layoutId item=layout}
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
		  {g->linkset}
		    {if (isset($layout.actions.activate))}
		      {g->item}
			{g->title}
			  {g->link arg1="controller=core:AdminLayouts" arg2="form[action][activate]=1" arg3="layoutId=$layoutId"}
			    {g->text text="activate"}
			  {/g->link}
			{/g->title}
		      {/g->item}
		    {/if}
		    {if (isset($layout.actions.deactivate))}
		      {g->item}
			{g->title}
			  {g->link arg1="controller=core:AdminLayouts" arg2="form[action][deactivate]=1" arg3="layoutId=$layoutId"}
			    {g->text text="deactivate"}
			  {/g->link}
			{/g->title}
		      {/g->item}
		    {/if}
		  {/g->linkset}
		{/g->column}	
	      {/g->row}
	    {/foreach}
	  {/g->table}
	{/g->box}
      {/if}

      {if ($AdminLayouts.mode == "editLayout")}
	{g->box style="admin"}
	  {g->title}
	    {g->text text="%s Layout Settings" arg1=$layout.name}
	  {/g->title}

	  {g->description}
	    {g->text text="These are the global settings for the layout.  They can be overridden at the album level."}
	  {/g->description}

	  {if !empty($AdminLayouts.settings)}
	    {g->table style="admin_widgets"}
	      {foreach from=$AdminLayouts.settings item=setting}
		{assign var="settingKey" value=$setting.key}
		{g->row}
		  {g->column}
		    {g->text text=$setting.name l10Domain=$layout.l10Domain}
		  {/g->column}
		  {g->column}
		    {if ($setting.type == 'text-field')}
		      {g->input type="text" size="6" name="form[key][$settingKey]"}{$form.key.$settingKey}{/g->input}
		    {/if}
		  {/g->column}
		{/g->row}
		{if isset($form.error.key.$settingKey.invalid)}
		  {g->row}
		    {g->column colspan="2"}
		      {g->error}
			{$form.errorMessage.$settingKey}
		      {/g->error}
		    {/g->column}
		  {/g->row}
		{/if}
	      {/foreach}
	    {/g->table}
	  {else}
	    {g->element style="emphasized"}
	      {g->text text="There are no settings for this layout"}
	    {/g->element}
	  {/if}
	{/g->box}

	{g->box style="admin"}
	  {g->element}
	    {g->input type="hidden" name="layoutId"}{$AdminLayouts.layoutId}{/g->input}
	    {g->input type="hidden" name="mode"}editLayout{/g->input}
	    {g->input type="submit" name="form[action][saveLayout]"}{g->text text="Save"}{/g->input}
	    {g->input type="submit" name="form[action][undoLayout]"}{g->text text="Undo"}{/g->input}
	  {/g->element}
	{/g->box}
      {/if}
    {/g->element}
  {/g->tabbedbox}
{/g->pagebox}
