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
    {/g->success}
  {/if}

  {g->tabbedbox}
    {g->tabset}
      {g->item}
	{g->title}
	  {if ($AdminLayouts.mode == 'config')}
	    {g->text text="All Layouts"}
	  {else}
	    {g->link url_view="core:SiteAdmin" url_subView="core:AdminLayouts" url_mode="config"}
	      {g->text text="All Layouts"}
	    {/g->link}
	  {/if}
	{/g->title}
      {/g->item}

      {foreach from=$AdminLayouts.layouts key=layoutName item=layout}
	{g->item}
	  {g->title}
	    {if ($AdminLayouts.mode == 'editLayout') && ($AdminLayouts.activeLayoutName == $layoutName)}
	      {g->text text=$layout.name l10Domain=$layout.l10Domain}
	    {else}
	      {g->link url_view="core:SiteAdmin" url_subView="core:AdminLayouts" url_mode="editLayout" url_activeLayoutName=$layoutName}
		{g->text text=$layout.name l10Domain=$layout.l10Domain}
	      {/g->link}
	    {/if}
	  {/g->title}
	{/g->item}
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
      {else}
	{g->box style="admin"}
	  {g->title}
	    {g->text text="%s Layout Settings" arg1=$layout.name}
	  {/g->title}

	  {g->description}
	    {g->text text="These are the global settings for the layout.  They can be overridden at the album level."}
	  {/g->description}

	  {if !empty($AdminLayouts.settings)}
	    {g->table style="admin_widgets" evenodd="true"}
	      {foreach from=$AdminLayouts.settings item=setting}
		{g->row}
		  {g->column}
		    {g->text text=$setting.name l10Domain=$layout.l10Domain}
		  {/g->column}
		  {g->column}
		    {if ($setting.type == 'text-field')}
		      {g->input type="text" size="6" name="key_$setting.key"}{$setting.values.0}{/g->input}
		    {/if}
		  {/g->column}
		{/g->row}
	      {/foreach}
	    {/g->table}
	  {else}
	    {g->element style="emphasized"}
	      {g->text text="There are no settings for this layout"}
	    {/g->element}
	  {/if}
	{/g->box}
      {/if}
    {/g->element}
    {g->box}
      {g->element}
	{g->input type="submit" name="form.action.save"}{g->text text="Save"}{/g->input}
	{g->input type="submit" name="form.action.undo"}{g->text text="Undo"}{/g->input}
      {/g->element}
    {/g->box}
  {/g->tabbedbox}
{/g->pagebox}
