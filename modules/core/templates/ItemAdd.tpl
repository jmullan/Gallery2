{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Add Items"}

      <!-- Gotta put this somewhere; move it when we switch to pure HTML templates -->
      {g->input type="hidden" name="addPlugin"}{$ItemAdd.addPlugin}{/g->input}
    {/g->title}
  {/g->banner}

  {g->tabbedbox}
    {g->tabset}
      {foreach from=$ItemAdd.plugins item=plugin} 
	{if $plugin.isSelected}
	  {g->item selected="true"}
	    {g->title}
	      {$plugin.title}
	    {/g->title}
	  {/g->item}
	{else}
	  {g->item}
	    {g->title}
	      {g->link arg1="view=core:ItemAdmin" arg2="subView=core:ItemAdd" arg3="itemId=`$ItemAdmin.item.id`" arg4="addPlugin=`$plugin.id`"}
		{$plugin.title}
	      {/g->link}
	    {/g->title}
	  {/g->item}
	{/if}
      {/foreach}
    {/g->tabset}

    {include file=$ItemAdd.pluginFile l10Domain=$ItemAdmin.viewL10Domain}

  {/g->tabbedbox}
{/g->pagebox}
